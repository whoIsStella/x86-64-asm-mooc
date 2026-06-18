# 03 — write-count

Difficulty: ★★☆

Estimated time: 30–45 minutes

## Objective

Write a freestanding x86-64 Linux program with a `_start` entry point that:

1. Writes the string `"ABCABCABC"` (exactly 9 bytes, **no newline**) to stdout.
2. Exits with status code 0.

You can produce the output however you like — a single `write` call, three separate `write` calls of 3 bytes each, or a loop. The validation only checks the final output.

## Syscall ABI reminder

```
rax = syscall number
rdi = arg1
rsi = arg2
rdx = arg3
syscall
```

Relevant numbers:

| Number | Name  | Args                        |
|--------|-------|-----------------------------|
| 1      | write | rdi=fd, rsi=buf, rdx=count  |
| 60     | exit  | rdi=status                  |

## What to edit

```text
src/write_count.S
```

## How to do it

Store `"ABC"` once and write it three times in a counted loop (Part 4), then exit. The
one trap: `syscall` destroys `rcx` and `r11`, so keep your loop counter somewhere safe
like `rbx`, and reload the `write` arguments every iteration (the kernel may clobber
them too):

```asm
.section .rodata
abc:
    .ascii "ABC"
.text
.globl _start
_start:
    mov rbx, 3                ; loop counter — rbx survives the syscall
.Lloop:
    mov rax, 1                ; write
    mov rdi, 1                ; stdout
    lea rsi, [rip + abc]      ; buffer
    mov rdx, 3                ; 3 bytes
    syscall
    dec rbx                   ; counter--
    jnz .Lloop                ; repeat while not zero  → 3 × "ABC" = "ABCABCABC"

    mov rax, 60               ; exit
    xor rdi, rdi              ; status 0
    syscall
```

`dec`+`jnz` is the loop: `dec` sets the zero flag when `rbx` hits 0, and `jnz` keeps
looping until then. The arguments are re-loaded inside the loop precisely because a
syscall is allowed to trample caller-saved registers.

## Commands

```bash
make test    # RED: stub produces wrong output
make solve   # GREEN: solution outputs "ABCABCABC"
make check   # builds both without running
make clean   # remove build/ artifacts
```

## Suggested approach (loop variant)

1. Store `"ABC"` in `.rodata`.
2. Set a loop counter (register) to 3.
3. Each iteration: call `write(1, abc_buf, 3)`.
4. Decrement counter and jump back if not zero.
5. Call `exit(0)`.

Note: `syscall` clobbers `rcx` and `r11`, so use a callee-safe register like `rbx` for the loop counter. (Since there are no C callers here, any register works; just be consistent.)

## Pitfalls

- You must declare `_start` as `.globl _start`.
- `syscall` clobbers `rcx` and `r11` — save your loop counter in another register (e.g. `rbx`).
- The output must be exactly `"ABCABCABC"` — no trailing newline, no extra bytes.
- You still must call the `exit` syscall at the end.
- For the loop variant: remember to restore `rsi` (and other args) each iteration before the `syscall`.
