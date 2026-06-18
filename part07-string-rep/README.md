# Part 7 — String and REP instructions

> Prerequisite: [Part 6](../part06-memory-rip-relative/README.md). You can loop over
> memory by hand. This part introduces instructions that loop over memory *for* you —
> one instruction that copies or scans a whole buffer — plus the one piece of CPU
> state (the direction flag) you must leave tidy when you do.
>
> **Why care / how it connects:** `memcpy`/`strlen`/`memset` are among the most-run
> code on any machine, and the direction-flag rule is a classic real-world ABI bug. The
> Part 12 `cat` capstone is a syscall loop wrapped around exactly these ideas.

x86-64 inherited a family of *string instructions* from the 8086 era.  They
are compact and hardware-optimised for operating on contiguous memory regions,
but they come with an implicit contract: the **direction flag (DF)**.  This
part teaches both the mechanics and the ABI discipline required to use them
safely.

## Why string/REP instructions exist

Before SIMD and before 64-bit wide loads, processors needed an efficient way
to copy, compare, scan, and fill memory one byte (or word, or dword) at a
time.  The x86 architects solved this with a set of one-byte instructions that
implicitly reference a trio of registers:

| Register | Role |
|----------|------|
| `rsi`    | *source* pointer (for `movs`, `cmps`, `lods`) |
| `rdi`    | *destination* pointer (for `movs`, `stos`, `scas`) |
| `rcx`    | repeat count (decremented each iteration) |

Pair any of these with the `rep` (or `repe`/`repne`) prefix and the CPU
executes the operation `rcx` times in a tight hardware loop — no branch
overhead, and often backed by microcode or even special cache-bypass paths.

The direction flag controls whether the pointers advance (`cld`, DF=0) or
retreat (`std`, DF=1) after each step.

## The direction-flag ABI rule

The SysV AMD64 ABI (shared by Linux, macOS, and all major x86-64 platforms)
states:

> **DF must be clear (0) on function entry and on function exit.**

This means:

- Your function may assume DF is clear when it is called.
- If you ever execute `std`, you **must** execute `cld` before `ret`.
- Forgetting `cld` is silent undefined behaviour: the next caller that uses a
  string instruction will walk its pointers *backwards*, silently corrupting
  memory or crashing unpredictably.

## Shipped exercises

- `01-strlen-scasb` ★☆☆ — implement `unsigned long my_strlen(const char *s)`
  using `repne scasb` to scan for a NUL terminator and compute the length.
- `02-memcpy-movsb` ★☆☆ — implement `void my_memcpy(void *dst, const void *src, unsigned long n)`
  using `rep movsb` to copy a byte range.
- `03-direction-flag` ★★☆ — implement `void reverse_copy(unsigned char *dst, const unsigned char *src, unsigned long n)`
  and study why the stub (which calls `std` without a matching `cld`) breaks
  subsequent code; fix it with correct DF discipline.

## Quick reference

```asm
cld              ; DF = 0  (forward: pointers increment)
std              ; DF = 1  (backward: pointers decrement)

rep   movsb      ; copy rcx bytes from [rsi] to [rdi]
rep   stosb      ; fill rcx bytes at [rdi] with al
repe  cmpsb      ; compare while [rsi]==[rdi] and rcx>0
repne scasb      ; scan [rdi] while [rdi]!=al and rcx>0
```

## Source alignment

See:

- [`../REFERENCE.md`](../REFERENCE.md)
- [`../docs/source-map.md`](../docs/source-map.md)

## Competency target

After this part, you should be able to:

- Write a `repne scasb` byte scan and derive the count from the final `rcx`.
- Write a `rep movsb` bulk copy and know why `cld` must precede it.
- Explain the SysV direction-flag rule and demonstrate what happens when it is
  violated.
