# 02 — Callee-saved registers

Difficulty: ★★☆

Estimated time: 30–40 minutes

## Objective

Implement a SysV AMD64 ABI-compatible function:

```c
long sum_with_saved(long a, long b, long c, long d);
```

Return `a + b + c + d`. You **must** move the arguments into callee-saved registers (`rbx`, `r12`–`r15`) and correctly **save** them at entry and **restore** them before returning.

## ABI reminder

Under the SysV AMD64 ABI:

- `a` arrives in `rdi`, `b` in `rsi`, `c` in `rdx`, `d` in `rcx`
- return value goes in `rax`
- **Callee-saved registers**: `rbx`, `rbp`, `r12`, `r13`, `r14`, `r15`
  - If your function modifies these, it must save and restore them.
  - The C harness (and test framework) relies on this contract being upheld.

## Save/restore pattern

```asm
sum_with_saved:
    push rbx        ; save callee-saved register
    push r12        ; save callee-saved register
    ; ... use rbx and r12 freely ...
    pop r12         ; restore in REVERSE push order
    pop rbx
    ret
```

Note: two `push` instructions from an entry state of `rsp % 16 == 8` leaves `rsp % 16 == 8` again (even number of pushes), so alignment is maintained.

## How to do it

The exercise *requires* you to use the callee-saved registers `rbx` and `r12`, which
means you must hand them back to the caller exactly as you found them. The shape is
always the same: push what you'll use at entry, do the work, pop in reverse order
before `ret`.

```asm
sum_with_saved:
    push rbx            ; save caller's rbx
    push r12            ; save caller's r12  (two pushes ⇒ stack stays aligned)

    mov rbx, rdi        ; rbx = a
    mov r12, rsi        ; r12 = b
    add rbx, r12        ; rbx = a + b
    add rbx, rdx        ; rbx = a + b + c
    add rbx, rcx        ; rbx = a + b + c + d
    mov rax, rbx        ; return value in rax

    pop r12             ; restore in REVERSE order (stack is last-in-first-out)
    pop rbx
    ret
```

The pop order is the reverse of the push order because the stack is LIFO — the last
value pushed sits on top and must come off first. Two pushes from the entry state
(`rsp % 16 == 8`) leave it back at `8`, so alignment is preserved with no extra pad.
(You don't actually *need* callee-saved registers to add four numbers — this exercise
forces them so you practise the save/restore contract.)

## What to edit

Edit only:

```text
src/sum_with_saved.S
```

## Commands

```bash
make test    # RED until implemented
make solve   # GREEN reference
make check   # build stub and solution
make objdump # inspect reference disassembly
```

## Pitfalls

- Pop order must be the reverse of push order — a stack is LIFO.
- Using `rax`, `rcx`, `rdx`, `rsi`, `rdi`, `r8`–`r11` (caller-saved) for intermediate values is fine *without* saving them, but you would lose the original argument values.
- Forgetting to restore a callee-saved register is undefined behaviour visible as corrupted variables in the C caller.
