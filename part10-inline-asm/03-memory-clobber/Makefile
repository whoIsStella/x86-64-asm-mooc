NAME    := negate_all
CC      := cc
CFLAGS  := -std=gnu11 -Wall -Wextra -g -Iinclude -I../../vendor/ctest
BUILD   := build

.PHONY: test solve check clean
.DEFAULT_GOAL := test

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/test_stub: tests/test_$(NAME).c src/$(NAME).c include/$(NAME).h | $(BUILD)
	$(CC) $(CFLAGS) tests/test_$(NAME).c src/$(NAME).c -o $@

$(BUILD)/test_solution: tests/test_$(NAME).c solution/$(NAME).c include/$(NAME).h | $(BUILD)
	$(CC) $(CFLAGS) tests/test_$(NAME).c solution/$(NAME).c -o $@

test: $(BUILD)/test_stub
	@echo "--- Running stub (expect failures) ---"
	-./$(BUILD)/test_stub; true

solve: $(BUILD)/test_solution
	@echo "--- Running solution (expect all pass) ---"
	./$(BUILD)/test_solution

check: $(BUILD)/test_stub $(BUILD)/test_solution
	@echo "=== Stub ==="
	-./$(BUILD)/test_stub; true
	@echo "=== Solution ==="
	./$(BUILD)/test_solution

clean:
	rm -rf $(BUILD)
