# 02 — SIMD memchr (SSE2)

Difficulty: ★★★

Estimated time: 45–75 minutes

## Objective

Implement a C-callable byte-search function using SSE2 vector instructions:

```c
long simd_find_byte(const unsigned char *s, unsigned long n, unsigned char c);
```

Returns the index (0-based) of the first byte equal to `c` in `s[0..n-1]`,
or `-1` if no match is found.

This is the SSE2-accelerated equivalent of `memchr`.

## Parts synthesized

| Part | Concept used |
|------|-------------|
| 1 — Registers & Arithmetic | integer registers, `add`, `sub`, `inc`, `dec` |
| 2 — Data Movement / Addressing | byte load (`movzx`), `movdqu` unaligned vector load |
| 3 — Control Flow | conditional jumps, structured loop |
| 4 — Functions & ABI | SysV AMD64 with integer + pointer arguments |
| 6 — Bit Manipulation | `bsf` (bit scan forward), `test`, `and` on bitmask |
| 8 — SIMD (SSE2) | `movd`, `punpcklbw`, `punpcklwd`, `pshufd`, `pcmpeqb`, `pmovmskb` |

## Algorithm

```
broadcast c into all 16 bytes of xmm1

index = 0
while n >= 16:
    chunk = load_unaligned_16_bytes(s + index)
    mask  = movemask(pcmpeqb(chunk, xmm1))   // 16-bit bitmask of matches
    if mask != 0:
        return index + bsf(mask)             // first set bit = first match
    index += 16
    n     -= 16

// scalar tail: remaining < 16 bytes
for i in 0..n-1:
    if s[index + i] == c:
        return index + i
return -1
```

### Broadcasting a byte into an XMM register

SSE2 has no single "broadcast byte" instruction.  The solution uses four steps:

```asm
movd      xmm1, edx       // xmm1 = [c, 0, 0, ..., 0]
punpcklbw xmm1, xmm1      // xmm1 = [c,c, 0,0, 0,0, 0,0, ...]
punpcklwd xmm1, xmm1      // xmm1 = [c,c,c,c, 0,0,0,0, ...]
pshufd    xmm1, xmm1, 0   // replicate dword 0 -> all 4 dwords
                           // xmm1 = [c,c,c,c, c,c,c,c, c,c,c,c, c,c,c,c]
```

### Why `movdqu` not `movaps`

`movdqu` loads 16 bytes from any address regardless of alignment.
`movaps` requires 16-byte alignment and raises a general-protection fault
(`#GP`) on misaligned addresses.  Because we make no alignment guarantees
about the input pointer, `movdqu` is mandatory.

### `pmovmskb` + `bsf`

`pmovmskb` extracts the most-significant bit of each of the 16 bytes of an
XMM register into a 16-bit integer.  Because `pcmpeqb` sets matching bytes
to `0xFF` (MSB = 1) and non-matching bytes to `0x00` (MSB = 0), the result
is a bitmask where bit `i` is set iff `s[index+i] == c`.

`bsf` (Bit Scan Forward) finds the position of the lowest set bit, giving
the offset of the first match within the 16-byte chunk.

## ABI

Under the SysV AMD64 ABI:

- `s` arrives in `rdi`
- `n` arrives in `rsi`
- `c` arrives in `rdx` (as an `unsigned char`, zero-extended into `edx`)
- return value (`long`) goes in `rax`
- XMM0–XMM7 are caller-saved; XMM8–XMM15 are callee-saved.  The solution
  uses only `xmm0` and `xmm1` (both caller-saved), so no save/restore needed.

## What to edit

Edit only:

```
src/simd_find_byte.S
```

The test file `tests/test_simd_find_byte.c` and header
`include/simd_find_byte.h` are frozen.

## Commands

```bash
make test    # RED until implemented (stub returns -1 always)
make solve   # GREEN reference solution
make check   # build both without running
make objdump # inspect reference disassembly
make clean   # remove build/
```

## Pitfalls

- **Wrong broadcast sequence**: `pshuflw`/`pshufhw` operate on 16-bit words,
  not bytes; using them after a single `punpcklbw` leaves the high 8 bytes as
  zero.  Use `punpcklbw` + `punpcklwd` + `pshufd` to fill all 16 lanes.
- **`movaps` alignment fault**: always use `movdqu` for unaligned input.
- **Forgetting the scalar tail**: if `n` is not a multiple of 16, the last
  `n % 16` bytes are never checked by the vector loop.
- **Index accumulation**: the absolute index returned must account for all
  chunks processed before the match; track a running offset and add it to
  `bsf`'s result.
- **`bsf` undefined on zero input**: only call `bsf` after confirming the mask
  is non-zero with `test eax, eax`.

## Expert review questions

1. **What alignment hazard does `movdqu` avoid compared with `movaps`, and
   under what circumstances would switching to `movaps` be safe and beneficial?**

2. **`pmovmskb` extracts the MSB of each byte.  Since `pcmpeqb` sets matching
   bytes to `0xFF`, the MSB is always 1 for a match.  How would the logic change
   if you used `pcmpeqb` with a register containing `0x01` instead of `0xFF`
   as the "match" sentinel?**

3. **The vector loop processes chunks of exactly 16 bytes and uses a scalar tail
   for the remainder.  An alternative design reads the last partial chunk with
   `movdqu` and masks out out-of-range positions.  What is the risk of reading
   past the end of `s`, and when is the masking approach preferable?**
