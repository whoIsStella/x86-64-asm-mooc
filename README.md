# x86-64 Assembly MOOC

I built the assembly course I wanted to have: small programs, fixed interfaces, tests that tell you when you're wrong, and enough ABI work to make a debugger useful. It starts with returning a constant and ends with CRC-32, SSE2 byte search, and a no-libc `cat`.

**Runnable course material.** There are 34 exercises across Part 0 and 12 numbered parts, with starter code, reference solutions, and build/check targets. Intel and AT&T syntax, SysV AMD64, Linux syscalls, SIMD, and disassembly are part of the progression.

## Start here

Requires Linux on x86-64, a C compiler with GNU-compatible assembler support,
GNU Make, and binutils. GDB is useful for the debugging exercises.

```bash
make check-all
make -C part00-ground-zero/01-return-constant test  # red until you implement it
make -C part00-ground-zero/01-return-constant solve # verify the reference
make solve-all                                    # all reference exercises
make clean
```

Edit `src/`; keep the test harness and interface fixed. Read
[Part 0](part00-ground-zero/README.md) before reaching for the solution.

## How an exercise works

| Path | Role |
| --- | --- |
| `README.md` | Task and constraints, where supplied |
| `src/` | Your implementation or intentionally broken starter |
| `include/` | C interface for harness-based exercises |
| `tests/` | C tests for harness-based exercises |
| `solution/` | Reference implementation |
| `Makefile` | Build, test, solution, and disassembly targets |

Syscall and forensic exercises use their own layouts. `make test-all` tolerates
starter failures by design, so its exit status is not a completion check.
`make solve-all` stops on a failing reference exercise.

## Progression

| Parts | Material |
| --- | --- |
| 0–3 | Registers, operand order, addressing, arithmetic, flags, bit operations |
| 4–7 | Branches, loops, stack frames, calling convention, RIP-relative data, string instructions |
| 8–10 | SSE2, raw syscalls/ELF, inline assembly and clobbers |
| 11–12 | Debugging, disassembly, ABI forensics, and capstones |

The SIMD exercises currently use SSE2; the part directory's `sse-avx` name
is broader than the implemented material.

## Notes worth keeping open

- [Curriculum and exercise status](CURRICULUM.md)
- [Intel/AT&T syntax](SYNTAX_ROSETTA.md), [ABI](ABI_NOTES.md), [flags](FLAGS_GUIDE.md)
- [Syscalls](SYSCALLS.md) and [debugging/disassembly](DEBUGGING.md)
- [Reference](REFERENCE.md), [source map](docs/source-map.md), [completion criteria](docs/competency-model.md)

The exercise format takes inspiration from MOOC.fi. This repository is its own
course, not an official MOOC.fi offering.
