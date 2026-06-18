# 02 — RIP-relative table lookup

Difficulty: ★★☆

Estimated time: 30–45 minutes

## Objective

Implement a SysV AMD64 ABI-compatible function backed by a constant table you define
in the same `.S` file:

```c
int weekday_len(int day);   /* Mon=0 .. Sun=6 */
```

Return the length of the weekday name for `day` (Monday→6, Tuesday→7, Wednesday→9,
Thursday→8, Friday→6, Saturday→8, Sunday→6). Return `-1` for any `day` outside `0..6`.

## ABI reminder

Under the SysV AMD64 ABI:

- `day` (an `int`) arrives in `edi`
- return value (an `int`) goes in `eax`

## How to do it

Two phases: declare a constant table in `.rodata`, then bounds-check and index it via
a RIP-relative address.

First, the data (above or below your function, in the data section):

```asm
.section .rodata
.align 4
weekday_lengths:
    .int 6, 7, 9, 8, 6, 8, 6   ; seven 4-byte ints, one per weekday
.text
```

Then the code:

```asm
weekday_len:
    cmp edi, 0
    jl  .Lout_of_range         ; day < 0
    cmp edi, 6
    jg  .Lout_of_range         ; day > 6
    lea rax, [rip + weekday_lengths]      ; rax = runtime address of the table
    movsx eax, dword ptr [rax + rdi*4]    ; eax = table[day] (4-byte int, sign-extended)
    ret
.Lout_of_range:
    mov eax, -1
    ret
```

The `lea [rip + weekday_lengths]` gets the table's address in a way that stays correct
no matter where the program loads. Then `[rax + rdi*4]` is the scaled-index form from
Part 2 — element `day` of an array of 4-byte ints. Bounds-check **before** you index,
or an out-of-range `day` reads past the table.

## What to edit

Edit only:

```text
src/rip_table_lookup.S
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

- Forgetting the bounds check: `weekday_len(7)` and `weekday_len(-1)` must return `-1`,
  not whatever bytes follow (or precede) the table.
- Scale must match the element size: the table is `.int` (4 bytes), so index with
  `rdi*4`. If you made it `.quad`, you would use `rdi*8`.
- You need the full 64-bit `rax` to hold the address from `lea`, even though `day` and
  the result are 32-bit.
