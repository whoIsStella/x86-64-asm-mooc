# 02 — Signed vs unsigned comparison (three-way compare)

Difficulty: ★☆☆

Estimated time: 25–35 minutes

## Objective

Implement a SysV AMD64 ABI-compatible function:

```c
int cmp3(long a, long b);
```

Return `-1` if `a < b`, `0` if `a == b`, `1` if `a > b` using **signed**
comparison semantics (i.e. `-1 < 1`, `LONG_MIN < 0`).

Use `jl`/`jg` (signed condition codes), **not** `jb`/`ja` (unsigned).

## ABI reminder

Under the SysV AMD64 ABI:

- `a` arrives in `rdi`
- `b` arrives in `rsi`
- return value (int) goes in `eax`

## How to do it

`cmp rdi, rsi` computes `rdi - rsi` purely to set the flags (it throws the subtraction
result away). After it, a signed conditional jump tells you which case you are in.
Structure it as "assume equal, then jump away if not":

```asm
    xor eax, eax       ; assume a == b  → return 0  (eax = 0)
    cmp rdi, rsi       ; set flags from a - b
    jl  .Lless         ; signed a <  b ?  go set -1
    jg  .Lgreater      ; signed a >  b ?  go set  1
    ret                ; neither fired → equal → eax is already 0
.Lless:
    mov eax, -1
    ret
.Lgreater:
    mov eax, 1
    ret
```

A label like `.Lless:` is just a name for a spot in the code (the leading `.L` keeps
it local/private). `jl`/`jg` are the **signed** jumps — using the unsigned `jb`/`ja`
here would call `-1` "bigger than `1`" because it reads the all-ones bit pattern as a
huge unsigned number.

## What to edit

Edit only:

```text
src/signed_unsigned_cmp.S
```

## Commands

```bash
make test    # RED until implemented
make solve   # GREEN reference
make check   # build stub and solution
make objdump # inspect reference disassembly
```

## Key instructions

- `cmp rdi, rsi` — computes `rdi - rsi` and sets `SF`, `OF`, `ZF` (does not write a destination).
- `jl label` — jump if **less** (signed): `SF != OF`.
- `jg label` — jump if **greater** (signed): `ZF=0` and `SF == OF`.
- `jb`/`ja` are the *unsigned* equivalents; using them here would give wrong results for negative values.

## Why signed vs unsigned matters

With unsigned comparison, the bit pattern `0xFFFFFFFFFFFFFFFF` (i.e. `-1L`
when interpreted as a signed `long`) is treated as `ULONG_MAX` — the *largest*
unsigned value. A correct signed implementation must return `-1` for
`cmp3(-1, 1)`, not `1`.
