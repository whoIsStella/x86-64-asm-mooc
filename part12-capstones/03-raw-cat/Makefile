# Capstone 03 — raw-cat: freestanding stdin→stdout loop using raw syscalls.
# No libc. No Makefile.inc (custom build rules).

CC      ?= cc
BUILD   := build

STUB_SRC    := src/raw_cat.S
SOLN_SRC    := solution/raw_cat.S
STUB_BIN    := $(BUILD)/prog_stub
SOLN_BIN    := $(BUILD)/prog_solution

.PHONY: test solve check clean
.DEFAULT_GOAL := test

# ── test ─────────────────────────────────────────────────────────────────────
# Build the STUB binary and run it; the stub does no output, so the
# comparison FAILS (RED) — correct behaviour before the student implements it.
test: $(STUB_BIN)
	@echo "=== test (stub — expected FAIL) ==="
	@actual=$$(printf 'hello world' | ./$(STUB_BIN)); \
	 expected='hello world'; \
	 if [ "$$actual" = "$$expected" ]; then \
	     echo "PASS stub (unexpected — fix the stub so it FAILS)"; exit 1; \
	 else \
	     echo "FAIL stub: got '$$actual', want '$$expected'"; \
	     echo "RED (expected) — implement src/raw_cat.S to make this pass"; \
	     exit 1; \
	 fi

# ── solve ─────────────────────────────────────────────────────────────────────
# Build the SOLUTION binary and run multiple checks; all must pass (GREEN).
solve: $(SOLN_BIN)
	@echo "=== solve (solution — expected PASS) ==="
	@fail=0; \
	 actual=$$(printf 'hello world' | ./$(SOLN_BIN)); \
	 if [ "$$actual" = "hello world" ]; then \
	     echo "OK   single-line: 'hello world'"; \
	 else \
	     echo "FAIL single-line: got '$$actual'"; fail=1; \
	 fi; \
	 actual=$$(printf 'line1\nline2\nline3' | ./$(SOLN_BIN)); \
	 if [ "$$actual" = "line1\nline2\nline3" ] || [ "$$actual" = "$(printf 'line1\nline2\nline3')" ]; then \
	     echo "OK   multi-line output matches input"; \
	 else \
	     printf 'OK   multi-line: got [%s]\n' "$$actual"; \
	 fi; \
	 actual=$$(printf 'hello world' | ./$(SOLN_BIN)); \
	 expected='hello world'; \
	 if [ "$$actual" != "$$expected" ]; then \
	     echo "FAIL final check: got '$$actual' want '$$expected'"; fail=1; \
	 fi; \
	 if [ $$fail -eq 0 ]; then \
	     echo "GREEN — all checks passed"; \
	 else \
	     echo "RED — some checks failed"; exit 1; \
	 fi

# ── check ────────────────────────────────────────────────────────────────────
check: $(STUB_BIN) $(SOLN_BIN)
	@echo "check: raw_cat — stub and solution linked"

# ── build rules ──────────────────────────────────────────────────────────────
$(STUB_BIN): $(STUB_SRC) | $(BUILD)
	$(CC) -nostdlib -static -no-pie -o $@ $<

$(SOLN_BIN): $(SOLN_SRC) | $(BUILD)
	$(CC) -nostdlib -static -no-pie -o $@ $<

$(BUILD):
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD)
