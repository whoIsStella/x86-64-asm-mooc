# Part 10 — Inline Assembly in C

**Prerequisite:** Part 5 (Stack frames and SysV ABI)

**Estimated time:** 6 hours

> Instead of a separate `.S` file, this part drops assembly *inside* a C function with
> GCC's `asm(...)` syntax. The new skill is the **constraint string** — how you tell the
> compiler which C variables your assembly reads, writes, and disturbs.
>
> **Why care / how it connects:** this is the seam most real projects actually use
> assembly through — one hot instruction (an atomic, a `cpuid`, a vector op) without
> leaving C. Getting a constraint wrong is a top source of "impossible" miscompilation
> bugs, so it sharpens your sense of the ABI from Part 5 from the other side.

---

## Why inline assembly?

Writing a standalone `.S` file and linking it is clean, but sometimes you want
to drop a single instruction — or a short sequence — directly into a C function
without leaving the translation unit. GCC's *extended inline assembly* syntax
lets you do exactly that while giving the compiler full visibility of which
registers you read, which you write, and which architectural state (condition
codes, memory) your snippet may disturb.

Getting the constraint string wrong is one of the most common sources of
mysterious miscompilation. The exercises here are designed so that a single
wrong constraint or a missing clobber produces a **deterministically wrong
answer**, making the failure obvious.

---

## GCC extended asm — a minimal reference

```c
asm [volatile] ( "template"
                 : output-operands
                 : input-operands
                 : clobbers );
```

### Constraint letters (64-bit integer)

| Letter | Meaning |
|--------|---------|
| `r`    | any general-purpose register |
| `q`    | register usable as byte (`al`, `bl`, `cl`, `dl`, `sil`, `dil`, …) |
| `m`    | memory operand |
| `i`    | immediate integer constant |

### Output-operand modifiers

| Prefix | Meaning |
|--------|---------|
| `=`    | write-only output |
| `+`    | read-write operand |
| `&`    | early-clobber (written before inputs are consumed) |

### Tying: `"0"`, `"1"`, …

Tying an input to output `%0` (for example) tells GCC to place the input in
the **same register** as output 0. Use this when the instruction reads and then
overwrites the same register (e.g. `addq %1, %0`).

### Clobber entries

- `"cc"` — your snippet modifies `EFLAGS` (almost any arithmetic instruction
  does; omitting this is safe only when GCC knows the instruction can't affect
  flags, which is rare).
- `"memory"` — your snippet reads or writes memory that the compiler doesn't
  know about through the explicit operands. This acts as a compiler barrier:
  the compiler will not reorder memory accesses across the `asm` boundary and
  will not keep stale values in registers.

---

## Exercises

| # | Exercise | Concept | Difficulty |
|---|----------|---------|------------|
| 01 | `add_inline` | Basic constraint syntax, tied operands | ★☆☆ |
| 02 | `times3_via_lea` | LEA in inline asm, recognising when output is unused | ★★☆ |
| 03 | `negate_all` | `"+m"` memory operand, `"cc"` clobber, `asm volatile` | ★★☆ |

---

## Building

Each sub-directory has its own `Makefile`:

```bash
make test    # compile stub + run (RED by design)
make solve   # compile solution + run (GREEN)
make check   # compile both, show pass/fail for each
make clean   # remove build/
```
