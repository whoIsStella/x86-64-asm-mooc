NAME      := exit_code
BUILD     := build
STUB_SRC  := src/$(NAME).S
SOLN_SRC  := solution/$(NAME).S
STUB_BIN  := $(BUILD)/prog_stub
SOLN_BIN  := $(BUILD)/prog_solution

CC        ?= cc
ASMFLAGS  := -nostdlib -static -no-pie

.PHONY: test solve check clean
.DEFAULT_GOAL := test

$(BUILD):
	mkdir -p $(BUILD)

$(STUB_BIN): $(STUB_SRC) | $(BUILD)
	$(CC) $(ASMFLAGS) -o $@ $<

$(SOLN_BIN): $(SOLN_SRC) | $(BUILD)
	$(CC) $(ASMFLAGS) -o $@ $<

test: $(STUB_BIN)
	@echo "--- test (stub, expect FAIL) ---"
	@./$(STUB_BIN); ec=$$?; \
	 if test $$ec -eq 42; then \
	   echo "UNEXPECTED PASS — stub should be RED"; exit 1; \
	 else \
	   echo "FAIL (expected — stub exited $$ec, not 42)"; exit 0; \
	 fi

solve: $(SOLN_BIN)
	@echo "--- solve (solution, expect PASS) ---"
	@./$(SOLN_BIN); ec=$$?; \
	 if test $$ec -eq 42; then \
	   echo "PASS (exit code $$ec)"; \
	 else \
	   echo "FAIL: expected exit 42, got $$ec"; exit 1; \
	 fi

check: $(STUB_BIN) $(SOLN_BIN)
	@echo "check: $(NAME) — stub and solution built"

clean:
	rm -rf $(BUILD)
