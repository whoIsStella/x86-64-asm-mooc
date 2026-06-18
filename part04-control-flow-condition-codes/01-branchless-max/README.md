# 01 — Branchless max

Difficulty: ★☆☆

Estimated time: 20–30 minutes

## Objective

Implement a SysV AMD64 ABI-compatible function:

```c
long imax(long a, long b);
```

Return the greater of `a` and `b` **without any conditional jump**. Use `cmp` to set condition codes, then `cmovg` ("conditional move if greater") to select the result.

## ABI reminder

Under the SysV AMD64 ABI:

- `a` arrives in `rdi`
- `b` arrives in `rsi`
- return value goes in `rax`

## How to do it

The pattern for any branchless select is: put one candidate in the destination first,
then *conditionally* overwrite it with the other. Here, start with `b` and replace it
with `a` only when `a > b`:

```asm
    mov   rax, rsi     ; tentatively, the answer is b
    cmp   rdi, rsi     ; set flags from a - b
    cmovg rax, rdi     ; if a > b (signed), overwrite rax with a
    ret
```

`cmovg` ("conditional move if greater") either copies or does nothing, based on the
flags `cmp` just set — but it is a plain data instruction, so there is no branch for
the CPU to mispredict. If `a > b` it loads `a`; otherwise `rax` keeps `b`. Either way
the larger value ends up in `rax`.

## What to edit

Edit only:

```text
src/branchless_max.S
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
| `cmp rdi, rsi` | Compute `rdi - rsi` and set SF, ZF, OF flags; discard result |
| `cmovg dst, src` | Copy `src` into `dst` if the previous comparison was "greater" (signed) |

## Pitfalls

- `cmp a, b` sets flags as if computing `a - b`. So `cmovg` fires when `a > b`.
- `cmov` variants come in signed (`cmovg`/`cmovl`) and unsigned (`cmova`/`cmovb`) flavors; use the signed variant for `long`.
- There is no conditional-move instruction for 8-bit or 16-bit operands; use 64-bit registers here.
