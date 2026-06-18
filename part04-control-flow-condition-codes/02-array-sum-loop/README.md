# 02 — Array sum loop

Difficulty: ★☆☆

Estimated time: 25–35 minutes

## Objective

Implement a SysV AMD64 ABI-compatible function:

```c
long array_sum(const long *a, unsigned long n);
```

Return the sum of the first `n` elements of the array `a`. When `n == 0` return `0`.

Use a **counted loop**: maintain an index in a register, compare it to `n` before (or after) each iteration, and branch back with a conditional jump while the condition holds.

## ABI reminder

Under the SysV AMD64 ABI:

- `a` (pointer) arrives in `rdi`
- `n` (unsigned long) arrives in `rsi`
- return value goes in `rax`

## How to do it

A counted loop needs three registers: an accumulator for the running sum, an index
`i`, and the inputs (`rdi` = array, `rsi` = n). Check `i < n` **at the top** so that
`n == 0` skips the body entirely:

```asm
    xor rax, rax        ; sum = 0   (this is the return value)
    xor rcx, rcx        ; i = 0
.Lloop:
    cmp rcx, rsi        ; compare i to n
    jae .Ldone          ; if i >= n (unsigned), we're finished
    mov r8, [rdi + rcx*8]   ; load a[i]  — element i of an 8-byte-per-element array
    add rax, r8         ; sum += a[i]
    inc rcx             ; i++
    jmp .Lloop          ; back to the test
.Ldone:
    ret
```

Two things make this correct: the test is **before** the load (so an empty array
never dereferences anything), and the comparison is **unsigned** (`jae`) because `n`
is `unsigned long`. The address `[rdi + rcx*8]` is the scaled-index form from Part 2 —
it picks element `rcx` of an array of 8-byte longs.

## What to edit

Edit only:

```text
src/array_sum_loop.S
```

## Commands

```bash
make test    # RED until implemented
make solve   # GREEN reference
make check   # build stub and solution
make objdump # inspect reference disassembly
```

## Key instructions

| Instruction | Meaning |
|-------------|---------|
| `cmp rcx, rsi` | Set flags from `rcx - rsi` |
| `jae label` | Jump if above or equal (unsigned >=) |
| `jb label` | Jump if below (unsigned <) |
| `mov rax, [rdi + rcx*8]` | Load 8-byte element at index `rcx` |
| `inc rcx` | Increment index |

## Pitfalls

- `n` is `unsigned long`, so use unsigned comparisons (`jae`/`jb`) rather than signed (`jge`/`jl`).
- The array pointer is in `rdi`; scaled-index addressing `[rdi + rcx*8]` reads element `rcx`.
- Make sure the loop body is skipped entirely when `n == 0` — check the condition **before** the first load.
