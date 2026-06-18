# 01 — Byte scan

Difficulty: ★☆☆

Estimated time: 25–35 minutes

## Objective

Implement a SysV AMD64 ABI-compatible function:

```c
long find_byte(const unsigned char *s, unsigned long n, unsigned char target);
```

Scan the first `n` bytes of buffer `s`. Return the **index** of the first byte equal
to `target`, or `-1` if none match. For `n == 0`, return `-1`.

## ABI reminder

Under the SysV AMD64 ABI:

- `s` (pointer) arrives in `rdi`
- `n` (unsigned long) arrives in `rsi`
- `target` (one byte) arrives in `rdx` — the byte is in its low 8 bits, `dl`
- return value goes in `rax`

## How to do it

This is the Part 4 counted loop, but the elements are single **bytes**, so the scale
is 1 and you load with a byte-sized access. Compare each byte to `target` and return
the index on the first hit:

```asm
    xor rcx, rcx                  ; i = 0
.Lloop:
    cmp rcx, rsi                  ; i < n ?
    jge .Lnot_found               ; ran off the end → not found
    movzx eax, byte ptr [rdi + rcx]  ; load s[i] (1 byte, zero-extended)
    cmp al, dl                    ; compare it to target (both are bytes)
    je  .Lfound
    inc rcx
    jmp .Lloop
.Lfound:
    mov rax, rcx                  ; return the index
    ret
.Lnot_found:
    mov rax, -1
    ret
```

`[rdi + rcx]` has no `*scale` because bytes are 1 apart. `byte ptr` tells the
assembler to read exactly one byte; comparing `al` to `dl` compares the two low bytes.

## What to edit

Edit only:

```text
src/byte_scan.S
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

- Compare bytes to bytes: `cmp al, dl`, not `cmp rax, rdx` (the upper bits of `rdx`
  are not part of the byte argument).
- Test `i < n` **before** the load so an empty buffer never dereferences `s`.
- The stub already returns `-1`, so the "miss" tests pass before you start — that is
  expected; the "hit" tests are what start RED.
