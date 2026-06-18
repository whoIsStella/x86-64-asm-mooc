# 03 — Sum a static array

Difficulty: ★★☆

Estimated time: 30–45 minutes

## Objective

Implement a SysV AMD64 ABI-compatible function that takes **no arguments** and sums a
fixed array you define in the assembly source itself:

```c
long sum_static(void);
```

The array is `{10, 20, 30, 40, 50}`, so the answer is always `150`.

## ABI reminder

Under the SysV AMD64 ABI:

- no arguments
- return value goes in `rax`

## How to do it

Declare the array in `.rodata` and mark both its start and its end with labels — the
two labels let you loop with a pointer until you reach the end, no length needed:

```asm
.section .rodata
.align 8
static_array:
    .quad 10, 20, 30, 40, 50   ; five 8-byte longs
static_array_end:              ; address just past the last element
.text
```

Then walk a pointer from start to end, accumulating:

```asm
sum_static:
    lea rdi, [rip + static_array]       ; rdi = current element pointer
    lea rsi, [rip + static_array_end]   ; rsi = one-past-the-end
    xor rax, rax                        ; sum = 0
.Lloop:
    cmp rdi, rsi                        ; reached the end?
    jge .Ldone
    add rax, qword ptr [rdi]            ; sum += *rdi  (8-byte load)
    add rdi, 8                          ; advance to the next long
    jmp .Lloop
.Ldone:
    ret
```

This is a **pointer-sentinel loop**: instead of counting indices, you compare the
moving pointer against the end address. Each step adds the 8-byte value the pointer
addresses, then moves the pointer forward by 8 (the size of one `long`).

## What to edit

Edit only:

```text
src/sum_static.S
```

Do not edit the frozen tests.

## Commands

```bash
make test    # RED until implemented
make solve   # GREEN reference
make check   # build stub and solution
make objdump # inspect reference disassembly
```

## Pitfalls

- Advance the pointer by `8`, not `1` — the elements are 8-byte `long`s.
- Use `qword ptr [rdi]` (or just `[rdi]` with a 64-bit destination) so the load is
  8 bytes wide.
- Both `lea [rip + …]` lines are needed: one for the start pointer, one for the
  end sentinel.
