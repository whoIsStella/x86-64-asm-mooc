# Linux x86-64 Syscall Notes

Linux syscalls use the `syscall` instruction and a register convention distinct from the C function ABI.

## Register convention

```text
rax = syscall number
rdi = arg1
rsi = arg2
rdx = arg3
r10 = arg4
r8  = arg5
r9  = arg6
```

Return value is in `rax`. Negative values in the range `-4095..-1` represent `-errno` at the raw syscall layer.

## Clobbers

`syscall` clobbers `rcx` and `r11`.

## Safety boundary

Syscall exercises in this course must be local and deterministic. No exercise should make network connections or execute a shell payload by default.
