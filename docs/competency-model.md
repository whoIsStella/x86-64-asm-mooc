# x86-64 Assembly Competency Model

This file defines the skills covered by `x86-64-asm-mooc`.

## Expected skills at completion

A learner who completes this course should be able to:

- Read and write x86-64 assembly in Intel and AT&T syntax.
- Distinguish architectural rules from ABI, assembler, linker, OS, and debugger behavior.
- Write SysV AMD64 ABI-compliant functions callable from C.
- Preserve stack alignment and callee-saved registers.
- Reason about flags, signed/unsigned comparisons, overflow, and carry.
- Use addressing modes and RIP-relative data access correctly.
- Write small Linux syscall programs without confusing syscall and C ABIs.
- Use gdb and objdump to prove what code does.
- Understand SIMD foundations and common transition/performance hazards.
- Audit assembly for ABI violations, clobber bugs, stack bugs, unsafe syscall assumptions, and exploit-adjacent misuse.

## Competency levels

### Level 1: Instruction operator

Can write simple register arithmetic and pass a C harness.

### Level 2: ABI-safe assembly programmer

Can write C-callable functions, preserve registers, align the stack, and debug failures with disassembly.

### Level 3: Systems assembly engineer

Can combine stack frames, memory addressing, syscalls, SIMD, and inline asm with correct boundaries.

### Level 4: Advanced practitioner

Can audit and repair assembly for correctness, portability, ABI safety, and security-sensitive misuse.

## Part-by-part competencies

### Part 1: Architecture, registers, and syntax

Learner can:

- Identify general-purpose registers and ABI argument/return registers.
- Write a minimal C-callable function.
- Explain GAS Intel syntax vs NASM Intel syntax vs AT&T syntax.

Evidence:

- `01-add-two` solution passes and disassembles to a minimal implementation.

### Part 2: Data movement and addressing

Learner can:

- Use `mov`, extension moves, and `lea` correctly.
- Explain partial-register and 32-bit zero-extension effects.
- Use base/index/scale/displacement addressing.

Evidence:

- `01-lea-scale-add` solution uses `lea` to compute `base + index * 8 + 16` and passes signed test cases.

### Part 3: Arithmetic, flags, and bit manipulation

Learner can:

- Predict flag effects.
- Choose signed vs unsigned condition codes.
- Implement overflow-aware helpers.

### Part 4: Control flow and condition codes

Learner can:

- Build loops and branches.
- Use `cmov`/`setcc` where appropriate.
- Debug branch decisions through flags.

### Part 5: Stack frames and SysV ABI

Learner can:

- Maintain 16-byte stack alignment at call boundaries.
- Preserve callee-saved registers.
- Use recursion and local stack storage safely.

### Part 6: Memory layout and RIP-relative addressing

Learner can:

- Access constants/tables position-independently.
- Reason about stack/static/text sections at a practical level.

### Part 7: String and REP instructions

Learner can:

- Use string instructions with correct direction-flag assumptions.
- Avoid unbounded copy/scan bugs.

### Part 8: SIMD/SSE/AVX foundations

Learner can:

- Use XMM/YMM registers for basic packed operations.
- Explain ABI and transition caveats.

### Part 9: Linux syscalls and minimal ELF programs

Learner can:

- Write raw syscall programs.
- Explain syscall register conventions and clobbers.
- Handle negative error returns where relevant.

### Part 10: Inline assembly in C

Learner can:

- Write GCC extended asm with correct constraints and clobbers.
- Identify missing `memory` clobber hazards.

### Part 11: Debugging, disassembly, and compiler output

Learner can:

- Use gdb/objdump evidence to diagnose defects.
- Compare compiler output across optimization levels.

### Part 12: Capstones

Learner can synthesize the course into:

- C-callable optimized routines
- SIMD scanners
- no-libc syscall utilities
- reverse-engineering reports grounded in disassembly

## Review questions

1. Is this behavior architectural, ABI-defined, assembler-specific, OS-specific, or debugger-specific?
2. Which registers does this function have to preserve?
3. Is `rsp` aligned before this call?
4. Which flags does this instruction read or write?
5. Is this comparison signed or unsigned?
6. Is this addressing mode accessing the intended object?
7. Does this code accidentally depend on the red zone?
8. Is this a C ABI call or a Linux syscall?
9. What does objdump prove about the actual machine code?
10. Could this exercise be misused offensively, and has it been safely scoped?

## Completion gate

Do not mark this course complete until:

- Parts 1–12 have source-cited lectures.
- Every shipped exercise has red stub, frozen test, green solution, and Makefile.
- `make check-all` and `make solve-all` pass.
- Syntax, ABI, syscall, and debugging docs are present.
- Exploit-adjacent content is local-only and non-default-runnable.
