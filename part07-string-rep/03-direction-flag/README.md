# 03 — Direction-flag discipline

Difficulty: ★★☆

Estimated time: 25–35 minutes

## Objective

Implement a SysV AMD64 ABI-compatible function:

```c
void reverse_copy(unsigned char *dst, const unsigned char *src, unsigned long n);
```

Copy `n` bytes from `src` to `dst` in forward order (byte 0 first), and
**always** leave the direction flag (DF) clear before returning.

## The direction-flag ABI rule

The SysV AMD64 ABI mandates that DF is **clear on both function entry and
function exit**.  This rule exists because string instructions (`movsb`,
`scasb`, `stosb`, …) consult DF to decide whether to increment or decrement
their pointer registers.  If a callee sets DF with `std` but forgets to
restore it with `cld`, every subsequent string instruction in the caller
(including inside the C standard library) will walk backwards through
memory — silently corrupting data or crashing.

### The buggy pattern (what the stub does)

```asm
std       ; set DF — now pointers decrement
...
ret       ; DF still set — ABI violation!
```

### The correct pattern

```asm
std       ; set DF if needed for a backward operation
...
cld       ; ALWAYS restore DF before returning
ret       ; DF clear — ABI satisfied
```

This exercise implements a straightforward forward copy (`rep movsb` with
`cld`), so `std` is not needed at all.  The stub sets `std` without a
matching `cld`, demonstrating the failure mode.

## ABI reminder

Under the SysV AMD64 ABI:

- `dst` arrives in `rdi`
- `src` arrives in `rsi`
- `n` arrives in `rdx`
- DF **must be clear** (0) when the function returns.

## How to do it

The exercise name is a trap: despite "reverse", the correct copy is a plain *forward*
one — the lesson is that you must not leave `std` in effect. The fix is the same
forward copy as exercise 02:

```asm
reverse_copy:
    mov rcx, rdx          ; count = n
    cld                   ; DF = 0 (forward) — and this is the ABI-required exit state
    rep movsb             ; copy rcx bytes [rsi]→[rdi]
    ret                   ; DF is still 0 → contract honoured
```

The stub fails because it runs `std` (DF = 1) and never clears it, so when the test
harness later calls `memcmp` its string instructions walk backwards and misbehave.
Replacing that with `cld + rep movsb` both does the copy and leaves DF in the state the
caller is promised. Rule to carry forward: **if you ever `std`, you must `cld` before
`ret`.**

## What to edit

Edit only:

```text
src/reverse_copy.S
```

## Commands

```bash
make test    # RED (stub sets std without cld — tests fail)
make solve   # GREEN reference
make check   # build stub and solution
make objdump # inspect reference disassembly
```

## Pitfalls

- The stub sets `std` but never executes a copy and never clears DF.
  Tests fail because `memcmp` in the test harness malfunctions with DF set.
- The fix is simple: use `cld` + `rep movsb` for a correct forward copy,
  and never leave `std` in effect at return.
- If you ever need a backward copy (overlapping regions, memmove-style),
  point `rsi`/`rdi` at the *last* byte of each region before `rep movsb`
  with `std` — then restore DF with `cld` before `ret`.
