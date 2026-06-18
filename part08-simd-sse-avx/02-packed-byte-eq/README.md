# 02 — Packed byte equality count

Difficulty: ★★☆

Estimated time: 25–40 minutes

## Objective

Implement a SysV AMD64 ABI-compatible function:

```c
int count_equal_bytes(const unsigned char *a, const unsigned char *b);
```

Compare exactly 16 bytes of `a` and `b` in parallel using SSE2 and return the
number of positions where they are equal.

## ABI reminder

Under the SysV AMD64 ABI:

- `a` arrives in `rdi`
- `b` arrives in `rsi`
- return value (int) goes in `rax` (or `eax` — writing `eax` zero-extends to
  `rax` automatically)

## Key instructions

| Instruction | Operation |
|---|---|
| `movdqu xmm0, [rdi]` | Load 16 bytes unaligned into xmm0 |
| `pcmpeqb xmm0, xmm1` | Per-byte equality: each byte becomes `0xFF` if equal, `0x00` if not |
| `pmovmskb eax, xmm0` | Build a 16-bit integer: bit *i* is set iff byte *i* of xmm0 has its MSB set |
| `popcnt eax, eax` | Count the number of set bits in eax |

### Why this works

`pcmpeqb` sets every equal byte to `0xFF`, so its MSB (bit 7) is always 1 for
equal bytes and 0 for unequal bytes. `pmovmskb` collects those 16 MSBs into a
plain 16-bit integer. `popcnt` then counts how many bits are set, which equals
the number of equal positions.

## How to do it

The trick is turning "16 parallel comparisons" into a single count. `pcmpeqb` does all
16 byte-compares at once, producing `0xFF` (all bits set) where equal; `pmovmskb`
gathers the top bit of each of those 16 bytes into a 16-bit number; `popcnt` counts the
1s:

```asm
count_equal_bytes:
    movdqu  xmm0, [rdi]    ; 16 bytes of a
    movdqu  xmm1, [rsi]    ; 16 bytes of b
    pcmpeqb xmm0, xmm1     ; each lane: 0xFF if a[i]==b[i], else 0x00
    pmovmskb eax, xmm0     ; eax bit i = (lane i was 0xFF)  → a 16-bit mask
    popcnt  eax, eax       ; eax = number of 1 bits = number of equal positions
    ret
```

Note `pmovmskb` writes to a *general-purpose* register (`eax`), crossing back from the
vector world to ordinary integers — that is what lets `popcnt` finish the job. `movdqu`
is the integer-flavoured 16-byte load (use it, not `movups`, for byte data).

## What to edit

Edit only:

```text
src/packed_byte_eq.S
```

## Commands

```bash
make test    # RED until implemented
make solve   # GREEN reference
make check   # build stub and solution
make objdump # inspect reference disassembly
```

## Pitfalls

- `movdqu` (integer) vs `movups` (float): both move 16 unaligned bytes, but use
  `movdqu` for integer data — it avoids domain-crossing penalties on older CPUs.
- `pmovmskb` writes to a *general-purpose* register (`eax`), not an XMM register.
- `popcnt` requires SSE4.2 on the assembler command line (`-mpopcnt` for GCC),
  but the GAS assembler accepts it by default on x86-64 targets because the
  POPCNT feature flag is separate from SSE.
