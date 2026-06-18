# 01 — LEA scaled add

Difficulty: ★☆☆

Estimated time: 25–35 minutes

## Objective

Implement a SysV AMD64 ABI-compatible function:

```c
long lea_scale_add(long base, long index);
```

Return:

```text
base + index * 8 + 16
```

Use `lea` in the reference mental model: it computes an effective address expression and writes the arithmetic result without loading memory and without modifying condition flags.

## ABI reminder

Under the SysV AMD64 ABI:

- `base` arrives in `rdi`
- `index` arrives in `rsi`
- return value goes in `rax`

## How to do it

The address-formula from the lecture *is* the arithmetic you want. Map it onto the
argument registers:

```text
base + index*8 + 16   →   [rdi + rsi*8 + 16]
 │       │      │
 rdi     rsi    displacement
```

So the body is one instruction plus the return:

```asm
lea rax, [rdi + rsi*8 + 16]   ; rax = rdi + rsi*8 + 16  (arithmetic — no memory load)
ret
```

`lea` evaluates the bracket and writes the resulting *number* into `rax`; it does
**not** read memory at that address. Replace the stub's `xor rax, rax` (which just
sets `rax = 0`) with the `lea`, then `make test`.

## What to edit

Edit only:

```text
src/lea_scale_add.S
```

## Commands

```bash
make test    # RED until implemented
make solve   # GREEN reference
make check   # build stub and solution
make objdump # inspect reference disassembly
```

## Pitfalls

- `lea` does not dereference memory.
- x86 scaled-index addressing supports scale factors 1, 2, 4, and 8.
- `lea rax, [rdi + rsi*8 + 16]` is arithmetic here, not a load from memory.
