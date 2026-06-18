# 02 — exit-code

Difficulty: ★☆☆

Estimated time: 15–20 minutes

## Objective

Write a freestanding x86-64 Linux program with a `_start` entry point that exits with a **specific non-zero exit code**: **42**.

The program produces no output. Its only observable effect is the exit status.

## Syscall ABI reminder

```
rax = syscall number
rdi = arg1
syscall
```

Relevant number:

| Number | Name  | Args          |
|--------|-------|---------------|
| 60     | exit  | rdi=status    |

The kernel never returns from `exit`. The process simply stops.

## What to edit

```text
src/exit_code.S
```

## How to do it

The whole program is one syscall — `exit(42)`:

```asm
.globl _start
_start:
    mov rax, 60           ; syscall #60 = exit
    mov rdi, 42           ; arg1: status code 42
    syscall               ; process stops; nothing runs after
```

That is it. The stub already has this shape but passes `0`; change it to `42`. After
`make solve`, check the exit status from the shell with `echo $?` — it should print
`42`. (Exit codes are a single byte, 0–255.)

## Commands

```bash
make test    # RED: stub exits 0; check fails (expected 42)
make solve   # GREEN: solution exits 42
make check   # builds both without running
make clean   # remove build/ artifacts
```

## Pitfalls

- You must declare `_start` as `.globl _start`.
- The stub exits with code 0, which is wrong. The solution must exit 42.
- Exit codes are 8-bit values: 0–255. Values above 255 are silently masked by the shell.
- There is no output to check here — only the process exit status (`$?` in the shell).
- You still must call the `exit` syscall; `_start` must not fall through.
