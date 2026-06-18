# Part 6 — Memory layout and RIP-relative addressing

> Prerequisite: [Part 5](../part05-stack-frames-abi/README.md). So far your data came
> in through arguments or lived on the stack. This part adds **static data** — arrays
> and tables you write into the program itself — and the correct way to find its
> address at runtime.
>
> **Why care / how it connects:** every global variable, lookup table, and string
> literal in a real program is static data reached this way. RIP-relative addressing is
> also why modern binaries can load anywhere (ASLR) — the same mechanism behind a lot
> of security hardening.

This part explains how x86-64 code accesses static data safely in position-independent executables and why RIP-relative addressing replaced the old absolute-address model.

## Declaring data: sections, labels, and size specifiers

Up to now every line you wrote was code. To embed a constant table you switch the
assembler into a **data section** and emit values:

```asm
.section .rodata        ; "read-only data" — constants the program never modifies
.align 8                ; start on an 8-byte boundary (so .quad loads are aligned)
static_array:           ; a LABEL — names the ADDRESS of the first byte that follows
    .quad 10, 20, 30, 40, 50   ; five 8-byte values laid out back to back
static_array_end:       ; another label — marks the address just past the last value
.text                   ; switch back to the code section for instructions
```

- A **label** in a data section is just a name for an *address*. `static_array` means
  "wherever these bytes ended up". `lea rax, [rip + static_array]` puts that runtime
  address in `rax`.
- Data-emitting directives by size: `.byte` (1), `.int`/`.long` (4), `.quad` (8). The
  bytes are placed in order, so `.quad 10, 20, 30` is a 3-element array of `long`.
- `.rodata` is for constants; `.data` is for things you also write to.

When you *load* from a computed address, the assembler needs to know **how many bytes**
to read if it can't tell from a register. That is the **size specifier**:

```asm
movzx eax, byte ptr  [rdi + rcx]    ; read 1 byte, zero-extend into eax
movsx eax, dword ptr [rax + rdi*4]  ; read 4 bytes, sign-extend into eax
add   rax, qword ptr [rdi]          ; read 8 bytes
```

`byte/word/dword/qword ptr` = 1/2/4/8 bytes. `movzx` zero-extends a narrow value into a
wide register (for unsigned data); `movsx` sign-extends (for signed data) — the same
distinction you met as the 32-bit zero-extension rule in Part 2, now made explicit.

## Why RIP-relative addressing exists

Before x86-64, 32-bit code used absolute 32-bit addresses to reference `.data` and `.rodata` symbols. That worked because a process's virtual address was fixed at link time. On x86-64 with ASLR, the load address changes at runtime, so hard-coded 32-bit absolute addresses are wrong.

The CPU solves this with **RIP-relative addressing**: any memory reference of the form `[rip + offset]` computes the effective address as the address of the *next* instruction plus a signed 32-bit displacement baked in by the linker. Because the displacement is relative to the instruction itself, it stays correct regardless of where the binary is loaded.

The GAS Intel-syntax spelling is:

```asm
lea rax, [rip + my_table]          ; rax = runtime address of my_table
mov eax, dword ptr [rip + my_var]  ; load 32-bit value at my_var
```

The linker fills in the correct displacement automatically.

### When to use it

- Reading constants or tables from `.rodata` (e.g., length tables, lookup tables).
- Accessing mutable variables in `.data` that belong to the same translation unit.
- Any time you need the runtime address of a local symbol without going through the GOT.

### Contrast with absolute addressing

With `-no-pie` (as used in this course), the linker can also satisfy 32-bit absolute references, so both forms link. In a real PIE or shared library only RIP-relative (or GOT-indirect) references are valid. Knowing the RIP-relative form keeps your assembly portable.

## Shipped exercises

- `01-byte-scan` ★☆☆ — `find_byte`: scan a byte buffer with a pointer loop; return the index of the first match or −1.
- `02-rip-table-lookup` ★★☆ — `weekday_len`: map a weekday index 0–6 to its name length using a `.rodata` table accessed via `lea rax, [rip + weekday_lengths]`.
- `03-sum-static-array` ★★☆ — `sum_static`: sum a fixed `.rodata` array of `long` values using a RIP-relative pointer loop; no arguments.

## Source alignment

See:

- [`../REFERENCE.md`](../REFERENCE.md)
- [`../docs/source-map.md`](../docs/source-map.md)

## Competency target

After this part you should be able to explain why `[rip + label]` is needed in PIE code, write a `.rodata` table in the same `.S` file as its consumer, and loop over a static array using a pointer derived from RIP-relative `lea`.
