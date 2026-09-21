# Curriculum

The arc from x86-64 register basics through ABI-safe assembly, Linux syscalls, debugging, SIMD, inline assembly, and capstones. Difficulty: ★☆☆ easy → ★★★ hard.

> Legend: ✅ shipped · 🗺️ mapped

## Course structure

Each part builds on the previous material. Early exercises cover registers, memory, arithmetic, flags, and control flow. Later parts add the SysV ABI, position-independent data access, SIMD, Linux syscalls, inline assembly, debugging, and capstones.

```text
Part 0   Basic assembly syntax and registers
Part 1   C-callable functions and register conventions
Part 2   Memory and addressing
Part 3   Arithmetic, flags, and bit operations
Part 4   Branches and loops
Part 5   Stack frames and the SysV ABI
Part 6   Static data and RIP-relative addressing
Part 7   String and REP instructions
Part 8   SIMD
Part 9   Linux syscalls and minimal ELF programs
Part 10  Inline assembly in C
Part 11  Debugging and disassembly
Part 12  Capstones
```

The prerequisite table below shows the intended order.
| # | Part | Prereq | Est. | Status |
|---|------|--------|------|--------|
| 0 | Ground Zero: what assembly is (no prior knowledge) | none | 1h | ✅ |
| 1 | Architecture, registers, and syntax | 0 | 4h | ✅ |
| 2 | Data movement and addressing | 1 | 4h | ✅ |
| 3 | Arithmetic, flags, and bit manipulation | 2 | 5h | ✅ |
| 4 | Control flow and condition codes | 3 | 5h | ✅ |
| 5 | Stack frames and SysV ABI | 4 | 6h | ✅ |
| 6 | Memory layout and RIP-relative addressing | 5 | 5h | ✅ |
| 7 | String and REP instructions | 6 | 4h | ✅ |
| 8 | SIMD/SSE/AVX foundations | 6 | 8h | ✅ |
| 9 | Linux syscalls and minimal ELF programs | 5 | 6h | ✅ |
| 10 | Inline assembly in C | 5 | 6h | ✅ |
| 11 | Debugging, disassembly, and compiler output | 1–10 | 6h | ✅ |
| 12 | Capstones | 1–11 | 20h+ | ✅ |

## Prerequisite graph

```text
0 ── 1 ── 2 ── 3 ── 4 ── 5 ──┬── 6 ──┬── 7
                              │       └── 8
                              ├── 9
                              ├── 10
                              └── 11 ── 12
```

## Part 0: Ground Zero: what assembly is ✅

Lecture: [`part00-ground-zero/README.md`](part00-ground-zero/README.md)

The on-ramp for learners with **no prior assembly experience**. Teaches, from
nothing, what machine code and assembly are, what a register is, how an instruction
and its operands are written (Intel destination-first order), and what every line of
a `.S` file does. Two single-instruction exercises establish the edit→test→inspect
loop before any real computation:

- `01-return-constant` ★☆☆: `long return_42(void)` via `mov rax, 42`; a register, an
  immediate, `ret`, and the build loop.
- `02-return-input` ★☆☆: `long echo(long x)` via `mov rax, rdi`; the argument
  register `rdi`, register-to-register copy, and Intel operand order.

## Part 1: Architecture, registers, and syntax ✅

Lecture: [`part01-architecture-registers/README.md`](part01-architecture-registers/README.md)

- `01-add-two` ★☆☆: first SysV AMD64 C-callable assembly function; arguments in `rdi`/`rsi`, result in `rax`; Intel syntax in GAS.

Mapped additions:

- register aliases and partial-register hazards
- AT&T version of the same function
- flags inspection drill

## Part 2: Data movement and addressing ✅

Lecture: [`part02-data-movement-addressing/README.md`](part02-data-movement-addressing/README.md)

- `01-lea-scale-add` ★☆☆: `lea` as address arithmetic without flag writes.

Mapped additions:

- `02-sign-zero-extend`: `movsx`/`movzx`, 32-bit write zero-extension
- `03-rip-relative-load`: position-independent constant access

## Part 3: Arithmetic, flags, and bit manipulation ✅

Lecture: [`part03-arithmetic-flags-bits/README.md`](part03-arithmetic-flags-bits/README.md)

- `01-checked-add` ★☆☆: `int checked_add(long a, long b, long *out)` using `add` + `seto` to detect signed overflow.
- `02-signed-unsigned-cmp` ★☆☆: `int cmp3(long a, long b)` returning -1/0/1 via `cmp` + `jl`/`jg` (signed condition codes, not unsigned `jb`/`ja`).
- `03-bit-ops` ★★☆: `unsigned long popcount_and_rotate(unsigned long x, int r)` combining `popcnt` and `rol` instructions.

## Part 4: Control flow and condition codes ✅

Lecture: [`part04-control-flow-condition-codes/README.md`](part04-control-flow-condition-codes/README.md)

- `01-branchless-max` ★☆☆: `long imax(long a, long b)` using `cmp` + `cmovg`; no jumps.
- `02-array-sum-loop` ★☆☆: `long array_sum(const long *a, unsigned long n)` with a counted loop and `jae` exit.
- `03-classify-sign` ★☆☆: `int classify(long x)` returning -1/0/1 via a `jl`/`je`/fall-through ladder.

Mapped additions:

- branchless min with `cmovl`
- pointer-sentinel loop variant of array-sum
- jump-table reading drill

## Part 5: Stack frames and SysV ABI ✅

Lecture: [`part05-stack-frames-abi/README.md`](part05-stack-frames-abi/README.md)

