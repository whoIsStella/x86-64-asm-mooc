# Part 0 Ground Zero: what assembly actually is

> Start here. This part assumes you have **never written or read assembly before**.
> If you already know what a register is and how `mov rax, rdi` works, skim this and
> jump to [Part 1](../part01-architecture-registers/README.md).

By the end of Part 0 you will have written two working assembly functions, each a
single instruction long, and understood every character in the file you edited.
Nothing here is memorization, it is the vocabulary the rest of the course speaks.

---

## Orientation: the five W's of assembly

Before any mechanics, the big picture in five questions.

**What** is assembly? It is the thinnest possible human-readable layer over the raw
**machine code** your CPU executes. One line of assembly corresponds to (essentially)
one CPU instruction. Higher-level languages  C, Python, Rust are eventually
translated down into these same instructions; assembly is where that ladder bottoms
out and you are talking to the hardware in its own terms. It is specific to a CPU
family; this course teaches **x86-64**, the instruction set of nearly every PC and
server.

**Who** writes or reads it, in practice? Almost nobody writes whole programs in it
anymore, compilers do that, and do it well. People reach for assembly to: write the
few performance-critical inner loops a compiler can't vectorize well (codecs, crypto,
math kernels); build the lowest layer of operating systems, bootloaders, and
device drivers; reverse-engineer or audit binaries for security; and, most relevant
to you *understand what the machine actually does* so the higher levels stop being
magic. Compilers, debuggers, and security researchers are the heavy users.

