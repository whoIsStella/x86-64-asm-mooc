# 02 — Return the input unchanged

Difficulty: ★☆☆

Estimated time: 10–15 minutes

> Second exercise. Builds directly on [`01-return-constant`](../01-return-constant/README.md).

## Objective

Implement a function that takes one argument and returns it untouched — an "echo":

```c
long echo(long x);
```

Under the SysV AMD64 ABI on Linux x86-64:

- the first argument `x` arrives in register `rdi`
- the return value must be left in register `rax`

So the whole job is: **copy `rdi` into `rax`, then `ret`.**

## What to edit

Edit only:

```text
src/echo.S
```

Do not edit the frozen tests.

## How to do it

Exercise 01 used an immediate (`mov rax, 42`). This time the source is another
**register**, not a literal. The `mov` instruction copies register-to-register the
same way:

```asm
mov rax, rdi    # rax = rdi   (rdi is left unchanged; mov copies, it does not move)
```

Remember Intel order: **destination first**. `mov rax, rdi` copies *from* `rdi`
*into* `rax`. Writing `mov rdi, rax` would copy the wrong direction and return
garbage.

## Commands

```bash
make test    # RED until implemented
make solve   # GREEN reference
make check   # build stub and solution
make objdump # inspect reference disassembly
```

## Why this matters

This is the first time you read an **argument**. Every function you write from here
on starts by pulling inputs out of `rdi`, `rsi`, `rdx`, … and ends by leaving the
answer in `rax`. `echo` is that pattern stripped to one move, so the argument and
return registers — and the destination-first order — become muscle memory before
Part 1 asks you to actually compute something.

## Pitfalls

- Reversing the operands: `mov rdi, rax` copies the wrong way.
- Reaching for `rsi`. That holds the *second* argument; `echo` has only one, in
  `rdi`.
- Returning a constant out of habit from exercise 01 — here you must return whatever
  the caller passed in.
