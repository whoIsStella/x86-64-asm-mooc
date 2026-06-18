# Debugging x86-64 Assembly

## Disassemble the reference

```bash
make -C part01-architecture-registers/01-add-two solve
make -C part01-architecture-registers/01-add-two objdump
```

## Use gdb

```bash
gdb --args part01-architecture-registers/01-add-two/build/test_solution
(gdb) set disassembly-flavor intel
(gdb) break add_two
(gdb) run
(gdb) info registers
(gdb) disassemble /r add_two
```

## Debugging standard

Do not patch assembly by guessing. Prove the defect with at least one of:

- failing test input
- register state
- flags state
- stack view
- disassembly
- ABI rule from `ABI_NOTES.md`