- `01-factorial-recursive` ★★☆: recursive `factorial(n)` with push/pop and 16-byte stack alignment at each call site.
- `02-callee-saved` ★★☆: `sum_with_saved(a, b, c, d)` using callee-saved registers `rbx`/`r12` with correct save/restore.
- `03-mixed-args` ★☆☆: `mixed(a, p, c)` returning `a + *p + c`; integer and pointer argument passing in `rdi`/`rsi`/`rdx`.

## Part 6: Memory layout and RIP-relative addressing ✅

Lecture: [`part06-memory-rip-relative/README.md`](part06-memory-rip-relative/README.md)

- `01-byte-scan` ★☆☆: scan a byte buffer; return the index of the first match or −1.
- `02-rip-table-lookup` ★★☆: `weekday_len`: `.rodata` table accessed via `lea rax, [rip + table]`.
- `03-sum-static-array` ★★☆: `sum_static`: sum a fixed `.rodata` array via RIP-relative pointer loop.

## Part 7: String and REP instructions ✅

Lecture: [`part07-string-rep/README.md`](part07-string-rep/README.md)

- `01-strlen-scasb` ★☆☆: `unsigned long my_strlen(const char *s)` using `repne scasb` to scan for a NUL terminator.
- `02-memcpy-movsb` ★☆☆: `void my_memcpy(void *dst, const void *src, unsigned long n)` using `rep movsb` for a bounded byte copy.
- `03-direction-flag` ★★☆: `void reverse_copy(…)` demonstrating that `std` must always be paired with `cld` before return (SysV ABI direction-flag rule).

## Part 8: SIMD/SSE/AVX foundations ✅

Lecture: [`part08-simd-sse-avx/README.md`](part08-simd-sse-avx/README.md)

- `01-vector-add4` ★☆☆: `void add4_floats(float *dst, const float *a, const float *b)` adding 4 packed floats with `movups`/`addps`/`movups`.
- `02-packed-byte-eq` ★★☆: `int count_equal_bytes(const unsigned char *a, const unsigned char *b)` comparing 16 bytes with `movdqu`/`pcmpeqb`/`pmovmskb`/`popcnt`.
- `03-sum4-doubles` ★★☆: `double sum4_doubles(const double *p)` summing 4 packed doubles with `movupd`/`addpd` and a `movhlps`/`addsd` horizontal reduction.

## Part 9: Linux syscalls and minimal ELF programs ✅

Lecture: [`part09-syscalls-elf/README.md`](part09-syscalls-elf/README.md)

- `01-hello-syscall` ★☆☆: freestanding `_start` that writes `"hello\n"` to stdout via `write` syscall (rax=1) and exits 0 via `exit` syscall (rax=60).
- `02-exit-code` ★☆☆: freestanding `_start` that exits with a specific code (42) via `exit` syscall; no output; validates `$?`.
- `03-write-count` ★★☆: freestanding `_start` that writes `"ABCABCABC"` (9 bytes) using a counted loop of `write` syscalls, then exits 0.

## Part 10: Inline assembly in C ✅

Lecture: [`part10-inline-asm/README.md`](part10-inline-asm/README.md)

- `01-add-inline` ★☆☆: `long add_inline(long a, long b)` via `addq` in GCC extended asm; introduces `"+r"` read-write constraint and `"cc"` clobber.
- `02-clobber-bughunt` ★★☆: `long times3_via_lea(long x)` using `leaq (%r,%r,2)`; the stub computes the correct asm result but returns a literal `0`: students find the dead-variable bug.
- `03-memory-clobber` ★★☆: `void negate_all(long *arr, long n)` using `negq` with a `"+m"` memory operand and `"cc"` clobber; demonstrates `asm volatile` and why memory operands require `"+"` not `"="`.

## Part 11: Debugging, disassembly, and compiler output ✅

Lecture: [`part11-debugging-disasm/README.md`](part11-debugging-disasm/README.md)

- `01-fix-the-bug` ★☆☆: `long sum_to_n(long n)` with an off-by-one branch bug (`jge` instead of `jg`); diagnose with gdb `stepi`/`info registers` and `objdump`, then apply a one-character fix.
- `02-disasm-compare` ★★☆: compile `clamp(x, lo, hi)` at `-O0` and `-O2`; read both `.s` files and answer five questions about calling convention, frame setup, branch count, `cmov` usage, and line-count difference.
- `03-abi-forensic` ★★☆: `long broken_abi(long a, long b)` that clobbers `rbx` without push/pop and returns `a+b` instead of `a*2+b`; use `objdump` to identify both the ABI violation and the arithmetic bug, document findings in `report.md`, then verify with the reference fix.

## Part 12: Capstones ✅

Lecture: [`part12-capstones/README.md`](part12-capstones/README.md)

Shipped capstones:

| # | Directory | Function / Entry | Synthesizes |
|---|-----------|-----------------|-------------|
| 01 | `part12-capstones/01-crc32-checksum` | `crc32(data, len)` | Parts 1–7: registers, addressing, control flow, ABI, bit ops, loops |
| 02 | `part12-capstones/02-simd-memchr` | `simd_find_byte(s, n, c)` | Parts 1–4, 6, 8: SIMD (SSE2), bitmask, bsf |
| 03 | `part12-capstones/03-raw-cat` | `_start` (freestanding) | Parts 1–3, 9: raw read/write/exit syscall loop |

## Adding a new exercise

1. `mkdir -p partNN-topic/NN-name/{include,src,tests,solution}`
2. Write `include/<name>.h`, red `src/<name>.S`, frozen `tests/test_<name>.c`, and green `solution/<name>.S`.
3. Copy a sibling `Makefile`; set `NAME`.
4. Add entries here, the part README, and `docs/source-map.md`.
5. Run `make check-all` and `make solve-all`.
