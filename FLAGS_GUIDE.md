# Flags Guide

x86-64 condition flags are shared state set by many arithmetic/logical instructions and consumed by branches, `cmov`, and `setcc`.

## High-value flags

- ZF: zero flag
- SF: sign flag
- CF: carry flag, commonly unsigned overflow/borrow
- OF: signed overflow

## Signed vs unsigned

Unsigned comparisons use carry/zero conditions such as `ja`, `jae`, `jb`, `jbe`.

Signed comparisons use sign/overflow/zero combinations such as `jg`, `jge`, `jl`, `jle`.

Mixing these up is a real correctness bug, not a style issue.

## `cmp` mental model

`cmp a, b` computes flags for `a - b` and discards the result in Intel syntax.

## `test` mental model

`test a, b` computes flags for bitwise `a & b` and discards the result. It is commonly used for zero checks.
