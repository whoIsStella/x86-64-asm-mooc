# x86-64 Course Source Map

This map ties each part to authoritative documentation. If course code or prose contradicts these sources, fix the course.

Last reviewed: 2026-06-16.

## Part 0 — Ground Zero

Exercises:

- `part00-ground-zero/01-return-constant`
- `part00-ground-zero/02-return-input`

Primary sources:

- AMD64 System V ABI: integer argument register `rdi`, `rax` return value.
- GNU assembler docs: `.intel_syntax noprefix`, `.text`, `.globl`, `.type`, `.size`,
  labels.
- Intel/AMD manuals: general-purpose register model, `mov`, `ret`.

Correctness notes:

- Pedagogical on-ramp for learners with no prior assembly. Must not assume any
  vocabulary; every directive and instruction used is explained in the part lecture.
- Keep exercises to a single computational instruction so the only new thing being
  tested is the toolchain/register/return model, not problem-solving.

## Part 1 — Architecture, registers, and syntax

Exercises:

- `part01-architecture-registers/01-add-two`

Primary sources:

- AMD64 System V ABI: integer argument registers and `rax` return value.
- GNU assembler docs: `.intel_syntax noprefix`, directives, ELF symbol metadata.
- Intel/AMD manuals: general-purpose register model.

Correctness notes:

- `rdi`/`rsi` argument usage is ABI-defined, not purely architectural.
- GAS Intel syntax is not NASM syntax; the syntax rosetta must keep these separate.

## Part 2 — Data movement and addressing

Exercises:

- `part02-data-movement-addressing/01-lea-scale-add`

Primary sources:

- Intel/AMD manuals: `mov`, `movsx`, `movzx`, `lea`, addressing modes.
- GNU assembler docs: memory operand syntax.

Required coverage:

- zero-extension from 32-bit destination writes
- signed/zero extension
- scaled indexed addressing
- RIP-relative addressing

## Part 3 — Arithmetic, flags, and bit manipulation

Primary sources:

- Intel/AMD manuals: arithmetic/logic instructions and flags.
- AMD64 ABI for function boundaries.

Required coverage:

- carry vs overflow
- signed vs unsigned comparisons
- shifts/rotates and count masking
- bit test/manipulation instructions

## Part 4 — Control flow and condition codes

Primary sources:

- Intel/AMD manuals: `jmp`, `jcc`, `cmp`, `test`, `cmov`, `setcc`.
- GDB docs for flags inspection.

## Part 5 — Stack frames and SysV ABI

Primary sources:

- AMD64 System V ABI.
- GDB documentation.

Required coverage:

- stack alignment before calls
- red zone
- caller/callee-saved registers
- recursion and frame layout

## Part 6 — Memory layout and RIP-relative addressing

Primary sources:

- AMD64 ABI: ELF and relocation basics.
- GNU binutils docs.
- Intel/AMD manuals for addressing semantics.

## Part 7 — String and REP instructions

Primary sources:

- Intel/AMD manuals: string instructions, direction flag, REP prefixes.

Required coverage:

- direction flag hygiene
- bounded copy/scan behavior
- performance caveats as secondary, not normative

## Part 8 — SIMD/SSE/AVX foundations

Primary sources:

- Intel/AMD manuals: XMM/YMM registers and SSE/AVX instructions.
- AMD64 ABI: vector register ABI rules.

## Part 9 — Linux syscalls and minimal ELF programs

Primary sources:

- Linux syscall ABI references and man pages.
- AMD64 ABI for ELF object context.

Correctness notes:

- `syscall` clobbers `rcx` and `r11`.
- syscall args use `rdi`, `rsi`, `rdx`, `r10`, `r8`, `r9`, not the C ABI fourth arg register `rcx`.

## Part 10 — Inline assembly in C

Primary sources:

- GCC extended asm documentation.
- Clang docs if Clang support is added.

Required coverage:

- constraints
- clobbers
- `volatile`
- `memory` clobber

## Part 11 — Debugging, disassembly, and compiler output

Lecture: `part11-debugging-disasm/README.md`

Primary sources:

- GDB docs.
- GNU objdump/binutils docs.
- GCC generated assembly docs/options.

## Part 12 — Capstones

Lecture: `part12-capstones/README.md`

Primary sources:

- All prior sources.
- SIMD and syscall capstones must cite the specific instruction/API references they depend on.

Safety note:

- Shellcode-adjacent content must be local, analysis-oriented, and non-networked. No default exercise should launch a shell payload.
