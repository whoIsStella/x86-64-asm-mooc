# ABI Forensic Report

## Your task

Run `make test` to see the failures, then use `objdump` and the questions
below to diagnose both bugs.  Replace every TODO with your findings.
When all TODOs are gone, `make solve` will also check this file.

---

## Bug 1 — wrong arithmetic

What value does `broken_abi(3, 4)` return?  What should it return?

**Observed return value:** 7

**Expected return value:** 10

**Root cause** (describe the arithmetic error in the assembly): The function
computes `a + b` (adds rsi directly to rdi's copy in rbx) instead of `a*2 + b`.
The `add rbx, rbx` step to double `a` is missing; only `add rbx, rsi` is
present, which adds `b` to a single copy of `a`.

---

## Bug 2 — ABI violation

Which callee-saved register is clobbered?

**Register:** rbx

What instruction writes to it without first saving it?

**Instruction:** `mov rbx, rdi`

What is missing at the start and end of the function?

**Missing prologue instruction:** `push rbx`

**Missing epilogue instruction:** `pop rbx`

---

## Fix summary

Added `push rbx` at function entry and `pop rbx` before `ret` to honour the
callee-save contract, and inserted `add rbx, rbx` after `mov rbx, rdi` to
correctly double `a` before adding `b`.
