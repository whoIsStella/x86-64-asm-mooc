# Compiler output comparison notes

## Your task

Run `make solve` to generate `build/clamp_O0.s` and `build/clamp_O2.s`, then
answer each question below by replacing the TODO markers with your observations.
When you have removed **all** TODO markers, `make test` will pass.

---

## Question 1 — calling convention

In `clamp_O0.s`, where does the compiler store the three arguments `x`, `lo`,
`hi` at the start of the function?

**Answer:** TODO

---

## Question 2 — stack frame

Does `clamp_O0.s` set up a stack frame (push rbp / mov rbp, rsp)?

**Answer:** TODO

---

## Question 3 — optimisation effect on branches

How many conditional-branch instructions (`j*`) appear in `clamp_O0.s`?
How many in `clamp_O2.s`?

**Answer:** TODO

---

## Question 4 — cmov vs jump

Does `clamp_O2.s` replace any branches with `cmov` (conditional move)?
If so, name the instruction(s) you see.

**Answer:** TODO

---

## Question 5 — line count comparison

`make solve` prints the number of lines in each `.s` file.  Which is shorter,
and by roughly how many lines?

**Answer:** TODO
