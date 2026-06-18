# 01 — Factorial recursive

Difficulty: ★★☆

Estimated time: 35–50 minutes

## Objective

Implement a SysV AMD64 ABI-compatible function:

```c
long factorial(long n);
```

Return `n!` computed **recursively** in assembly. For n ≤ 1 return 1.

## ABI reminder

Under the SysV AMD64 ABI:

- `n` arrives in `rdi`
- return value goes in `rax`
- On entry to a function `rsp % 16 == 8` (the `call` instruction pushed an 8-byte return address)
- Before any `call` instruction, `rsp` must be **16-byte aligned** (i.e. `rsp % 16 == 0`)

## Stack alignment recipe for a recursive call

```
; Entry: rsp % 16 == 8  (one return address on stack)
push rdi        ; save n — rsp now 0 mod 16
sub  rsp, 8     ; alignment pad  — rsp still 0 mod 16
; ... set up rdi for the recursive call ...
call factorial  ; call pushes 8-byte return address → callee sees rsp%16==8  ✓
add  rsp, 8     ; remove pad
pop  rdi        ; restore n
```

## How to do it

A recursive function needs two things: a **base case** that stops the recursion, and
a **recursive case** that calls itself on a smaller input. The wrinkle in assembly is
that the recursive `call` will overwrite `rdi`, so you must save `n` on the stack
across the call — and keep the stack 16-byte aligned while doing it (see the recipe
above).

```asm
factorial:
    cmp rdi, 1
    jle .Lbase          ; if n <= 1, answer is 1

    push rdi            ; save n across the call (rsp: 8→0 mod 16)
    sub  rsp, 8         ; pad so rsp is 16-aligned at the call site
    lea  rdi, [rdi - 1] ; argument for the recursive call: n - 1
    call factorial      ; rax = factorial(n - 1)
    add  rsp, 8         ; undo the pad
    pop  rdi            ; restore our n

    imul rax, rdi       ; rax = n * factorial(n - 1)
    ret
.Lbase:
    mov rax, 1
    ret
```

Walk the stack math: on entry `rsp % 16 == 8`. `push rdi` makes it `0`; `sub rsp, 8`
keeps it `0` — which is exactly the alignment the ABI requires *at a `call`*. After
the call you reverse both: `add rsp, 8` then `pop rdi`. `lea rdi, [rdi-1]` is just the
Part 2 trick for `rdi = rdi - 1` (it leaves the flags from `cmp` untouched, though
that does not matter here). `imul` is the signed multiply.

## What to edit

Edit only:

```text
src/factorial_recursive.S
```

## Commands

```bash
make test    # RED until implemented
make solve   # GREEN reference
make check   # build stub and solution
make objdump # inspect reference disassembly
```

## Pitfalls

- Forgetting to restore `rdi` after the recursive call clobbers `n`.
- Off-by-one in the base case: `factorial(0)` must return 1, not 0.
- Stack misalignment: each `push` or `pop` moves `rsp` by 8; count carefully.
- Using `mul` instead of `imul`: `mul` has a two-operand implicit form; `imul reg, reg` is cleaner.
