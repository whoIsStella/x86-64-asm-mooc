# 03 — Mixed integer and pointer arguments

Difficulty: ★☆☆

Estimated time: 20–30 minutes

## Objective

Implement a SysV AMD64 ABI-compatible function:

```c
long mixed(long a, long *p, long c);
```

Return `a + *p + c`.

`p` is a **pointer to a `long`**. You must dereference it with a memory load instruction to read the value it points to.

## ABI reminder

Under the SysV AMD64 ABI:

- `a` arrives in `rdi` (integer argument)
- `p` arrives in `rsi` (pointer argument — treated as an integer-class register, holding an address)
- `c` arrives in `rdx` (integer argument)
- return value goes in `rax`

Integer and pointer arguments share the same registers; the distinction is in how you **use** the register.

## Dereferencing a pointer in Intel syntax

```asm
mov rax, [rsi]   ; load the 8-byte value at the address contained in rsi
```

Square brackets mean "dereference" — read or write the memory at that address.

## How to do it

The only new idea is dereferencing the pointer `p`. Load `*p` first, then add the two
plain integer arguments:

```asm
    mov rax, [rsi]     ; rax = *p   (rsi holds the address; brackets read the long there)
    add rax, rdi       ; rax = *p + a
    add rax, rdx       ; rax = *p + a + c
    ret
```

The single most important distinction in this whole part: `mov rax, rsi` would copy
the *address* into `rax`; `mov rax, [rsi]` copies the *value stored at* that address.
The brackets are the dereference. After that it is just two adds.

## What to edit

Edit only:

```text
src/mixed.S
```

## Commands

```bash
make test    # RED until implemented
make solve   # GREEN reference
make check   # build stub and solution
make objdump # inspect reference disassembly
```

## Pitfalls

- `mov rax, rsi` copies the **address** — it does NOT load the value.
- `mov rax, [rsi]` loads the **value at that address** — this is what you want.
- Use `QWORD PTR` or just `[rsi]` for 8-byte (64-bit) loads in Intel syntax with GAS.
