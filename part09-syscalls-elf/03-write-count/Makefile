NAME      := write_count
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
	@out=$$(./$(STUB_BIN) 2>/dev/null); \
	 if test "$$out" = "ABCABCABC"; then \
	   echo "UNEXPECTED PASS — stub should be RED"; exit 1; \
	 else \
	   echo "FAIL (expected — stub output was '$$out', not 'ABCABCABC')"; exit 0; \
	 fi

solve: $(SOLN_BIN)
	@echo "--- solve (solution, expect PASS) ---"
	@out=$$(./$(SOLN_BIN)); \
	 if test "$$out" = "ABCABCABC"; then \
	   echo "PASS"; \
	 else \
	   echo "FAIL: expected 'ABCABCABC', got '$$out'"; exit 1; \
	 fi
	@./$(SOLN_BIN) >/dev/null; test $$? -eq 0

check: $(STUB_BIN) $(SOLN_BIN)
	@echo "check: $(NAME) — stub and solution built"

clean:
	rm -rf $(BUILD)
