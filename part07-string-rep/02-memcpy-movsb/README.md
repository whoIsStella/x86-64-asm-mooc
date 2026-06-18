# 02 — memcpy with rep movsb

Difficulty: ★☆☆

Estimated time: 20–30 minutes

## Objective

Implement a SysV AMD64 ABI-compatible function:

```c
void my_memcpy(void *dst, const void *src, unsigned long n);
```

Copy exactly `n` bytes from `src` to `dst`.  The regions must not overlap
(matching the C standard `memcpy` contract).

Use the `rep movsb` string copy idiom:

1. `cld` — clear the direction flag (DF=0, forward copy).
2. Move `rdx` (n) into `rcx` — `rep movsb` uses `rcx` as the count.
3. Execute `rep movsb` — copies one byte per iteration from `[rsi]` to
   `[rdi]`, then increments both pointers and decrements `rcx`, stopping
   when `rcx` reaches zero.

## ABI reminder

Under the SysV AMD64 ABI:

- `dst` arrives in `rdi`
- `src` arrives in `rsi`
- `n` arrives in `rdx`
- `movsb` implicitly reads/writes `rsi`, `rdi`, and `rcx` — all
  caller-saved; you may clobber them.

## How to do it

`rep movsb` is a one-instruction copy loop, but it has fixed register roles: it copies
from `[rsi]` to `[rdi]`, `rcx` times. Your job is just to put the count where it
expects it and clear the direction flag:

```asm
my_memcpy:
    mov rcx, rdx          ; rep movsb counts in rcx, but n arrived in rdx
    cld                   ; DF = 0, so both pointers advance forward
    rep movsb             ; copy rcx bytes [rsi]→[rdi], rsi++/rdi++/rcx-- each step
    ret
```

`rsi` and `rdi` already hold `src` and `dst` from the call, so you don't move them.
When `rcx` reaches 0 the copy stops — and if `n` was 0 it does nothing, which is
exactly the required behaviour. No `std` here, so DF stays clear and the ABI is happy.

## What to edit

Edit only:

```text
src/my_memcpy.S
```

## Commands

```bash
make test    # RED until implemented
make solve   # GREEN reference
make check   # build stub and solution
make objdump # inspect reference disassembly
```

## Pitfalls

- `rep movsb` uses `rcx` for the count, but `n` arrives in `rdx`.
  Don't forget `mov rcx, rdx`.
- Copying 0 bytes must be a no-op; `rep movsb` handles this correctly
  (when `rcx=0` it performs zero iterations).
- The direction flag must be clear (DF=0) for forward copy; always `cld`
  before `rep movsb`.
