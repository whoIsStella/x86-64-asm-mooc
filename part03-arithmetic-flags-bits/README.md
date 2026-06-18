# Part 3 — Arithmetic, flags, and bit manipulation

> Prerequisite: [Part 2](../part02-data-movement-addressing/README.md). You can move
> data between registers and memory. Now you make the CPU *compute* — and meet the
> hidden output every arithmetic instruction produces alongside its result: the
> **flags**.
>
> **Why care / how it connects:** flags are how the CPU "remembers" a comparison.
> Part 4 turns them into every branch and loop you will ever write, so this part is the
> foundation of all control flow.

This part teaches how arithmetic instructions set condition flags as side-effects, why signed and unsigned comparisons require different condition codes, and how to use hardware bit-manipulation instructions (`popcnt`, `rol`).

New vocabulary you will use: `add`/`sub` set flags; `cmp a, b` does a "throwaway"
subtraction `a - b` purely to set flags (it keeps no result); `seto`/`setc` copy a
single flag into a 0/1 byte; `popcnt` counts set bits; `rol` rotates bits. Each
exercise's "Key instructions" section defines the ones it needs — you are not expected
to know them in advance.

## Why flags as side-effects matter

Every arithmetic and logical instruction on x86-64 sets some combination of `CF`, `ZF`, `SF`, `OF`, `PF`, and `AF` in `RFLAGS`. Understanding which instruction sets which flag — and which intermediate instructions clobber flags — is essential for writing correct flag-dependent code (overflow detection, conditional branches, `setcc` byte writes).

## Signed vs unsigned distinction

x86-64 stores values in the same registers regardless of signedness. The difference surfaces only in *how you interpret* the flags after a comparison or arithmetic operation:

- **Signed** comparison: `jl`/`jg`/`jle`/`jge` — test `SF`, `OF`, `ZF`.
- **Unsigned** comparison: `jb`/`ja`/`jbe`/`jae` — test `CF`, `ZF`.

Mixing them up produces subtly wrong results when negative numbers are involved.

## Carry vs overflow distinction

- **CF** (carry flag) — unsigned arithmetic overflow; a carry out of or borrow into the most-significant bit.
- **OF** (overflow flag) — *signed* arithmetic overflow; the result cannot be represented in the signed integer range.

`add LONG_MAX, 1` sets `OF` (signed overflow) but not necessarily `CF`. Using the wrong flag means silent data corruption.

## Shipped exercises

- `01-checked-add` ★☆☆ — detect signed overflow with `add` + `seto`; store result via pointer.
- `02-signed-unsigned-cmp` ★☆☆ — three-way signed comparison using `cmp` + `jl`/`jg`; contrast with unsigned `jb`/`ja`.
- `03-bit-ops` ★★☆ — compute `popcnt(x) + left_rotate(x, r)` using the `popcnt` and `rol` instructions.

## Source alignment

See:

- [`../REFERENCE.md`](../REFERENCE.md)
- [`../FLAGS_GUIDE.md`](../FLAGS_GUIDE.md)
- [`../docs/source-map.md`](../docs/source-map.md)

## Competency target

After this part, you should be able to explain the difference between `CF` and `OF`, know which condition codes to use for signed vs unsigned branches, and use `seto`/`setc` to capture flag state into a register without branching.
