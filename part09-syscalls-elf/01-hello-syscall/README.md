# 01 — hello-syscall

Difficulty: ★☆☆

Estimated time: 20–30 minutes

## Objective

Write a freestanding x86-64 Linux program with a `_start` entry point that:

1. Writes the string `"hello\n"` (6 bytes) to file descriptor 1 (stdout) using the `write` syscall.
2. Exits with status code 0 using the `exit` syscall.

There is no `main`. There is no libc. Your `_start` is the very first instruction the OS runs.

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
src/hello_syscall.S
```

## How to do it

A syscall is "load `rax` with the syscall number, load the arguments into
`rdi`/`rsi`/`rdx`, run `syscall`." You do it twice — once for `write`, once for `exit`:

```asm
.section .rodata
msg:
    .ascii "hello\n"
msg_len = . - msg          ; assembler computes 6 = (here) - (msg label)
.text
.globl _start
_start:
    mov rax, 1             ; syscall #1 = write
    mov rdi, 1             ; arg1: fd 1 = stdout
    lea rsi, [rip + msg]   ; arg2: address of the bytes (RIP-relative, Part 6)
    mov rdx, msg_len       ; arg3: how many bytes = 6
    syscall                ; → kernel writes "hello\n"

    mov rax, 60            ; syscall #60 = exit
    xor rdi, rdi           ; arg1: status 0
    syscall                ; process ends here — never returns
```

The argument registers `rdi`/`rsi`/`rdx` are the *same* as the C ABI's first three,
but the syscall *number* goes in `rax` (not used for C args) and `exit` never returns,
so there is no `ret`. `.ascii` emits the raw bytes; `msg_len = . - msg` lets the
assembler count them for you.

## Commands

```bash
make test    # RED: stub prints nothing; check fails
make solve   # GREEN: solution prints "hello" and exits 0
make check   # builds both without running
make clean   # remove build/ artifacts
```

## Pitfalls

- You must declare `_start` as `.globl _start` — the linker requires it as the entry point.
- Your string constant belongs in `.rodata` or `.data`; the `.text` section is for executable code.
- `write` syscall number is **1** on x86-64 Linux (it is **not** the same as `printf`).
- You must call the `exit` syscall (number 60) before `_start` returns, or the program will crash.
- `syscall` clobbers `rcx` and `r11`; do not rely on them across a syscall.
- The 6 in `rdx` counts the bytes to write: `h`, `e`, `l`, `l`, `o`, `\n` = 6.
