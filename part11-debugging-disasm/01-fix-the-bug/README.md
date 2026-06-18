# 01 — Fix the Bug

Difficulty: ★☆☆

Estimated time: 30–45 minutes

## Objective

`src/sum_to_n.S` contains a broken implementation of:

```c
long sum_to_n(long n);   /* returns 1 + 2 + ... + n */
```

The function returns the wrong answer.  Your job is to find and fix the bug
using the debugger and disassembler — **not** by reading the source first.

Expected values:

| `n` | `sum_to_n(n)` |
|-----|---------------|
| 0   | 0             |
| 1   | 1             |
| 5   | 15            |
| 10  | 55            |
| 100 | 5050          |

## What to edit

```text
src/sum_to_n.S
```

## Commands

```bash
make test    # RED until you fix the bug
make solve   # GREEN reference solution
make objdump # disassemble the reference binary
```

## Debugging walkthrough

### Step 1 — build and observe the failure

```bash
make test
```

The test output shows which inputs produce wrong answers.  Note them down.

### Step 2 — disassemble the stub

```bash
make          # builds build/test_stub as a side-effect of make test
objdump -d -M intel build/test_stub | grep -A 20 '<sum_to_n>:'
```

Read the branch instructions carefully.  Ask yourself: when does this loop
exit?  Is that the right condition?

### Step 3 — single-step with gdb

```bash
gdb build/test_stub
```

Inside gdb:

```text
(gdb) set disassembly-flavor intel
(gdb) break sum_to_n
(gdb) run
(gdb) disassemble
(gdb) stepi                 # execute one instruction
(gdb) info registers        # inspect all integer registers
(gdb) p $rax                # print accumulator
(gdb) p $rcx                # print counter
(gdb) p $rdi                # print n
```

Repeat `stepi` + `info registers` until you see where the loop exits early.

### Step 4 — identify the bug

The loop counter is in `rcx` and the limit is in `rdi`.  Watch what value
`rcx` holds when the loop exits.  If it exits before `rcx == rdi`, the branch
condition is wrong.

The x86-64 signed-comparison branches:

| mnemonic | meaning          | exits when      |
|----------|------------------|-----------------|
| `jl`     | jump if less     | counter < n     |
| `jle`    | jump if ≤        | counter ≤ n     |
| `jge`    | jump if ≥        | counter ≥ n     |
| `jg`     | jump if greater  | counter > n     |

The loop should run **while** `counter <= n`, meaning it should exit only
when `counter > n`.  Which branch achieves that?

### Step 5 — apply the fix and verify

Edit `src/sum_to_n.S`, change the single branch mnemonic, then:

```bash
make test
```

All five tests should now print `OK`.

## ABI reminder

Under the SysV AMD64 ABI:

- `n` arrives in `rdi`
- return value goes in `rax`
- `rcx` is caller-saved — free to use without push/pop
