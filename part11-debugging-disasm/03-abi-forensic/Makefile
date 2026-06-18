CC      ?= cc
CFLAGS  := -std=c11 -Wall -Wextra -g -no-pie
BUILD   := build

.PHONY: test solve check clean objdump
.DEFAULT_GOAL := test

# RED: broken version produces wrong values
test: $(BUILD)/test_broken
	@echo "(running broken version — failures below are expected)"; \
	./$(BUILD)/test_broken; EXIT=$$?; \
	if [ $$EXIT -eq 0 ]; then \
	    echo "UNEXPECTED PASS: broken version should fail tests"; \
	    exit 1; \
	fi; \
	echo "(above failures are expected — run 'make solve' for the fix)"; \
	exit $$EXIT

# GREEN: fixed version produces correct values AND report.md has no TODOs
solve: $(BUILD)/test_fixed
	./$(BUILD)/test_fixed
	@if grep -qE '^\*\*[^:]+:\*\* TODO$$|^TODO$$' report.md; then \
	    echo "FAIL: report.md still contains unanswered TODO markers."; \
	    echo "      Fill in your findings and remove all TODO answers, then re-run make solve."; \
	    exit 1; \
	fi
	@echo "OK: report.md is complete"

check: solve

objdump: $(BUILD)/test_broken
	objdump -d -M intel $(BUILD)/test_broken | sed -n '/<broken_abi>:/,+20p'

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/test_broken: test_broken_abi.c src/broken.S | $(BUILD)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD)/test_fixed: test_broken_abi.c solution/fixed.S | $(BUILD)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(BUILD)
