# Part 2 — Data movement and addressing

> Prerequisite: [Part 1](../part01-architecture-registers/README.md). You can write
> a C-callable function: read arguments from `rdi`/`rsi`, leave the result in `rax`,
> `ret`. This part adds the two things real programs spend most of their time doing —
> moving data to and from **memory**, and computing **addresses**.
>
> **Why care / how it connects:** real data — arrays, strings, structs — lives in
> memory, so this is most of what programs do. The `[base + index*scale]` form you
> learn here reappears in Part 4's array loop, Part 6's tables, and Part 8's vector
> loads.

So far every value lived in a register. But registers are few (16) and tiny; real
data — arrays, strings, structs — lives in **memory** (RAM). This part teaches how an
instruction names a memory location, how to load from and store to it, and the
single most misunderstood instruction in x86-64: `lea`.

## A memory address is computed, not just named

When an instruction touches memory, it does not carry a fixed address. Instead it
carries a little formula the CPU evaluates every time the instruction runs. In Intel
syntax that formula goes inside square brackets:

```text
[ base + index*scale + displacement ]
   │       │     │        │
   │       │     │        └── a constant, e.g. +16  (the "offset")
   │       │     └────────── 1, 2, 4, or 8  (and ONLY those)
   │       └──────────────── a register holding an element number
   └──────────────────────── a register holding a starting address
```

Every part is optional. All of these are legal addresses:

```asm
[rdi]                  ; just a base:            the address in rdi
[rdi + 16]             ; base + displacement:    16 bytes past rdi
[rdi + rsi]            ; base + index:           rdi + rsi
[rdi + rsi*8]          ; base + index*scale:     the rsi-th 8-byte element
[rdi + rsi*8 + 16]     ; the full form
```

Why is the scale restricted to **1, 2, 4, or 8**? Those are the sizes of the common
data types — byte, word, dword, qword. `[rdi + rsi*8]` reads "element `rsi` of an
array of 8-byte `long`s starting at `rdi`", which is exactly C's `a[i]`. The CPU
encodes the scale in 2 bits, so no other value is possible.

## Two instructions, one bracket syntax — `mov` vs `lea`

The brackets mean different things depending on the verb:

```asm
mov rax, [rdi + 16]    ; LOAD:    go to address (rdi+16), read 8 bytes, put them in rax
lea rax, [rdi + 16]    ; COMPUTE: put the ADDRESS (rdi+16) in rax. Memory is NOT touched.
```

- **`mov rax, [addr]`** dereferences: it reads the *value stored at* that address.
  Without brackets, `mov rax, rdi` just copies the register.
- **`lea rax, [addr]`** ("load effective address") evaluates the formula and stores
  the resulting *number*. It never reads memory. It is secretly a math instruction:
  `lea rax, [rdi + rsi*8 + 16]` computes `rdi + rsi*8 + 16` in one step.

Two properties make `lea` a favourite tool:

1. It does arithmetic that would otherwise take several `add`/`shl`/`imul`
   instructions — multiply-by-{1,2,4,8} and add, all at once.
2. **It does not touch the flags.** Ordinary `add` updates `CF`/`OF`/`ZF`/… (Part 3);
   `lea` leaves them alone, so you can compute an address in the middle of a
   flag-sensitive sequence without disturbing a pending condition.

A store works the same way with the brackets on the left:

```asm
mov [rdi], rax         ; STORE: write the 8 bytes of rax to the address in rdi
```

## Operand sizes and the 32-bit zero-extension rule

A register can be touched at several widths. For `rax`: `rax` (64-bit), `eax`
(low 32), `ax` (low 16), `al` (low 8). They are the *same* register — writing the
small name changes part of the big one. One rule has caught every assembly
programmer at least once:

> **Writing a 32-bit register zeroes the upper 32 bits of the 64-bit register.**
> Writing an 8- or 16-bit register leaves the upper bits unchanged.

So `mov eax, 5` makes `rax` exactly `5`, but `mov al, 5` only sets the low byte and
leaves whatever was in the upper 56 bits. This is why solutions return an `int` by
writing `eax` (it cleanly zero-extends) and why a stray `al` write can leak garbage.
To deliberately widen narrow values you use `movzx` (zero-extend) and `movsx`
(sign-extend) — you will meet them when an exercise needs them.

## The `xor reg, reg` zeroing idiom

You will see this in many solutions instead of `mov rax, 0`:

```asm
xor eax, eax           ; eax = 0  (a number XOR'd with itself is 0)
```

`xor eax, eax` sets the register to zero just like `mov eax, 0`, but the machine-code
encoding is shorter and the CPU recognises it as "produce a zero". It is the
*idiomatic* way to clear a register. (It writes `eax`, so by the rule above the whole
`rax` becomes 0.) Read every `xor reg, reg` as simply "`reg = 0`". The one catch: like
other arithmetic it disturbs the flags, so don't place it between a `cmp` and the jump
that depends on it (Part 3).

## Shipped exercises

- `01-lea-scale-add` ★☆☆ — use `lea` to compute `base + index*8 + 16` in a single
  instruction, without loading memory and without touching the flags.

## Source alignment

See:

- [`../REFERENCE.md`](../REFERENCE.md)
- [`../SYNTAX_ROSETTA.md`](../SYNTAX_ROSETTA.md)
- [`../docs/source-map.md`](../docs/source-map.md)

## Competency target

After this part, you should be able to explain why `lea` is address arithmetic (not a
memory load), read and write memory with `[...]` operands, name the only legal scale
factors and why, and state when a 32-bit register write zero-extends into the full
64-bit register.
