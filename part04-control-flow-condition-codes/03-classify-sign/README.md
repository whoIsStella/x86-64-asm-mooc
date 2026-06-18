# 03 — Classify sign

Difficulty: ★☆☆

Estimated time: 20–30 minutes

## Objective

Implement a SysV AMD64 ABI-compatible function:

```c
int classify(long x);
```

Return:

- `-1` if `x < 0`
- `0` if `x == 0`
- `1` if `x > 0`

Use a **jump ladder**: a single `cmp` followed by two conditional jumps (`jl` and `je`) that dispatch to labelled blocks, with the positive case handled by fall-through.

## ABI reminder

Under the SysV AMD64 ABI:

- `x` arrives in `rdi`
- return value (an `int`) goes in `eax`

## How to do it

One `cmp rdi, 0` sets every flag you need; then a two-rung ladder of jumps peels off
the negative and zero cases, leaving the positive case to fall straight through:

```asm
    cmp rdi, 0
    jl  .Lneg          ; x < 0
    je  .Lzero         ; x == 0
    mov eax, 1         ; fell through ⇒ x > 0
    ret
.Lneg:
    mov eax, -1
    ret
.Lzero:
    xor eax, eax       ; eax = 0
    ret
```

"Fall-through" means: if neither jump fires, execution just continues to the next
line — no jump needed for the last case. Write the result into `eax` (32-bit), not
`rax`: the return type is `int`, and writing `eax` cleanly zero-extends the rest of
`rax` (the Part 2 rule).

## What to edit

Edit only:

```text
src/classify_sign.S
```

## Commands

```bash
make test    # RED until implemented
make solve   # GREEN reference
make check   # build stub and solution
make objdump # inspect reference disassembly
```

## Key instructions

| Instruction | Meaning |
|-------------|---------|
| `cmp rdi, 0` | Set SF, ZF, OF from `rdi - 0` |
| `jl label` | Jump if less (signed, SF != OF) |
| `je label` | Jump if equal (ZF == 1) |
| `jg label` | Jump if greater (signed, ZF=0 and SF==OF) |

## Pitfalls

- The return type is `int` (32-bit), so write `eax`, not `rax`. Writing `eax` automatically zero-extends into the full `rax`.
- `mov eax, -1` sign-extends the immediate into a 32-bit register, which is what C callers expect for a negative `int`.
- A single `cmp rdi, 0` sets all the flags you need; you do not need a second `cmp` or `test`.
