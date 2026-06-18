# Part 5 — Stack frames and SysV ABI

> Prerequisite: [Part 4](../part04-control-flow-condition-codes/README.md). You can
> branch and loop. This part is about what happens when one function *calls* another —
> where local data and saved registers live, and the rules both sides must obey so
> C and assembly can call each other without corrupting anything.
>
> **Why care / how it connects:** the ABI is the contract that lets your hand-written
> assembly coexist with C and the OS. It is also where the scariest bugs live (silent
> corruption). Parts 9–12 all depend on getting it right.

This part teaches why stack frames exist and what the SysV AMD64 ABI contract requires of every C-callable assembly function. Getting the ABI wrong produces subtle corruption bugs that are hard to reproduce because they depend on the caller's register state.

## First: what *is* the stack?

There are only 16 general-purpose registers, but a program has far more values to
remember — especially once functions call other functions. The **stack** is a region
of memory used as scratch space, with one special register, `rsp` (the *stack
pointer*), always holding the address of its top.

It grows **downward**: pushing makes `rsp` *smaller*. Two instructions do the work:

```asm
push rdi      ; rsp -= 8, then store rdi at [rsp]      (put an 8-byte value on top)
pop  rdi      ; load [rsp] into rdi, then rsp += 8      (take the top value back off)
```

It is **LIFO** (last-in, first-out): the last thing you push is the first thing you
pop. That is why save/restore code pops in the *reverse* order it pushed.

Why do you need it? Two reasons, which are the whole point of this part:

1. **Surviving a `call`.** A `call` overwrites registers. If you need a value to still
   be there *after* calling another function, `push` it before the call and `pop` it
   after. (The recursive `factorial` does exactly this with `n`.)
2. **Honouring the contract.** The ABI promises the caller that certain registers come
   back unchanged. If you want to use one of those, you `push` it on entry and `pop` it
   before `ret`. (The `callee-saved` exercise does exactly this.)

`call` itself uses the stack: it pushes the **return address** (where to resume after
the callee finishes) and jumps; `ret` pops that address and jumps back. That single
push is why, on entry to your function, `rsp` is 8 past a 16-byte boundary — the fact
the alignment rule below keeps tripping over.

## Why stack frames and the ABI contract matter

### Stack alignment

The SysV AMD64 ABI requires `rsp` to be **16-byte aligned immediately before a `call` instruction**. A `call` pushes an 8-byte return address, so on entry to a function `rsp % 16 == 8`. If your function calls another function, you must ensure `rsp` is 0 mod 16 at that `call` site — typically by pushing/popping an even number of 8-byte words, or by an explicit `sub rsp, 8` pad.

Violating alignment does not always crash immediately. SSE/AVX instructions that require 16-byte aligned memory (`movaps`, `movdqa`) will fault with `SIGBUS` or `#GP`. Other failures appear as mysteriously wrong values deep in library code.

### Callee-saved register preservation

Registers are divided into two classes:

- **Caller-saved** (`rax`, `rcx`, `rdx`, `rsi`, `rdi`, `r8`–`r11`): the callee is free to overwrite them. The caller must save them before the call if it needs the values afterwards.
- **Callee-saved** (`rbx`, `rbp`, `r12`–`r15`): the callee must restore these to their entry values before returning. C compilers depend on this to hold live variables in registers across function calls.

### Red zone

The SysV ABI defines a **128-byte red zone** — scratch space below `rsp` that the OS will not clobber in a leaf function (a function that makes no further calls). Leaf functions may use it for temporaries without adjusting `rsp`. Exercises in this part do not rely on the red zone.

## Shipped exercises

- `01-factorial-recursive` ★★☆ — recursive `factorial(n)` with push/pop stack alignment at each call site.
- `02-callee-saved` ★★☆ — `sum_with_saved(a, b, c, d)` using `rbx`/`r12` with correct save/restore.
- `03-mixed-args` ★☆☆ — `mixed(a, p, c)` returning `a + *p + c`; integer and pointer arguments in `rdi`/`rsi`/`rdx`.

## Source alignment

See:

- [`../REFERENCE.md`](../REFERENCE.md)
- [`../ABI_NOTES.md`](../ABI_NOTES.md)
- [`../docs/source-map.md`](../docs/source-map.md)

## Competency target

After this part, you should be able to write any ABI-compliant C-callable assembly function: pass arguments, return values, push/pop callee-saved registers, maintain 16-byte stack alignment across `call` instructions, and explain what goes wrong when each rule is violated.
