# 03 — raw-cat (freestanding syscall loop)

Difficulty: ★★☆

Estimated time: 30–50 minutes

## Objective

Write a freestanding (no-libc) x86-64 assembly program that reads from stdin
(fd 0) and writes to stdout (fd 1) in a loop until EOF, then exits with code 0.
It behaves exactly like `cat` with no arguments:

```bash
printf 'hello world' | ./build/prog_solution
# -> prints: hello world
```

No C runtime.  No `main()`.  Entry point is `_start`.  Linked with
`-nostdlib -static -no-pie`.

## Parts synthesized

| Part | Concept used |
|------|-------------|
| 1 — Registers & Arithmetic | set up syscall arguments in registers |
| 2 — Data Movement | stack buffer allocation with `sub rsp` |
| 3 — Control Flow | loop with `jmp`, `jz`/`js` for EOF detection |
| 9 — Linux Syscalls | `read` (0), `write` (1), `exit` (60) |

## Syscall ABI

Linux x86-64 syscall convention (`syscall` instruction):

| Register | Role |
|----------|------|
| `rax` | syscall number (on entry); return value (on exit) |
| `rdi` | argument 1 |
| `rsi` | argument 2 |
| `rdx` | argument 3 |
| `r10` | argument 4 |
| `r8`  | argument 5 |
| `r9`  | argument 6 |

Syscalls used:

```
SYS_read  = 0   read(int fd, void *buf, size_t count)
                returns: bytes read (0 = EOF, negative = error)

SYS_write = 1   write(int fd, const void *buf, size_t count)
                returns: bytes written (may be < count on partial write)

SYS_exit  = 60  exit(int status)
                does not return
```

## Algorithm

```
allocate 4096-byte stack buffer (sub rsp, 4096)

loop:
    rax = read(0, rsp, 4096)
    if rax <= 0: break          // 0 = EOF, negative = error

    r8 = rax                    // total bytes to write
    r9 = rsp                    // write pointer

    write_loop:
        rax = write(1, r9, r8)
        if rax <= 0: exit        // write error
        r8 -= rax               // bytes remaining
        r9 += rax               // advance pointer
        if r8 != 0: goto write_loop

    goto loop

exit(0)
```

The inner write loop handles **partial writes**: the kernel may write fewer
bytes than requested if the output pipe buffer is full.  A correct `cat`
must retry until all bytes are flushed.

## What to edit

Edit only:

```
src/raw_cat.S
```

The solution lives in `solution/raw_cat.S`.

## Commands

```bash
make test    # RED: stub exits immediately without output, test fails
make solve   # GREEN: solution passes single-line and multi-line checks
make check   # build both without running
make clean   # remove build/
```

## Pitfalls

- **Not looping on partial writes**: `write` may return fewer bytes than
  requested.  If you just call `write` once per `read`, you may silently drop
  data on large inputs or full pipe buffers.
- **Forgetting EOF detection**: `read` returns 0 at EOF and negative on error.
  Both must terminate the loop; checking only for 0 may spin forever on error.
- **Using 32-bit registers for pointers**: `rsp` and buffer pointers must stay
  64-bit.  Accidentally using `esp` truncates the address.
- **Stack alignment**: the Linux ABI requires `rsp` to be 16-byte aligned at
  `_start`; subtracting 4096 (a multiple of 16) preserves that.
- **`-nostdlib` + `_start`**: without `-nostdlib`, the linker provides a C
  runtime `_start` that calls `main`.  With `-nostdlib`, you must define
  `_start` yourself and call `exit` explicitly — falling off the end of
  `_start` causes a segfault.

## Safety note

This program uses local pipes only.  No network syscalls (`socket`, `connect`,
`bind`) are used or required.  The only file descriptors touched are stdin (0)
and stdout (1), both inherited from the parent process.

## Expert review questions

1. **Why must `raw_cat` loop on partial writes rather than assuming a single
   `write` call flushes all bytes?  Under what OS conditions does a `write` to
   stdout return fewer bytes than requested?**

2. **`read` returning 0 signals EOF.  What does `read` returning a negative value
   indicate, and why is treating both cases the same (exit the loop) acceptable
   here but not in production code?**

3. **The program allocates its 4096-byte buffer on the stack with `sub rsp, 4096`
   rather than using a `.bss` section.  What are the trade-offs of each approach
   in terms of address-space layout, TLB pressure, and BSS zero-initialization?**
