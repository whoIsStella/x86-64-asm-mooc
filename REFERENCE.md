# x86-64 Assembly Course Reference Corpus

This is the source-of-truth documentation index for `x86-64-asm-mooc`.

Last checked from this workspace: 2026-06-16.

## Trust model

Use sources in this order:

1. Intel/AMD architecture manuals for instruction and architectural semantics.
2. AMD64 System V ABI for C-callable function behavior.
3. GNU/binutils/NASM docs for assembler and object tooling behavior.
4. Linux man pages/kernel syscall references for Linux syscall ABI.
5. Course-owned notes for distilled teaching explanations.

Do not infer ABI rules from compiler output alone. Do not teach Linux syscall conventions as C function calling conventions. Do not ship exploit payloads as default-runnable coursework.

## Primary architecture references

### Intel Software Developer Manuals

- URL: https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html
- Publisher: Intel
- Access check: simple Python URL fetch received HTTP 403 on 2026-06-16; access via browser/manual download may still work.
- Use for: instruction semantics, flags, memory ordering, system instructions, SIMD details.

### AMD64 Architecture Programmer's Manual

- Publisher: AMD
- Use for: AMD64 architectural behavior, long mode, instructions, system programming context.

## ABI references

### AMD64 System V ABI

- URL: https://gitlab.com/x86-psABIs/x86-64-ABI
- Publisher: x86-64 psABI maintainers
- Access check: HTTP 200 on 2026-06-16
- Use for: argument registers, return values, stack alignment, red zone, callee-saved registers, ELF object ABI.

## Assembler and toolchain references

### GNU assembler / binutils

- URL: https://sourceware.org/binutils/docs/as/
- Access check: HTTP 200 on 2026-06-16
- Use for: GAS Intel/AT&T syntax, directives, labels, `.globl`, `.type`, objdump behavior.

### NASM documentation

- URL: https://www.nasm.us/doc/
- Access check: HTTP 200 on 2026-06-16
- Use for: Intel syntax comparison and future NASM-backed exercises.

### GCC documentation

- URL: https://gcc.gnu.org/onlinedocs/
- Use for: compiling C harnesses, generated assembly (`-S`), inline assembly constraints.

### GDB documentation

- URL: https://sourceware.org/gdb/documentation/
- Use for: register inspection, disassembly, stepping, flags, stack frames.

## Linux syscall references

- Linux man-pages: https://man7.org/linux/man-pages/
- Linux syscall tables from kernel/user ABI references.
- Use for: `syscall` number/argument conventions, return values, `write`, `exit`, `read`.

## Course-owned distilled references

- `SYNTAX_ROSETTA.md` — Intel and AT&T syntax comparison.
- `ABI_NOTES.md` — SysV AMD64 ABI essentials.
- `FLAGS_GUIDE.md` — condition flags and signed/unsigned reasoning.
- `SYSCALLS.md` — Linux syscall ABI notes.
- `DEBUGGING.md` — gdb/objdump workflow.
- `docs/source-map.md` — part-to-source mapping.
- `docs/competency-model.md` — expert outcomes.
