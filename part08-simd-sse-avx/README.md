# Part 8 — SIMD/SSE/AVX foundations

> Prerequisite: [Part 6](../part06-memory-rip-relative/README.md). Everything so far
> processed one value per instruction. This part introduces a *second* set of
> registers that hold several values at once, and instructions that act on all of
> them in a single step.
>
> **Mental model — lanes.** Picture a 128-bit `xmm` register as a row of slots
> ("lanes"): 4 floats, or 16 bytes, or 2 doubles side by side. A "packed" instruction
> like `addps` runs the *same* operation on every lane in parallel — 4 additions for
> the price of one. The `ps`/`pd`/`b` suffix tells you how the row is sliced. That is
> the whole idea of SIMD; the rest of this part is which instruction slices which way.
>
> **Why care / how it connects:** SIMD is where most real-world performance comes from
> — video/audio codecs, machine learning, image processing, fast text parsing. It
> reuses Part 6's memory loads and Part 3's `popcnt`; the Part 12 `memchr` capstone is
> built directly on this part.

Modern x86-64 CPUs contain a second register file of 128-bit (XMM) or 256-bit
(YMM) registers that can hold multiple integer, float, or double values packed
side by side. A single instruction operates on *all lanes simultaneously* —
this is **SIMD** (Single Instruction, Multiple Data). It is the mechanism behind
fast video codecs, signal processing, database scans, and vectorised math
libraries.

## Why SIMD exists

A 128-bit XMM register holds:

- **16 bytes** (int8 / uint8)
- **8 words** (int16 / uint16)
- **4 doublewords** (int32 / float)
- **2 quadwords** (int64 / double)

One `addps` instruction adds all four float lanes in the same number of cycles
as one scalar `addss` — a 4× throughput gain for free, once the data is laid
out correctly.

## SSE vs AVX

| Feature | SSE / SSE2 | AVX / AVX2 |
|---|---|---|
| Register width | 128-bit (XMM) | 256-bit (YMM), 512-bit (ZMM with AVX-512) |
| Encoding | Legacy (REX prefix) | VEX-encoded (three-operand, non-destructive) |
| Availability | Baseline on x86-64 | Requires CPUID check or compile-time target |
| Instruction prefix | `movups`, `addps` | `vmovups`, `vaddps` |

All exercises in this part use SSE2 (`movups`, `addps`, `movdqu`, `pcmpeqb`,
`addpd`), which is **guaranteed available** on every x86-64 CPU. No CPUID check
is needed.

## The AVX/SSE transition hazard and `vzeroupper`

When mixing AVX (VEX-encoded, YMM) code with legacy SSE code in the same
process, the CPU must save and restore the upper 128 bits of each YMM register.
If AVX code leaves the upper bits in an "unknown" (dirty) state and then calls
an SSE function, Intel CPUs can suffer a **False Upper Dirty** stall — a
hundreds-of-cycle penalty per call.

The fix is `vzeroupper`: it zeroes the upper 128 bits of all YMM registers,
signalling to the CPU that the transition is clean.

```asm
vzeroupper          ; call before leaving AVX code that called SSE code
```

Rule of thumb: always emit `vzeroupper` before a `ret` or a call to an
external function in any function that uses YMM registers. The compiler
(`-mavx2`) does this automatically; hand-written AVX assembly must do it
explicitly.

These exercises use SSE2 only (XMM registers), so `vzeroupper` is not needed
here — but you will need it the moment you graduate to AVX/AVX2 code.

## Alignment: `movups` / `movdqu` vs `movaps` / `movdqa`

| Instruction | Data type | Alignment required |
|---|---|---|
| `movups` | packed float | none (unaligned) |
| `movaps` | packed float | 16-byte |
| `movdqu` | 128-bit integer | none (unaligned) |
| `movdqa` | 128-bit integer | 16-byte |

Using `movaps` or `movdqa` on a non-aligned address raises a **General
Protection fault** (`#GP`) at runtime. When you control the allocation (e.g.
`_Alignas(16)` in C, or `.balign 16` in assembly), `movaps` is slightly more
efficient. For general-purpose library code that cannot guarantee caller
alignment, always use `movups` / `movdqu`.

## Shipped exercises

- `01-vector-add4` ★☆☆ — add four packed single-precision floats with `movups`/`addps`/`movups`.
- `02-packed-byte-eq` ★★☆ — count equal byte positions in two 16-byte arrays with `movdqu`/`pcmpeqb`/`pmovmskb`/`popcnt`.
- `03-sum4-doubles` ★★☆ — sum four packed doubles with `movupd`/`addpd` and a `movhlps`/`addsd` horizontal reduction.

## Source alignment

See:

- [`../REFERENCE.md`](../REFERENCE.md)
- [`../docs/source-map.md`](../docs/source-map.md)

## Competency target

After this part you should be able to:

- load and store packed data with unaligned SSE instructions
- select the right packed instruction suffix (`ps` = packed float, `pd` = packed
  double, `b`/`w`/`d`/`q` = integer byte/word/dword/qword)
- perform a 4→1 horizontal reduction using `addpd` + `movhlps` + `addsd`
- explain why `vzeroupper` is required when returning from AVX code to SSE callers
- explain the alignment contract for `movaps` vs `movups`
