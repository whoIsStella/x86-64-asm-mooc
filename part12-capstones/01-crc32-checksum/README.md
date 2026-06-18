# 01 — CRC-32 Checksum

Difficulty: ★★★

Estimated time: 45–75 minutes

## Objective

Implement a C-callable CRC-32 function:

```c
unsigned int crc32(const unsigned char *data, unsigned long len);
```

This is the IEEE 802.3 / zlib CRC-32: polynomial 0xEDB88320 (the reflected
representation of 0x04C11DB7), initial value 0xFFFFFFFF, final XOR 0xFFFFFFFF.

The canonical test vector is:

```
crc32("123456789", 9) == 0xCBF43926
```

## Parts synthesized

| Part | Concept used |
|------|-------------|
| 1 — Registers & Arithmetic | integer registers, shifts, XOR, loop counter |
| 2 — Data Movement / Addressing | byte load with `movzx`, pointer arithmetic |
| 3 — Control Flow | conditional jumps (`jz`, `jb`, `jnz`) |
| 4 — Functions & ABI | SysV AMD64 calling convention, callee-saved registers |
| 5 — Memory & Stack | stack not used heavily but pointer walk is core |
| 6 — Bit Manipulation | `shr`, `and`, `xor`, `not`, `neg` as conditional mask |
| 7 — Loops | byte loop over array, inner 8-iteration unrolled bit loop |

## Algorithm

The reflected CRC-32 algorithm processes each bit from LSB to MSB:

```
crc = 0xFFFFFFFF
for each byte b in data[0..len-1]:
    crc ^= b                   // XOR byte into low 8 bits of accumulator
    for bit in 0..7:
        lsb = crc & 1
        crc >>= 1
        if lsb: crc ^= 0xEDB88320
return crc ^ 0xFFFFFFFF        // final inversion
```

The inner bit loop is unrolled 8 times in the solution using a branchless
conditional-XOR trick:

```asm
mov  edx, ecx          ; copy accumulator
and  edx, 1            ; isolate LSB
neg  edx               ; 1 -> 0xFFFFFFFF,  0 -> 0x00000000
shr  ecx, 1            ; shift accumulator right
and  edx, 0xEDB88320   ; mask: poly if LSB was 1, else 0
xor  ecx, edx          ; conditionally apply polynomial
```

This avoids a conditional branch inside the bit loop while remaining
fully readable.

## ABI

Under the SysV AMD64 ABI:

- `data` arrives in `rdi` (pointer, 64-bit)
- `len` arrives in `rsi` (64-bit unsigned)
- return value (`unsigned int`) goes in `eax`; the upper 32 bits of `rax` are
  automatically zero-extended by any `mov eax, ...` instruction
- Registers `rbx`, `rbp`, `r12`–`r15` are callee-saved; the solution uses only
  `rax`, `rcx`, `rdx`, `rdi`, `rsi`, `r8` (all caller-saved), so no push/pop needed

## What to edit

Edit only:

```
src/crc32.S
```

The test file `tests/test_crc32.c` and header `include/crc32.h` are frozen.

## Commands

```bash
make test    # RED until implemented (stub returns 0)
make solve   # GREEN reference solution
make check   # build both without running
make objdump # inspect reference disassembly
make clean   # remove build/
```

## Pitfalls

- **Wrong init/final XOR**: forgetting `0xFFFFFFFF` init or final XOR produces
  wrong results for all non-empty inputs.  The empty-string case returns 0 because
  `~0xFFFFFFFF == 0x00000000`.
- **AT&T vs Intel syntax**: this repo uses `.intel_syntax noprefix` — operand
  order is `dest, src`, not reversed.
- **32-bit vs 64-bit register**: CRC accumulates in `ecx` (32-bit); using `rcx`
  unintentionally carries garbage in the upper 32 bits.
- **Pointer arithmetic width**: `rdi` and `r8` must be 64-bit for correct address
  comparison; never use `edi` for pointer math.
- **`neg edx` for a 32-bit mask**: `neg` on a 32-bit register produces `0xFFFFFFFF`
  when edx==1 because `-1` in 32-bit two's complement is all ones.  This only works
  reliably if edx contains exactly 0 or 1 before the `neg`.

## Expert review questions

1. **Why does CRC-32 use a reflected polynomial (0xEDB88320) rather than the
   non-reflected form (0x04C11DB7)?**
   Hint: think about the order in which serial data arrives at a hardware shift
   register and which end of the byte is processed first.

2. **The inner bit loop is unrolled 8 times rather than left as a counted loop
   with a branch.  What performance trade-off does this create, and when does
   unrolling make it worse?**

3. **Why is the initial value 0xFFFFFFFF rather than 0x00000000, and why is
   there a final XOR with the same constant?**
   Hint: consider what happens if the input starts with a run of zero bytes.
