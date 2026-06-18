# Part 11 — Debugging, disassembly, and compiler output

> Prerequisite: Parts 1–10. You can *write* assembly. This part teaches the inverse
> and far more common skill: **reading assembly back** — diagnosing a wrong answer,
> stepping through a binary, and understanding what the C compiler produced.
>
> **Why care / how it connects:** this is the part you will actually use for the rest
> of your career. You will read assembly a hundred times for every time you write it —
> to debug an optimized crash, to see why a function is slow, to audit a binary for a
> security flaw, or just to confirm the compiler did what you expected. It ties every
> earlier part together: a bug here is a wrong **flag** (Part 3/4), a broken **ABI**
> contract (Part 5), or a bad **address** (Part 2/6), now seen from the outside.

## The three tools

You do not guess at assembly bugs — you observe them. Three tools, each answering a
different question:

| Tool | Question it answers | Typical command |
|------|--------------------|-----------------|
| **objdump** | "What machine code did this become?" | `objdump -d -M intel build/test_stub` |
| **gdb** | "What are the registers/flags doing *as it runs*?" | `gdb build/test_stub` → `break`, `stepi`, `info registers` |
| **gcc -S** | "What assembly does the compiler emit for this C?" | `gcc -O2 -S -masm=intel file.c` |

### Reading a disassembly (objdump)

`objdump -d -M intel <binary>` prints each function as address, raw bytes, and the
Intel-syntax instruction. `-M intel` is essential — without it you get AT&T syntax.
To see just one function:

```bash
objdump -d -M intel build/test_solution | grep -A 20 '<sum_to_n>:'
```

### Stepping with gdb

gdb runs the program under your control so you can freeze it mid-execution:

```text
(gdb) set disassembly-flavor intel   # show Intel syntax
(gdb) break sum_to_n                  # stop when this function is entered
(gdb) run
(gdb) stepi                           # execute exactly ONE instruction
(gdb) info registers                  # dump every integer register
(gdb) p $rax                          # print one register
(gdb) info registers eflags           # see the flags (ZF, SF, CF, OF…)
```

The loop you will run constantly: `stepi`, then `info registers`, watching a value
until it goes wrong. The instruction *before* it went wrong is your bug.

### Comparing optimization levels (gcc -S)

Compiling the same C at `-O0` and `-O2` shows the compiler's reasoning: `-O0` spills
every variable to the stack and keeps a frame pointer (easy to debug); `-O2` keeps
values in registers, drops the frame, and replaces branches with `cmov`. Reading both
side by side is how the abstract "the compiler optimizes" becomes concrete.

## A disciplined bug hunt

Never patch assembly by guessing. Prove the defect first, with at least one of: a
failing test input, a register value, a flags state, a stack view, or a disassembly
line. (This is the standard in [`../DEBUGGING.md`](../DEBUGGING.md).) Then make the
smallest fix that addresses *that* evidence, and re-run the test.

## Shipped exercises

- `01-fix-the-bug` ★☆☆ — a `sum_to_n` loop with an off-by-one branch (`jge` where it
  should be `jg`). Find it with gdb and objdump, then change one mnemonic.
- `02-disasm-compare` ★★☆ — compile `clamp(x, lo, hi)` at `-O0` and `-O2` and answer
  questions about frame setup, argument registers, branch count, and `cmov`.
- `03-abi-forensic` ★★☆ — a function with two bugs (wrong arithmetic *and* a
  callee-saved register clobbered without push/pop). Diagnose both with objdump and
  write up the findings.

## Source alignment

See:

- [`../DEBUGGING.md`](../DEBUGGING.md) — the gdb/objdump workflow and debugging standard.
- [`../REFERENCE.md`](../REFERENCE.md)
- [`../docs/source-map.md`](../docs/source-map.md)

## Competency target

After this part you should be able to: disassemble a binary in Intel syntax, set a
breakpoint and single-step while watching registers and flags, locate a wrong-branch or
ABI-violation bug from evidence rather than guesswork, and explain the structural
differences between `-O0` and `-O2` compiler output.
