# 03 — ABI Forensic

Difficulty: ★★☆

Estimated time: 45–60 minutes

## Objective

`src/broken.S` contains a function with **two bugs**:

1. It computes the wrong answer.
2. It violates the SysV AMD64 ABI by clobbering a callee-saved register.

```c
/* Should return a*2 + b */
long broken_abi(long a, long b);
```

Your job is to diagnose both bugs using `objdump`, then fill in `report.md`.

## Commands

```bash
make test    # RED — wrong values (expected)
make solve   # GREEN — fixed version passes + report.md complete
make objdump # disassemble the broken binary
make clean
```

## Workflow

### Step 1 — observe the failure

```bash
make test
```

The test output shows which inputs return wrong values.  For example,
`broken_abi(3, 4)` should return 10 (`3*2 + 4`) but returns something else.

### Step 2 — disassemble the broken function

```bash
make          # builds build/test_broken
make objdump
```

Or manually:

```bash
objdump -d -M intel build/test_broken | grep -A 15 '<broken_abi>:'
```

Read each instruction:

1. What register is written first?
2. Is that register callee-saved?
3. Was it pushed on the stack before being written?
4. What arithmetic is performed?  Does it match `a*2 + b`?

### Step 3 — understand callee-saved registers

The SysV AMD64 ABI divides integer registers into two groups:

| Caller-saved (scratch) | Callee-saved (preserved) |
|------------------------|--------------------------|
| rax, rcx, rdx          | rbx, rbp, r12–r15        |
| rsi, rdi, r8, r9       |                          |
| r10, r11               |                          |

A function **may** use callee-saved registers freely, but it **must** restore
them to their original values before returning.  The canonical pattern is:

```asm
push rbx        ; save
...             ; use rbx freely
pop  rbx        ; restore
ret
```

If a function writes `rbx` without pushing it first, any caller that stored a
live value in `rbx` will silently get the wrong data back — a notoriously
hard-to-debug ABI violation.

### Step 4 — identify the arithmetic bug

The function should compute `a*2 + b`.  Doubling `a` can be done as:

```asm
add  rdi, rdi    ; rdi = a + a = a*2  (no extra register needed)
```

or:

```asm
lea  rax, [rdi + rdi]   ; rax = a*2
```

Look at what the broken version actually computes and describe the error in
`report.md`.

### Step 5 — read the reference fix

```bash
cat solution/fixed.S
```

Compare it instruction-by-instruction with `src/broken.S`.

### Step 6 — fill in report.md

Open `report.md` and replace every `TODO` with your findings.  When no TODOs
remain, `make solve` will succeed.

## ABI reminder

- Arguments: `a` in `rdi`, `b` in `rsi`
- Return value: `rax`
- Callee-saved: `rbx`, `rbp`, `r12`, `r13`, `r14`, `r15`
- A missing `push`/`pop` around a callee-saved register is an ABI violation.
