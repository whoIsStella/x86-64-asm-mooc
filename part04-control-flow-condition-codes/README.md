# Part 4 — Control flow and condition codes

> Prerequisite: [Part 3](../part03-arithmetic-flags-bits/README.md). You know that
> `cmp` sets flags. This part *acts* on those flags: conditional jumps (`jcc`) to build
> `if`/`while`/`for`, and conditional moves (`cmov`) to avoid branching entirely.
>
> **Why care / how it connects:** this is how `if`/`while`/`for`/`switch` actually
> exist at the machine level. Every loop in Parts 6–12 — array scans, copy loops,
> syscall loops — is built from the jumps you learn here.

Every `if`, `while`, `for`, and `switch` in C compiles down to a handful of condition-setting instructions followed by conditional branches. This part makes that mapping explicit: you write the branches yourself, read the condition-code flags directly, and discover where the compiler's choices for branchless code come from.

A `label:` is simply a name for a position in the code; a jump like `jl .Lless`
transfers control there when its condition holds. That is the entire machinery of
loops and branches — there is no `if` keyword, only "set flags, then jump on them".

## Why condition codes matter

x86-64 arithmetic instructions (`add`, `sub`, `cmp`, `test`, `inc`, …) leave a 6-bit summary of the result in `RFLAGS`:

| Flag | Meaning |
|------|---------|
| ZF | Result was zero |
| SF | Result was negative (sign bit set) |
| CF | Unsigned carry/borrow out of the top bit |
| OF | Signed overflow (result did not fit) |
| PF | Parity of the low byte |
| AF | Auxiliary carry (BCD; ignore for now) |

Conditional jumps (`jz`, `jnz`, `jl`, `jge`, `jb`, `jae`, …) and conditional moves (`cmovg`, `cmovle`, …) test combinations of these flags. Because flags are set as a side-effect of ordinary arithmetic, a good assembly programmer avoids redundant `cmp` / `test` instructions by reading the flags left by the preceding operation.

## Branchless vs. branchy code

Modern CPUs are pipelined: a mispredicted branch flushes the pipeline and can cost 15–20 cycles. The compiler often avoids branches entirely for short computations:

```c
// C: return a > b ? a : b;
// Compiler output (branchless):
//   mov  rax, rsi
//   cmp  rdi, rsi
//   cmovg rax, rdi
```

A `cmov` ("conditional move") is an ordinary data-flow instruction with no branch prediction cost. Use it whenever the two paths are short and data-independent. Use a branch (`jcc`) when one path is rarely taken (branch predictor wins) or when the two paths are long enough that the fall-through path saves significant work.

## Shipped exercises

- `01-branchless-max` ★☆☆ — `long imax(long a, long b)` using `cmp` + `cmovg`; no jumps allowed.
- `02-array-sum-loop` ★☆☆ — `long array_sum(const long *a, unsigned long n)` using a counted loop; `cmp` index to `n`, `jae` to exit.
- `03-classify-sign` ★☆☆ — `int classify(long x)` returning -1/0/1 via a `jl`/`je`/fall-through ladder.

## Source alignment

See:

- [`../REFERENCE.md`](../REFERENCE.md)
- [`../FLAGS_GUIDE.md`](../FLAGS_GUIDE.md)
- [`../docs/source-map.md`](../docs/source-map.md)

## Competency target

After this part, you should be able to:

1. Read a `RFLAGS` state and predict which `jcc` / `cmovcc` conditions fire.
2. Rewrite a simple `if/else` max into branchless form using `cmov`.
3. Write a loop that correctly handles `n == 0` without special-casing the body.
4. Explain the performance tradeoff between `cmov` and predicted branches.
