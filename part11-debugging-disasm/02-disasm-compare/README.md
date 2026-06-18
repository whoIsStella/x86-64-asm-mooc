# 02 — Disassembly compare

Difficulty: ★★☆

Estimated time: 30–45 minutes

## Objective

Compile `reference.c` at two optimisation levels and read the generated
assembly to understand what the compiler does to a simple three-argument
function.

```c
int clamp(int x, int lo, int hi);
```

## Commands

```bash
make solve   # compile at -O0 and -O2, assert -O2 output is shorter
make test    # GREEN once you have removed all TODO markers from notes.md
make clean
```

## Workflow

### Step 1 — generate the assembly

```bash
make solve
```

This produces:

```text
build/clamp_O0.s   — unoptimised
build/clamp_O2.s   — optimised
```

### Step 2 — read the unoptimised output

```bash
less build/clamp_O0.s
```

Observe:

- The prologue: `push rbp` / `mov rbp, rsp` (frame setup).
- The three integer arguments arrive in `edi`, `esi`, `edx` per the SysV
  AMD64 calling convention.  GCC spills them to stack locals right away at
  `-O0` (because it does not perform register allocation without `-O`).
- Two conditional branches implement the two `if` statements.
- The epilogue: `pop rbp` / `ret`.

### Step 3 — read the optimised output

```bash
less build/clamp_O2.s
```

Observe:

- No frame setup (the function uses no stack space at all).
- Arguments stay in registers throughout.
- Branches may be replaced by `cmov` (conditional-move) instructions, which
  avoid branch misprediction penalties.
- The function body is much shorter.

### Step 4 — count the difference

```bash
wc -l build/clamp_O0.s build/clamp_O2.s
```

### Step 5 — answer the questions in notes.md

Open `notes.md` and replace each `TODO` with your observations.  When every
TODO is gone, `make test` will pass.

## Key concepts

### Calling convention (SysV AMD64)

Integer/pointer arguments arrive in order: `rdi`, `rsi`, `rdx`, `rcx`, `r8`,
`r9`.  For 32-bit `int` parameters the compiler uses the 32-bit aliases
`edi`, `esi`, `edx` and zero-extends to 64 bits automatically.

### Stack frame

At `-O0` GCC always creates a frame pointer (`push rbp` / `mov rbp, rsp`) to
support debugger backtraces.  At `-O2` it omits this unless the function
actually needs stack space (e.g. for local arrays or `alloca`).

### cmov — conditional move

`cmovl eax, esi` means "copy `esi` into `eax` if the last comparison found
less-than (signed)".  It performs the same logical operation as a branch but
without the pipeline flush that a mispredicted jump would cause.

### Why -O2 is shorter

`-O0` inserts loads and stores for every C variable to make stepping through
the source in gdb predictable.  `-O2` keeps everything in registers and folds
away redundant instructions.
