CC      ?= cc
BUILD   := build
O0_ASM  := $(BUILD)/clamp_O0.s
O2_ASM  := $(BUILD)/clamp_O2.s

.PHONY: test solve check clean
.DEFAULT_GOAL := test

# RED: fail until learner removes all TODO markers from notes.md
test:
	@if grep -q 'TODO' notes.md; then \
	    echo "FAIL: notes.md still contains TODO markers."; \
	    echo "      Run 'make solve', read the generated .s files, then"; \
	    echo "      answer every question in notes.md and remove the TODOs."; \
	    exit 1; \
	fi
	@echo "OK: no TODO markers found in notes.md"

# GREEN: compile at both optimisation levels, assert O2 output is shorter
solve: $(O0_ASM) $(O2_ASM)
	@O0_LINES=$$(wc -l < $(O0_ASM)); \
	 O2_LINES=$$(wc -l < $(O2_ASM)); \
	 echo "clamp_O0.s: $${O0_LINES} lines"; \
	 echo "clamp_O2.s: $${O2_LINES} lines"; \
	 if [ "$$O2_LINES" -ge "$$O0_LINES" ]; then \
	     echo "FAIL: expected O2 output to be shorter than O0 output"; \
	     exit 1; \
	 fi; \
	 echo "OK: -O2 output ($$O2_LINES lines) is shorter than -O0 ($$O0_LINES lines)"

check: solve

$(BUILD):
	mkdir -p $(BUILD)

$(O0_ASM): reference.c | $(BUILD)
	$(CC) -O0 -S -masm=intel -o $@ $<

$(O2_ASM): reference.c | $(BUILD)
	$(CC) -O2 -S -masm=intel -o $@ $<

clean:
	rm -rf $(BUILD)
