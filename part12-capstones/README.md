# Part 12 — Capstones

> Prerequisite: Parts 1–11. These are not new material — they are **synthesis**. Each
> capstone is a real, self-contained program that forces you to combine registers,
> addressing, flags, control flow, the ABI, memory, SIMD, and syscalls into one working
> whole.
>
> **Why care / how it connects:** individual exercises teach one idea in isolation; real
> code never arrives that way. A checksum is a bit-manipulation loop *plus* an ABI
> contract *plus* pointer walking. A fast search is SIMD *plus* a scalar tail *plus*
> bitmask math. A `cat` is a syscall loop *plus* partial-write handling. The capstones
> are where the course stops being drills and starts being programming — and where you
> prove to yourself that the earlier parts actually fused into a skill.

## How a capstone differs from an exercise

Earlier exercises hand you a "How to do it" walkthrough. Capstones deliberately do not.
Instead each one gives you:

- a precise **specification** and a canonical **test vector** (e.g.
  `crc32("123456789", 9) == 0xCBF43926`),
- a **"Parts synthesized"** table naming exactly which earlier parts it draws on — use
  it as a checklist of techniques to reach for,
- an **algorithm** in pseudocode (the *what*, not the line-by-line *how*),
- **pitfalls** and **expert review questions** that probe whether you understand *why*
  the solution is correct, not just that the tests pass.

The reference `solution/` is still there. The intended workflow: attempt it from the
spec and algorithm; consult the pitfalls when stuck; read the solution only to check
your reasoning, then explain to yourself why each instruction is there. If you can
answer the expert review questions, you have mastered the material.

## Shipped capstones

| # | Directory | Entry point | Synthesizes | ★ |
|---|-----------|-------------|-------------|---|
| 01 | `01-crc32-checksum` | `crc32(data, len)` | Parts 1–7: registers, addressing, control flow, ABI, bit ops, loops | ★★★ |
| 02 | `02-simd-memchr` | `simd_find_byte(s, n, c)` | Parts 1–4, 6, 8: SSE2 SIMD, bitmask, `bsf`, scalar tail | ★★★ |
| 03 | `03-raw-cat` | `_start` (freestanding) | Parts 1–3, 9: raw read/write/exit syscall loop, partial writes | ★★☆ |

Pick `03-raw-cat` first if you want the most approachable one; `01` and `02` are the
full ★★★ integration challenges.

## Safety note

These capstones are local, analysis-oriented, and non-networked by design. `raw_cat`
touches only inherited stdin/stdout; no exercise opens sockets or executes a shell
payload. Keep any extensions you write within that boundary.

## Source alignment

See:

- [`../REFERENCE.md`](../REFERENCE.md) — and the specific instruction/syscall references
  each capstone cites in its own README.
- [`../docs/source-map.md`](../docs/source-map.md)
- [`../docs/competency-model.md`](../docs/competency-model.md) — expert-level completion
  criteria the capstones are designed to meet.

## Competency target

After completing the capstones you should be able to take a written specification and a
single test vector and produce correct, ABI-compliant x86-64 assembly that integrates
arithmetic, control flow, memory access, and (where relevant) SIMD or syscalls — and
defend every instruction choice against the expert review questions.