**When** did it come from, and when do you use it? Assembly dates to the late 1940s–50s,
as a humane replacement for entering raw numeric machine code by hand; x86 specifically
descends from Intel's 8086 (1978), extended to 64-bit ("x86-64" / "AMD64") by AMD in
2003. You reach for it *when* a compiler's output isn't good enough, isn't possible
(there's no C for "set this exact CPU flag"), or isn't trusted (you need to see the—
real bytes). The rest of the time, you *read* it far more than you *write* it.

**Where** does it run and live? It runs directly on the CPU's execution units, operating
on **registers** (tiny on-chip storage) and **memory**. It lives in the `.text` section
of your compiled program. In this course it lives in `.S` files you edit, gets
translated by the assembler into an executable, and is inspected with `objdump` and
`gdb`. It sits one layer below C and one layer above the silicon.

**Why** learn it if compilers are so good? Because it makes you a stronger programmer
at *every* level above it: you understand why a struct layout or a branch is slow, how
a pointer really works, what "undefined behavior" lets a compiler do, how a stack
overflow or a security exploit functions, and what your debugger is showing you. You
are not learning assembly to write assembly, you are learning it to see the machine
clearly. Everything in Parts 1–12 serves that.

---

## 1. What is assembly, and why does it exist?

Your CPU does not understand C, Python, or even the text in these files. It executes
**machine code**: raw numbers, each encoding one tiny operation ("add these two
things", "copy this number there", "jump to that location"). Machine code is
unreadable to humans, it is just bytes like `48 01 f0`.

**Assembly language** is a one-line-per-operation, human-readable spelling of that
machine code. The bytes `48 01 f0` are written in assembly as:

```asm
add rax, rsi
```

A program called an **assembler** (we use `as`, part of the GNU toolchain, invoked
for us by the C compiler `cc`) translates your assembly text into those machine-code
bytes. So the pipeline is:

```text
you write:  add rax, rsi        (assembly what you edit)
assembler:  48 01 f0            (machine code, what the CPU runs)
```

Assembly is not a single language. Each CPU family has its own instructions. This
course teaches **x86-64** (also called AMD64 or `x86_64`), the instruction set in
virtually every desktop, laptop, and server CPU from Intel and AMD.

There is one more wrinkle: even for x86-64, there are two competing *spellings* of
the same instructions, **Intel syntax** and **AT&T syntax**. They describe the
identical machine code with different punctuation. This course starts in Intel
syntax because it reads left-to-right like `destination = source`. You will meet
AT&T later. ([`SYNTAX_ROSETTA.md`](../SYNTAX_ROSETTA.md) is the translation table.)

---

## 2. Registers: the CPU's hands

The CPU cannot compute on data sitting in memory (RAM) directly. It first pulls
values into **registers**, a tiny set of named storage slots that live *inside* the
CPU and are the fastest storage in the machine. Think of them as the CPU's hands:
to add two numbers, it holds one in each hand.

x86-64 gives you **16 general-purpose registers**, each holding **64 bits** (8 bytes,
i.e. one `long` on Linux). Their names:

```text
rax  rbx  rcx  rdx  rsi  rdi  rbp  rsp
r8   r9   r10  r11  r12  r13  r14  r15
```

For now you only need four of them:

| Register | What we use it for in Part 0                          |
|----------|--------------------------------------------------------|
| `rdi`    | The **first argument** handed to a function.           |
| `rsi`    | The **second argument** handed to a function.          |
| `rax`    | The **return value** a function hands back.            |
| `rsp`    | The stack pointer (you will not touch it yet).         |

Why *those* registers for arguments and return values? That is not a CPU rule, it
is a **convention**, the SysV AMD64 ABI, a contract that lets C and assembly call
each other. Part 1 explains it; Part 5 covers it in depth. For now, treat the table
above as the rules of the game.

---

## 3. Instructions and operand order

An **instruction** is one verb of work. It is written as a mnemonic (the verb)
followed by its **operands** (the nouns it acts on), separated by commas:

```asm
mov  rax, rdi
│    │    └── source operand:      copy FROM here
│    └─────── destination operand: copy INTO here
└──────────── mnemonic (the verb): "move" (really: copy)
```

**In Intel syntax the destination always comes first.** Read `mov rax, rdi` as
`rax = rdi`. This trips up everyone once; after that it is automatic.

The handful of instructions you need to start:

| Instruction        | Meaning (Intel order: `dst, src`)                         |
|--------------------|------------------------------------------------------------|
| `mov rax, rdi`     | Copy `rdi` into `rax`. (`rdi` is unchanged, `mov` copies.)|
| `mov rax, 42`      | Put the literal number `42` into `rax`.                    |
| `add rax, rsi`     | `rax = rax + rsi`.                                          |
| `ret`              | Return from the function to whoever called it.             |

A bare number like `42` written directly in an instruction is called an
**immediate**, the value is baked into the instruction itself.

---

## 4. Anatomy of a `.S` file, every line explained

Assembly source files end in `.S` (capital S means "run the C preprocessor first").
Here is a complete, working function. Every line is either a **directive** (an
instruction *to the assembler*, starting with `.`) or an **instruction** (work *for
the CPU*). Nothing is magic, here is what each line does:

```asm
.intel_syntax noprefix      # Use Intel spelling, and don't require "%" before
                            #   register names. Affects how the WHOLE file is read.
.text                       # "Code goes here." Put the following into the program's
                            #   executable code section (as opposed to data).
.globl return_42            # Make the name "return_42" visible to other files, so
                            #   the C test harness is allowed to call it.
.type return_42, @function  # Tell tools this symbol is a function (helps debuggers).
return_42:                  # A LABEL: a name for this spot in the code. "return_42:"
                            #   marks where the function begins. Calling return_42()
                            #   from C jumps here.
    mov rax, 42             # The actual work: put 42 into the return register.
    ret                     # Hand control (and rax) back to the caller.
.size return_42, .-return_42  # Record the function's byte length ("." = here,
                            #   minus the label = size). Bookkeeping for tools.
```

Lines starting with `#` are **comments**, ignored by the assembler, there for you.

You do **not** need to memorize the boilerplate (`.intel_syntax`, `.text`, `.globl`,
`.type`, `.size`). Every exercise stub already contains it. The two lines that are
*yours* to write are the instructions between the label and `.size`:

```asm
    mov rax, 42
    ret
```

That is the whole job: fill in the verbs.

---

## 5. How a function call works, in one picture

When C runs `long r = return_42();`:

```text
1. C places any arguments in rdi, rsi, ...   (return_42 has none)
2. C executes a "call", control jumps to the return_42: label.
3. Your instructions run.  You leave the answer in rax.
4. "ret" jumps control back to the C code, right after the call.
5. C reads the answer out of rax into the variable r.
```

So a C-callable function's entire contract is: **read your inputs from the argument
registers, leave your output in `rax`, then `ret`.** That is it. Everything else in
the course builds on this one sentence.

---

## 6. The edit → test → inspect loop

Every exercise is a small folder. You edit exactly one file, `src/<name>.S` and
the tests, written in C, check your work. The commands (run them inside an exercise
folder):

```bash
make test     # Build YOUR src/<name>.S and run the tests. RED until you implement it.
make solve    # Build the reference solution/ instead proves the tests are passable.
make objdump  # Disassemble the compiled solution so you can see the real machine code.
make check    # Just compile both, don't run, a quick "does it assemble?" check.
```

A normal session: run `make test`, watch it fail, edit `src/<name>.S`, run `make
test` again, repeat until green. Stuck? `make solve` shows a working version; compare
it to yours. Curious what the bytes look like? `make objdump`.

The very first stub you will open looks like this, note it is deliberately *wrong*
so the test starts RED:

```asm
return_42:
    # TODO: put 42 into rax, then return.
    mov rax, 0      # <-- placeholder. Make this return 42 instead.
    ret
```

---

## 7. Your turn

Do these two in order. Each is a single instruction. The goal is not difficulty,
it is to make the file, the registers, and the build loop feel ordinary before any
real complexity arrives.

- [`01-return-constant`](01-return-constant/README.md) ★☆☆, return the constant
  `42`. Teaches: a register, an immediate, `mov`, `ret`, and the test loop.
- [`02-return-input`](02-return-input/README.md) ★☆☆ return the argument you were
  given, unchanged. Teaches: the argument register `rdi`, copying between registers,
  and Intel `dst, src` order.

When both are green, go to [Part 1](../part01-architecture-registers/README.md),
where `add_two` combines them: read two arguments, add them, return the result.

## Source alignment

See:

- [`../REFERENCE.md`](../REFERENCE.md) documentation corpus and trust model.
- [`../SYNTAX_ROSETTA.md`](../SYNTAX_ROSETTA.md) Intel ↔ AT&T spelling.
- [`../ABI_NOTES.md`](../ABI_NOTES.md) the argument/return-register contract.
