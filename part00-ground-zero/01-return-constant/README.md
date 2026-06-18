# 01 — Return a constant

Difficulty: ★☆☆

Estimated time: 10–15 minutes

> First exercise of the course. If anything here is unfamiliar, read
> [Part 0's lecture](../README.md) first — it explains every line of this file.

## Objective

Implement the simplest possible C-callable assembly function — one that ignores its
(nonexistent) inputs and always hands back the number `42`:

```c
long return_42(void);
```

The contract: leave the answer in the return register `rax`, then `ret`.

## What to edit

Edit only:

```text
src/return_42.S
```

The boilerplate directives (`.intel_syntax noprefix`, `.text`, `.globl`, …) are
already written for you. You only change the two instruction lines inside the
function. Do not edit the frozen tests.

## How to do it

You need exactly two instructions:

1. Put the immediate `42` into `rax`. (Look at the `mov rax, 42` row in the Part 0
   instruction table.)
2. `ret`.

The stub currently does `mov rax, 0` — that is why the test starts RED. Change the
`0` to `42`.

## Commands

```bash
make test    # RED until implemented
make solve   # GREEN reference
make check   # build stub and solution
make objdump # inspect reference disassembly
```

## Why this matters

Before you can move data, branch, or call functions, you must be fluent in the
absolute basics: an instruction has a verb and operands, a function returns through
`rax`, and `ret` ends it. This exercise isolates exactly that — nothing else can go
wrong, so when it goes green you know the toolchain and your mental model both work.

## Pitfalls

- Writing the operands backwards. In Intel syntax `mov rax, 42` means `rax = 42`;
  the destination is **first**. `mov 42, rax` is meaningless (you cannot store into
  a literal).
- Forgetting `ret`. Without it the CPU keeps executing past your function into
  whatever bytes follow — undefined behavior.
- Returning the value in some other register. The caller only reads `rax`.
