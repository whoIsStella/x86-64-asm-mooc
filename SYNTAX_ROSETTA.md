# Syntax Rosetta: Intel, GAS Intel, and AT&T

This course starts with GAS Intel syntax because it works with the system C compiler and does not require NASM. Later exercises may add NASM and AT&T variants.

## Operand order

| Meaning | Intel / GAS Intel | AT&T |
|---|---|---|
| copy rsi to rax | `mov rax, rsi` | `movq %rsi, %rax` |
| add rsi into rax | `add rax, rsi` | `addq %rsi, %rax` |

Intel order is destination, source. AT&T order is source, destination.

## Register names

| Register | Intel / GAS Intel | AT&T |
|---|---|---|
| return register | `rax` | `%rax` |
| first integer arg | `rdi` | `%rdi` |
| second integer arg | `rsi` | `%rsi` |

## Immediates and memory

| Meaning | Intel / GAS Intel | AT&T |
|---|---|---|
| immediate 7 | `7` | `$7` |
| load from address in rdi | `mov rax, [rdi]` | `movq (%rdi), %rax` |
| base + index*8 + 16 | `[rdi + rsi*8 + 16]` | `16(%rdi,%rsi,8)` |

## GAS Intel caveat

GAS Intel syntax is enabled with:

```asm
.intel_syntax noprefix
```

It is similar to NASM Intel syntax, but directives, symbol metadata, comments, and some memory forms differ. Do not assume NASM examples can be pasted into GAS unchanged.
