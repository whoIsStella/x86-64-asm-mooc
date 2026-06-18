# SysV AMD64 ABI Notes

These notes summarize the ABI rules most exercises rely on. The authoritative source is the AMD64 System V ABI.

## Integer/pointer arguments

For normal C-callable functions on Linux x86-64, the first six integer/pointer arguments are passed in:

```text
rdi, rsi, rdx, rcx, r8, r9
```

Integer/pointer return values come back in `rax`.

## Callee-saved registers

A function must preserve:

```text
rbx, rbp, r12, r13, r14, r15
```

If you modify one, save and restore it.

## Stack alignment

Before a `call`, the stack must be 16-byte aligned as required by the ABI. On entry to a normal function, `rsp` is typically 8 mod 16 because the return address was pushed by `call`.

## Red zone

The SysV ABI defines a 128-byte red zone below `rsp` that leaf functions may use. Kernel/interrupt contexts and some build modes may not allow this. Exercises should state when they rely on it.

## Syscall is different

Linux `syscall` does not use exactly the same register convention as C calls. See `SYSCALLS.md`.
