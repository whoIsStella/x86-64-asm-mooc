# 01 — Vector add (4 packed floats)

Difficulty: ★☆☆

Estimated time: 20–30 minutes

## Objective

Implement a SysV AMD64 ABI-compatible function:

```c
void add4_floats(float *dst, const float *a, const float *b);
```

Add four single-precision floats element-wise and write the results to `dst`:

```text
dst[i] = a[i] + b[i]   for i in { 0, 1, 2, 3 }
```

Use the SSE packed-float instructions: `movups` to load/store and `addps` to
add all four lanes in a single instruction.

## ABI reminder

Under the SysV AMD64 ABI:

- `dst` arrives in `rdi`
- `a`   arrives in `rsi`
- `b`   arrives in `rdx`
- This function returns `void`; **do not** modify `rax`.

XMM registers `xmm0`–`xmm7` are **caller-saved** — you may use them freely
without saving/restoring.

## Key instructions

| Instruction | Operation |
|---|---|
| `movups xmm0, [rsi]` | Load 16 bytes (4 × float) from memory into xmm0 (unaligned) |
| `addps  xmm0, xmm1`  | Add all four float lanes: xmm0[i] += xmm1[i] |
| `movups [rdi], xmm0` | Store 16 bytes from xmm0 to memory (unaligned) |

`movups` vs `movaps`: use `movups` (unaligned) here because the caller makes no
alignment guarantee. `movaps` requires 16-byte alignment and will fault if that
is not met.

## How to do it

Load each input array into its own vector register, add them in one packed
instruction, store the result. Four lines:

```asm
add4_floats:
    movups xmm0, [rsi]    ; xmm0 = { a[0], a[1], a[2], a[3] }
    movups xmm1, [rdx]    ; xmm1 = { b[0], b[1], b[2], b[3] }
    addps  xmm0, xmm1     ; xmm0 = a + b, all four lanes at once
    movups [rdi], xmm0    ; dst[0..3] = xmm0
    ret
```

`movups` moves 16 bytes (four floats) to or from memory; `addps` adds all four lanes
in parallel and writes the result back into its first operand (`xmm0`). This returns
`void`, so leave `rax` alone — the result goes to memory through `dst`, not a register.

## What to edit

Edit only:

```text
src/vector_add4.S
```

## Commands

```bash
make test    # RED until implemented
make solve   # GREEN reference
make check   # build stub and solution
make objdump # inspect reference disassembly
```

## Pitfalls

- `movups` takes the memory operand in Intel-syntax brackets: `movups xmm0, [rsi]`.
- `addps` modifies the *first* operand in-place: `addps xmm0, xmm1` writes into `xmm0`.
- Do not use `movaps` unless you can guarantee 16-byte alignment from the caller.
