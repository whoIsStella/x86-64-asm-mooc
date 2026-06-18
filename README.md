# x86-64-asm-mooc

> A self-contained, test-driven x86-64 assembly curriculum in the mooc.fi course format — learn Intel and AT&T syntax, the SysV AMD64 ABI, Linux syscalls, debugging, SIMD foundations, and capstone-level systems assembly.

This repository is generated from prompt **#11** of the [curriculum prompt library](../curriculum_prompts.md). It follows the same pedagogical contract as the sibling systems courses: why-before-what explanations, progressive scaffolding, frozen tests, red learner stubs, green reference solutions, and source-cited documentation.

## How it works

Each exercise is a small C-harnessed unit:

```text
partNN-topic/
└── NN-exercise-name/
    ├── README.md            ← task, objective, time, difficulty, hints
    ├── include/<name>.h     ← frozen C ABI
    ├── src/<name>.S         ← learner stub, starts RED
    ├── tests/test_<name>.c  ← frozen tests — do not modify
    ├── solution/<name>.S    ← reference implementation
    └── Makefile             ← `make test`, `make solve`, `make check`, `make objdump`
```

The learner edits only `src/<name>.S`. Reference implementations live under `solution/` and exist to validate the course.

## Quick start

```bash
make check-all
make -C part00-ground-zero/01-return-constant test     # start here — RED until implemented
make -C part00-ground-zero/01-return-constant solve    # GREEN reference
make -C part01-architecture-registers/01-add-two test   # RED until implemented
make -C part01-architecture-registers/01-add-two objdump
make solve-all
make clean
```

## Layout

| Path | Purpose |
|------|---------|
| `CURRICULUM.md` | Full learning arc, prerequisite graph, shipped/mapped status |
| `REFERENCE.md` | Source-of-truth documentation corpus |
| `docs/source-map.md` | Maps every part to authoritative docs |
| `docs/competency-model.md` | Expert-level completion criteria |
| `SYNTAX_ROSETTA.md` | Intel ↔ AT&T syntax translation reference |
| `ABI_NOTES.md` | SysV AMD64 ABI notes for C-callable assembly |
| `FLAGS_GUIDE.md` | Condition flags and signed/unsigned reasoning |
| `SYSCALLS.md` | Linux x86-64 syscall ABI notes |
| `DEBUGGING.md` | gdb/objdump/compiler-output workflow |
| `vendor/ctest/ctest.h` | Vendored tiny C test harness |
| `Makefile.inc` | Shared per-exercise build logic |

## Curriculum status

A ground-zero **Part 0** plus 12 numbered parts ship complete red/green exercises (34 exercises total), validated by `make solve-all`. Part 0 assumes **no prior assembly knowledge** and teaches registers, instructions, operand order, and the `.S` file from nothing; Parts 1–11 build conceptual and ABI fluency; Part 12 (Capstones) integrates them into a CRC-32 checksum, an SSE2 `memchr`, and a freestanding no-libc `cat`.

New to assembly? Start at [`part00-ground-zero/README.md`](part00-ground-zero/README.md).

See [`CURRICULUM.md`](CURRICULUM.md), [`docs/source-map.md`](docs/source-map.md), and [`docs/competency-model.md`](docs/competency-model.md) before adding exercises.
