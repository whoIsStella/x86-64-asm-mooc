# 01 — strlen with repne scasb

Difficulty: ★☆☆

Estimated time: 20–30 minutes

## Objective

Implement a SysV AMD64 ABI-compatible function:

```c
unsigned long my_strlen(const char *s);
```

Return the number of bytes before the first NUL terminator (`'\0'`), identical
to the C standard `strlen`.

Use the `repne scasb` string scan idiom:

1. `cld` — clear the direction flag (DF=0, forward scan).
2. Load `rdi` with the string pointer (it is already there from the call).
3. Set `al` = 0 (the NUL byte to search for).
4. Set `rcx` = a large sentinel (use `-1` = `0xFFFFFFFFFFFFFFFF`).
5. Execute `repne scasb` — it decrements `rcx` and advances `rdi` for each
   byte scanned, stopping when `[rdi] == al`.
6. Compute the length from `rcx`:
   - iterations consumed = `length + 1` (length chars plus the NUL)
   - `rcx_after` = `rcx_init − (length + 1)`
   - `not rcx_after` = `length + 1`
   - `length` = `(not rcx_after) − 1`

## ABI reminder

Under the SysV AMD64 ABI:

- `s` arrives in `rdi`
- return value goes in `rax`
- `rcx` and `rdi` are caller-saved (scratch); you may clobber them.

## How to do it

The whole function, assembled from the steps above:

```asm
my_strlen:
    cld                   ; forward scan (DF = 0)
    xor eax, eax          ; al = 0, the NUL byte we're looking for
    mov rcx, -1           ; rcx = 0xFFFF...FF, a huge countdown sentinel
    repne scasb           ; while [rdi] != al and rcx != 0: rdi++, rcx--
    not rcx               ; rcx = length + 1
    lea rax, [rcx - 1]    ; rax = length
    ret
```

`repne scasb` = "repeat while not equal, scan byte": it walks `rdi` forward comparing
each byte to `al`, decrementing `rcx` every step, and stops at the NUL. Because `rcx`
started at `-1` and counted down once per byte (including the NUL), `not rcx` recovers
"length + 1"; subtract 1 for the answer. `lea rax, [rcx - 1]` is just the Part 2 way to
write `rax = rcx - 1`.

## What to edit

Edit only:

```text
src/my_strlen.S
```

## Commands

```bash
make test    # RED until implemented
make solve   # GREEN reference
make check   # build stub and solution
make objdump # inspect reference disassembly
```

## Pitfalls

- `repne scasb` advances `rdi` past the NUL byte — the final `rdi` value is
  one byte past the NUL, not pointing at it.
- `rcx` holds the remaining count *after* scanning; invert it (bitwise NOT)
  and subtract 1 to get the byte count before the NUL.
- Always `cld` before a string instruction.  The SysV ABI guarantees DF is
  clear on entry, but being explicit is a good habit.
