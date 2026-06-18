# 02 — clobber-bughunt: times3_via_lea

Difficulty: ★★☆

Estimated time: 25–35 minutes

## Objective

Implement the function declared in `include/times3_via_lea.h`:

```c
long times3_via_lea(long x);
```

Return `x * 3` using the `leaq` instruction inside GCC extended inline
assembly.  **No multiplication instruction is allowed** — use the scaled-index
addressing mode that `lea` provides.

## The instruction

```asm
leaq (%rSRC, %rSRC, 2), %rDST    ; dst = src + src*2 = src*3
```

In GCC constraint syntax:

```c
asm("leaq (%1,%1,2), %0"
    : "=r"(result)
    : "r"(x)
    );
```

Note: unlike `addq`, `leaq` does **not** modify `EFLAGS`, so no `"cc"` entry
is needed in the clobber list.  The `=r` / `r` pair is sufficient because `lea`
writes a fresh result to a destination register without reading it first — the
input and output may safely be in different registers.

## The bug in the stub

Open `src/times3_via_lea.c`.  The `asm` statement is **syntactically correct**
and the operands are **properly constrained**, yet the function always returns
the wrong answer.

Find the bug:

1. Look at what the `asm` writes into.
2. Look at what the `return` statement actually returns.

The asm output is computed but then thrown away — a classic "dead variable"
bug that the compiler does not warn about because the variable *is* used (the
asm writes to it), just not returned.

## How to do it

The `asm` itself is already correct — this is a *reading* exercise, not a writing one.
Open `src/times3_via_lea.c` and trace two things: the variable the `asm` writes its
result into, and the variable the function actually `return`s. They differ — the
computed value is dropped on the floor and a literal `0` (or an unrelated variable) is
returned instead.

The fix is to return the value the `asm` produced. A correct version looks like:

```c
long times3_via_lea(long x)
{
    long result;
    asm("leaq (%1,%1,2), %0"    /* result = x + x*2 = x*3 */
        : "=r"(result)          /* lea writes a fresh value, so write-only "=r" is right */
        : "r"(x));              /* no "cc": lea does not touch the flags */
    return result;              /* ← return the computed result, not 0 */
}
```

Note this one *does* use `"=r"` (unlike exercise 01): `lea` does not read its
destination, so there is nothing to preserve going in. The lesson is that a perfectly
valid `asm` is still useless if the surrounding C throws its output away.

## What to edit

```text
src/times3_via_lea.c
```

Fix the function so it returns the value computed by the `asm`.

## Commands

```bash
make test    # RED (stub always returns 0)
make solve   # GREEN
make check   # both
```

## Pitfalls

- The `"r"` constraint on the input and `"=r"` on the output allocate
  independent registers for `lea`.  **Do not** use a tied operand (`"0"`)
  here — unlike `add`, `lea` writes a new value without reading the destination.
- Forgetting to `return result;` (returning `0` or an uninitialised variable
  instead) is exactly the bug this exercise demonstrates.
- `leaq` computes an *address expression* arithmetically.  Scale factors 1, 2,
  4, and 8 are the only values the encoding supports.  For ×3 use
  `(%reg, %reg, 2)` — base + index×2.
