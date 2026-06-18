# Part 1 — Architecture, registers, and syntax

> Prerequisite: [Part 0 — Ground Zero](../part00-ground-zero/README.md). Part 0
> teaches what a register, instruction, operand, and `.S` file are, from nothing,
> and has you write two single-instruction functions. Part 1 assumes you have done
> it: you already know that arguments arrive in `rdi`/`rsi`, results leave in `rax`,
> `mov` copies destination-first, and `ret` ends a function.
>
> **Why care / how it connects:** this is the C↔assembly contract — arguments in
> fixed registers, result in `rax`. Every single later part obeys it; get it wrong and
> nothing links or runs.

This part introduces x86-64 as a contract between four layers: architecture,
assembler, ABI, and C harness.

The CPU gives you registers and instructions (Part 0). The assembler gives you syntax and object files. The SysV AMD64 ABI tells C and assembly how to call each other. Confusing those layers is the fastest way to write assembly that works once and fails everywhere else.

Where Part 0's `echo` copied one argument straight to `rax`, Part 1's `add_two`
reads *two* arguments and combines them — the first function that actually computes.

## Shipped exercises

- `01-add-two` ★☆☆ — first C-callable x86-64 assembly function.

## Source alignment

See:

- [`../REFERENCE.md`](../REFERENCE.md)
- [`../ABI_NOTES.md`](../ABI_NOTES.md)
- [`../SYNTAX_ROSETTA.md`](../SYNTAX_ROSETTA.md)
- [`../docs/source-map.md`](../docs/source-map.md)
