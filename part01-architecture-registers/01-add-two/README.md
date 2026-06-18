# 01 — Add two integers

Difficulty: ★☆☆

Estimated time: 20–30 minutes

> Prerequisite: [Part 0](../../part00-ground-zero/README.md). This exercise combines
> `01-return-constant` (leave a value in `rax`) and `02-return-input` (read an
> argument from `rdi`) — now with a *second* argument and an addition.

## Objective

Implement a SysV AMD64 ABI-compatible assembly function:

```c
long add_two(long a, long b);
```

On Linux x86-64 under the SysV ABI:

- `a` arrives in `rdi`
- `b` arrives in `rsi`
- the return value must be placed in `rax`

## How to do it

The most direct path uses only instructions you already know from Part 0:

```asm
mov rax, rdi    # rax = a
add rax, rsi    # rax = a + b
ret
```

The reference `solution/` instead uses a single `lea rax, [rdi + rsi]` — a common
idiom that computes `rdi + rsi` in one instruction without touching the flags. Don't
worry if `lea` looks strange yet; Part 2 is devoted to it. Either approach passes the
tests. After it goes green, run `make objdump` and compare what your version compiled
to versus the reference.

## What to edit

Edit only:

```text
src/add_two.S
```

Do not edit the frozen tests.

## Commands

```bash
make test    # RED until implemented
make solve   # GREEN reference
make check   # build stub and solution
make objdump # inspect reference disassembly
```

## Why this matters

This is the smallest useful assembly/C trust boundary. You are not just adding numbers; you are proving that you understand where the ABI places inputs and outputs.

## Pitfalls

- Returning in `rdi` or `rsi` instead of `rax`.
- Assuming register choice is arbitrary.
- Forgetting that GAS Intel syntax is enabled by `.intel_syntax noprefix`.
