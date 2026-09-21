# x86-64 Assembly MOOC

A hands-on x86-64 assembly course built in a MOOC.fi-style exercise format.

The course covers Intel and AT&T syntax, the SysV AMD64 ABI, Linux syscalls, debugging, SIMD basics, and larger capstone exercises.

## Exercise format

Each exercise uses a small C test harness:

```text
partNN-topic/
└── NN-exercise-name/
    ├── README.md
    ├── include/<name>.h
    ├── src/<name>.S
    ├── tests/test_<name>.c
    ├── solution/<name>.S
    └── Makefile
```

Learners edit `src/<name>.S`. The C ABI and tests stay fixed. Reference implementations live under `solution/`.

## Quick start

```bash
make check-all

make -C part00-ground-zero/01-return-constant test
make -C part00-ground-zero/01-return-constant solve

make -C part01-architecture-registers/01-add-two test
make -C part01-architecture-registers/01-add-two objdump

make solve-all
make clean
```

If you are new to assembly, start with [`part00-ground-zero/README.md`](part00-ground-zero/README.md).

## Reference material

| Path | Contents |
| --- | --- |
| `CURRICULUM.md` | Course sequence, prerequisites, and exercise status |
| `REFERENCE.md` | Core reference notes |
| `docs/source-map.md` | Sources used for each part |
| `docs/competency-model.md` | Completion criteria |
| `SYNTAX_ROSETTA.md` | Intel and AT&T syntax comparison |
| `ABI_NOTES.md` | SysV AMD64 ABI notes |
| `FLAGS_GUIDE.md` | Condition flags and signed/unsigned comparisons |
| `SYSCALLS.md` | Linux x86-64 syscall notes |
| `DEBUGGING.md` | gdb, objdump, and compiler-output workflow |
| `vendor/ctest/ctest.h` | Small vendored C test harness |
| `Makefile.inc` | Shared exercise build rules |

## Current scope

The repository contains Part 0 plus 12 numbered parts and 34 exercises.

Part 0 starts with registers, instructions, operand order, and basic `.S` files. Later parts cover addressing, arithmetic, flags, control flow, stack frames, the ABI, RIP-relative addressing, string instructions, SIMD, syscalls, ELF, inline assembly, debugging, and disassembly.

The capstone exercises include a CRC-32 checksum, an SSE2 `memchr`, and a freestanding no-libc `cat`.

Run `make solve-all` to verify the shipped reference implementations.
