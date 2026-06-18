# Part 9 — Linux syscalls and minimal ELF programs

Estimated time: 6 hours  
Prerequisites: Part 5 (stack frames and SysV ABI)

> So far your code was always *called by* C and returned to it. This part removes C
> entirely: you write `_start`, the program's true entry point, and talk to the
> operating system directly with the `syscall` instruction.
>
> **Why care / how it connects:** every program that prints, reads a file, or exits
> ultimately makes a syscall — `printf` is just `write` with wrapping. Seeing the bare
> kernel boundary demystifies what libc does for you. It reuses Part 4 loops and Part 6
> `.rodata` strings, with a *different* register convention than the C ABI (note the
> contrast carefully — it is a classic source of bugs).

## Why raw syscalls and freestanding ELF?

Every C program you compile normally links the C runtime (CRT): the linker adds `crt1.o`, which contains `_start`. That function initialises `libc`, then calls your `main`. When `main` returns, `_start` calls `exit(3)` from libc.

In these exercises you skip all of that. The linker is told there is **no libc** (`-nostdlib`), so the binary is _freestanding_: no CRT, no libc, nothing. The OS jumps directly to `_start` — your code.

### What happens if you do not call exit?

When `_start` returns, the CPU tries to execute whatever bytes follow your function. On Linux that is typically the ELF auxiliary-vector data or unmapped memory, so the process crashes with a segfault (or an illegal-instruction fault). You **must** call the `exit` syscall before `_start` returns.

### Kernel ABI vs libc

The `syscall` instruction is the hardware gate between user space and the kernel. It is **not** a C function call:

```
rax  = syscall number
rdi  = arg1
rsi  = arg2
rdx  = arg3
r10  = arg4
r8   = arg5
r9   = arg6
```

Return value is in `rax`. The kernel clobbers `rcx` and `r11`. On error, `rax` is a small negative number (`-errno`).

Common syscall numbers for these exercises:

| Number | Name  | Signature (kernel view)                           |
|--------|-------|---------------------------------------------------|
| 0      | read  | (fd, buf, count) → bytes_read                    |
| 1      | write | (fd, buf, count) → bytes_written                 |
| 60     | exit  | (status) → (never returns)                       |

File descriptors 0, 1, 2 are stdin, stdout, stderr — same convention as in C.

### Building freestanding ELF

```bash
cc -nostdlib -static -no-pie -o build/prog solution/my_prog.S
```

Flags explained:
- `-nostdlib` — do not link libc or CRT startup objects
- `-static` — produce a self-contained static binary
- `-no-pie` — disable position-independent-executable hardening (keeps addresses simple)

## Safety note

All exercises in this part are **local, non-networked, deterministic programs**. No exercise opens files, connects to the network, or executes shell commands. Do not extend them to do so.

## Exercises

| # | Name | Difficulty | Objective |
|---|------|------------|-----------|
| 01 | hello-syscall | ★☆☆ | Write "hello\n" to stdout via write syscall, exit 0 |
| 02 | exit-code     | ★☆☆ | Exit with a specific non-zero code via exit syscall |
| 03 | write-count   | ★★☆ | Write "ABCABCABC" (9 bytes), verify output exactly |

## References

- [../SYSCALLS.md](../SYSCALLS.md) — syscall numbers and register ABI
- [../REFERENCE.md](../REFERENCE.md) — instruction quick-reference
- [../docs/source-map.md](../docs/source-map.md) — source layout guide
