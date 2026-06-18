# 03 — Bit operations: popcount and rotate

Difficulty: ★★☆

Estimated time: 30–45 minutes

## Objective

Implement a SysV AMD64 ABI-compatible function:

```c
unsigned long popcount_and_rotate(unsigned long x, int r);
```

Return `popcnt(x) + left_rotate(x, r)`:

- `popcnt(x)` — count the number of set bits in `x` using the `popcnt` instruction.
- `left_rotate(x, r)` — rotate `x` left by `r` bit positions using the `rol` instruction.

## ABI reminder

Under the SysV AMD64 ABI:

- `x` arrives in `rdi` (unsigned 64-bit)
- `r` arrives in `esi` (int; rotation count)
- return value goes in `rax` (unsigned 64-bit)

## How to do it

Two independent computations on the same input `x`, then add them. Compute the
popcount first (into the return register), then rotate the original `x`, then sum:

```asm
    popcnt rax, rdi    ; rax = number of 1-bits in x
    mov    ecx, esi    ; put the rotate count r into ecx, so its low byte cl is the count
    rol    rdi, cl     ; rdi = x rotated left by r  (variable rotates MUST use cl)
    add    rax, rdi    ; rax = popcnt(x) + rotate(x, r)
    ret
```

The one non-obvious rule: a *variable* shift or rotate count can only come from the
single register `cl` (the low byte of `rcx`) — the hardware has no other form. So you
copy `r` (in `esi`) into `ecx` and name it `cl` in the `rol`. Do `popcnt` before the
rotate so you still have the original `x` in `rdi` to rotate.

## What to edit

Edit only:

```text
src/bit_ops.S
```

## Commands

```bash
make test    # RED until implemented
make solve   # GREEN reference
make check   # build stub and solution
make objdump # inspect reference disassembly
```

## Key instructions

- `popcnt rax, rdi` — counts set bits in `rdi`, result in `rax`. Requires SSE4.2 (supported on all modern x86-64 CPUs post-2008).
- `rol rdi, cl` — rotate `rdi` left by the count in `cl` (the low byte of `rcx`). Variable-count rotates always use `cl`.
- `mov ecx, esi` — move the rotation count into `ecx` so `cl` holds the low byte.

## Pitfalls

- Variable-count shifts and rotates **must** use `cl` as the count operand; you cannot write `rol rdi, esi` directly.
- `popcnt` sets `ZF` if the result is zero and clears `OF`, `SF`, `AF`, `CF`, `PF` — keep this in mind if you add flag-dependent code after it.
- Left-rotating by 0 is a no-op; rotating by 64 is also effectively a no-op (mod 64).
