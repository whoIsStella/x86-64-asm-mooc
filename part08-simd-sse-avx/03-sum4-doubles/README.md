# 03 — Sum 4 packed doubles

Difficulty: ★★☆

Estimated time: 30–45 minutes

## Objective

Implement a SysV AMD64 ABI-compatible function:

```c
double sum4_doubles(const double *p);
```

Return the sum of four consecutive double-precision values:

```text
p[0] + p[1] + p[2] + p[3]
```

Use `movupd` and `addpd` (packed double) to process two doubles at a time,
then horizontally reduce the pair to a scalar result in `xmm0`.

## ABI reminder

Under the SysV AMD64 ABI:

- `p` arrives in `rdi` (pointer to four doubles)
- The return value is a `double`, which goes in the **low 64 bits of xmm0**.

This function takes a pointer argument, so `rdi` is used — not `xmm0`. Only the
*return* uses `xmm0`.

## Key instructions

| Instruction | Operation |
|---|---|
| `movupd xmm0, [rdi]` | Load 2 doubles (16 bytes) unaligned |
| `addpd  xmm0, xmm1`  | Add both double lanes in parallel |
| `movhlps xmm1, xmm0` | Copy high 64 bits of xmm0 into low 64 bits of xmm1 |
| `addsd  xmm0, xmm1`  | Scalar double add: xmm0[low] += xmm1[low] |

### Reduction pattern

```text
load { p[0], p[1] } into xmm0
load { p[2], p[3] } into xmm1
addpd xmm0, xmm1  →  xmm0 = { p[0]+p[2],  p[1]+p[3] }
movhlps xmm1, xmm0 → xmm1[low] = p[1]+p[3]
addsd xmm0, xmm1  →  xmm0[low] = (p[0]+p[2]) + (p[1]+p[3])  ✓
```

## How to do it

A vector add gets you *partial* sums, one per lane; you then have to "horizontally"
add the lanes together to a single number. Two doubles per register, so: add the two
pairs, then add the two surviving lanes:

```asm
sum4_doubles:
    movupd  xmm0, [rdi]       ; xmm0 = { p[0], p[1] }
    movupd  xmm1, [rdi + 16]  ; xmm1 = { p[2], p[3] }   (+16 bytes = next two doubles)
    addpd   xmm0, xmm1        ; xmm0 = { p[0]+p[2], p[1]+p[3] }
    movhlps xmm1, xmm0        ; xmm1 low = xmm0 high = p[1]+p[3]
    addsd   xmm0, xmm1        ; xmm0 low = (p[0]+p[2]) + (p[1]+p[3]) = the total
    ret
```

`addpd` is the *packed* (both lanes) add; `addsd` is the *scalar* (low lane only) add.
`movhlps` slides the high lane down into the low lane of another register so `addsd`
can combine them. The final scalar lands in the low 64 bits of `xmm0`, which is exactly
where a `double` return value belongs.

## What to edit

Edit only:

```text
src/sum4_doubles.S
```

## Commands

```bash
make test    # RED until implemented
make solve   # GREEN reference
make check   # build stub and solution
make objdump # inspect reference disassembly
```

## Pitfalls

- The pointer arrives in `rdi`, not `xmm0`. Load from memory using brackets.
- `[rdi + 16]` addresses the second pair of doubles (each double is 8 bytes,
  two doubles = 16 bytes).
- `movhlps` is an SSE1 instruction that moves 64-bit *float* halves; it works
  on the raw 64 bits regardless of the element type, so it is correct here.
- The final scalar result must be in the **low 64 bits** of `xmm0` — `addsd`
  writes exactly there.
