# 01 — add_inline

Difficulty: ★☆☆

Estimated time: 20–30 minutes

## Objective

Implement the function declared in `include/add_inline.h`:

```c
long add_inline(long a, long b);
```

Return `a + b` using **GCC extended inline assembly**.  A plain `return a + b;`
defeats the purpose — the point is to write the `asm(...)` statement yourself.

## Constraints to use

```c
long result = a;
asm("addq %1, %0"
    : "+r"(result)   /* read-write: loaded with a before, holds a+b after */
    : "r"(b)         /* input: b in any GP register                        */
    : "cc"           /* addq modifies EFLAGS                               */
    );
```

### Why `"+r"` instead of `"=r"`?

`addq src, dst` **reads and overwrites** `dst`.  Using `"=r"` (write-only)
would tell GCC that the output register is unread by the asm, so GCC is free
to not initialise it before the instruction runs — the old value of `result`
(which we need to be `a`) would be garbage.

The `"+"` modifier means *read-write*: GCC loads the operand into a register
before the asm executes and reads it back afterwards.  We initialise
`result = a` so the register already contains `a` when `addq` runs:

```
  reg = a           ; GCC loads result (which equals a) into a register
  addq %1, %0       ; reg += b  →  reg holds a+b
  result = reg      ; GCC stores the register back to result
```

### Alternative: tied operand

The same effect can be achieved with a tied input:

```c
long result;
asm("addq %2, %0" : "=r"(result) : "0"(a), "r"(b) : "cc");
```

Here operand numbering is: `%0` = result (output), `%1` = a tied to `%0`
(same register), `%2` = b.  The template uses `%2` (b), not `%1`, to add
into `%0` (the a/result register).  Both forms are correct; `"+r"` is more
idiomatic.

## How to do it

Put the whole thing together: initialise `result = a`, then one `asm` that adds `b`
into it. The complete function body:

```c
long add_inline(long a, long b)
{
    long result = a;            /* the register will start holding a   */
    asm("addq %1, %0"           /* %0 = result (dst), %1 = b (src)     */
        : "+r"(result)          /* read-write: GCC loads a, reads back a+b */
        : "r"(b)                /* input b in any register             */
        : "cc");                /* addq changes the flags              */
    return result;
}
```

The key choice is `"+r"`, not `"=r"`: `addq` *reads* its destination before writing,
so the register must already contain `a` when the instruction runs. `"+"` means
read-write and makes GCC load `result` (= `a`) in first; `"=r"` (write-only) would let
GCC skip that load and add `b` to garbage. `%0`/`%1` are numbered in the order the
operands appear (output first).

## What to edit

```text
src/add_inline.c
```

## Commands

```bash
make test    # RED until implemented
make solve   # GREEN reference
make check   # build and run both
```

## Pitfalls

- Using `"=r"(result)` without initialising the output first (e.g. without
  the `"+r"` modifier or a tie) means `addq` adds `b` into an uninitialised
  register — wrong result.
- `"addq %1, %0"` with `"=r"(result)`, `"0"(a)`, `"r"(b)` uses `%1` which
  is the *tied alias* of `%0` — adding the register to itself (doubling `a`)
  rather than adding `b`.  Use `"+r"` or `"addq %2, %0"` with a tied operand.
- Forgetting `volatile` is fine here because the asm has an output operand —
  GCC will not elide it.  Use `asm volatile` only when the asm has side effects
  not captured by its operands (e.g., it modifies memory or flags without
  declaring them).
