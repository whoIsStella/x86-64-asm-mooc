# 03 — memory-clobber: negate_all

Difficulty: ★★☆

Estimated time: 30–40 minutes

## Objective

Implement the function declared in `include/negate_all.h`:

```c
void negate_all(long *arr, long n);
```

Negate every element of `arr` in-place — i.e. `arr[i] = -arr[i]` for all `i`
in `[0, n)` — using the `negq` instruction inside GCC extended inline assembly.

## Key concepts

### `"+m"` — read-write memory operand

`negq` reads the value, negates it, and writes the result back to the same
memory location.  The `+m` constraint tells GCC:

- `m` — the operand lives in memory (not a register).
- `+` — the operand is both read *and* written.

This is different from `"=m"` (write-only) or just `"m"` (read-only input).

```c
asm volatile ("negq %0" : "+m"(arr[i]) : : "cc");
```

### `"cc"` — EFLAGS clobber

`negq` sets the carry flag (CF=1 if operand is non-zero), zero flag, sign
flag, overflow flag, and parity flag.  Declaring `"cc"` tells GCC that your
asm snippet may have modified `EFLAGS`, so it won't reuse a condition code
result that was computed before the `asm`.

### `asm volatile` — preventing elimination

When an `asm` statement has no output operands, GCC may decide it is a
no-op and delete it.  `volatile` prevents that.  Here we *do* have an output
(the `"+m"` operand), so `volatile` is technically optional — but it is good
practice for any asm that writes to memory.

### Why not `"memory"` clobber?

Adding `"memory"` to the clobber list tells GCC: *all memory may have
changed*.  That is a heavier hammer — it acts as a full compiler barrier and
forces the compiler to reload every cached variable from memory after the asm.

Using `"+m"(arr[i])` is more precise: only `arr[i]` is declared as modified.
The compiler can keep other cached values in registers.  Both approaches are
correct; `"+m"` is preferred when the scope of the memory write is known.

## What to edit

```text
src/negate_all.c
```

The stub does nothing — it returns without modifying the array.  Implement
the function with a C loop that applies an inline-asm `negq` to each element.

## How to do it

Loop in C; let one inline `asm` negate each element *in place* in memory:

```c
void negate_all(long *arr, long n)
{
    for (long i = 0; i < n; i++) {
        asm volatile ("negq %0"     /* arr[i] = -arr[i] */
                      : "+m"(arr[i]) /* +m: a memory operand that is read AND written */
                      :              /* (no separate inputs)                          */
                      : "cc");       /* negq changes the flags                        */
    }
}
```

The new idea is the `"+m"` constraint: `m` means the operand *is* the memory location
`arr[i]` (no register copy), and `+` means `negq` both reads and writes it — which is
exactly what an in-place negate does. `"=m"` (write-only) would be wrong because `negq`
needs the original value to negate. The C `for` loop supplies the iteration; the `asm`
supplies the one instruction.

## Commands

```bash
make test    # RED (stub leaves array unchanged)
make solve   # GREEN
make check   # both
```

## Pitfalls

- Using `"=m"` (write-only) instead of `"+m"` (read-write) causes `negq` to
  negate an uninitialised value — wrong result.
- Forgetting `"cc"` is not fatal at `-O0` but becomes an issue at higher
  optimisation levels where GCC reuses EFLAGS across statements.
- Calling `negq` via a register constraint (`"=r"` / `"r"`) and then storing
  back works too, but is more verbose and moves the value through an extra
  register unnecessarily.
