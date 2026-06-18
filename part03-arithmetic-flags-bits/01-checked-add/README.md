# 01 — Checked add (overflow detection)

Difficulty: ★☆☆

Estimated time: 25–35 minutes

## Objective

Implement a SysV AMD64 ABI-compatible function:

```c
int checked_add(long a, long b, long *out);
```

Compute `a + b` and store the result in `*out`. Return `1` if signed overflow
occurred (the overflow flag `OF` was set by the `add` instruction), otherwise
return `0`.

## ABI reminder

Under the SysV AMD64 ABI:

- `a` arrives in `rdi`
- `b` arrives in `rsi`
- `out` arrives in `rdx` (pointer)
- return value (int) goes in `eax`

## How to do it

The trick is that `add` already detects overflow for you — it sets the `OF` flag as a
side effect. You just have to *capture* that flag immediately, before any other
instruction disturbs it. Four steps:

```asm
add  rdi, rsi      ; rdi = a + b; OF flag = 1 if this overflowed (signed)
mov  [rdx], rdi    ; store the sum into *out  (rdx holds the pointer; [rdx] = the long)
seto al            ; al = the OF flag as a 0/1 byte  ("set if overflow")
movzx eax, al      ; widen that byte to a clean 32-bit int return value
ret
```

Order matters: `mov [rdx], rdi` is a plain store and does **not** touch the flags, so
`OF` from the `add` is still valid when `seto` reads it. If you reordered things so an
arithmetic instruction ran in between, `seto` would capture the wrong flag.

## What to edit

Edit only:

```text
src/checked_add.S
```

## Commands

```bash
make test    # RED until implemented
make solve   # GREEN reference
make check   # build stub and solution
make objdump # inspect reference disassembly
```

## Key instructions

- `add rdi, rsi` — adds two 64-bit registers and sets flags as side-effects.
- `seto al` — sets `al` to 1 if the overflow flag (`OF`) is set, 0 otherwise.
- `movzx eax, al` — zero-extends the byte result into `eax` (and by extension into `rax`).

## Pitfalls

- `OF` (overflow flag) signals *signed* overflow; `CF` (carry flag) signals *unsigned* overflow. They are different.
- `seto` captures `OF` *after* the `add`; any instruction between `add` and `seto` may clobber the flags.
- Writing to `[rdx]` dereferences the pointer — the test passes a valid stack address.
