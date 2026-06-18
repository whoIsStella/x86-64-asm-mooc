# Shared per-exercise Makefile fragment for x86-64-asm-mooc.

ROOT      ?= ../..
VENDOR    := $(ROOT)/vendor/ctest

CC        ?= cc
OBJDUMP   ?= objdump
CFLAGS    := -std=c11 -Wall -Wextra -g -Iinclude -I$(VENDOR)
ASFLAGS   := -g
LDFLAGS   := -no-pie
LDLIBS    :=
BUILD     := build
TEST_SRC  := tests/test_$(NAME).c
STUB_SRC  := src/$(NAME).S
SOLN_SRC  := solution/$(NAME).S

.PHONY: test solve check objdump clean

test: $(BUILD)/test_stub
	./$(BUILD)/test_stub

solve: $(BUILD)/test_solution
	./$(BUILD)/test_solution

check: $(BUILD)/test_stub $(BUILD)/test_solution
	@echo "check: $(NAME) — stub and solution linked"

objdump: $(BUILD)/test_solution
	$(OBJDUMP) -d -M intel $(BUILD)/test_solution | sed -n '/<$(NAME)>:/,+24p'

$(BUILD)/test_stub: $(TEST_SRC) $(STUB_SRC) include/$(NAME).h | $(BUILD)
	$(CC) $(CFLAGS) $(LDFLAGS) $(TEST_SRC) $(STUB_SRC) -o $@ $(LDLIBS)

$(BUILD)/test_solution: $(TEST_SRC) $(SOLN_SRC) include/$(NAME).h | $(BUILD)
	$(CC) $(CFLAGS) $(LDFLAGS) $(TEST_SRC) $(SOLN_SRC) -o $@ $(LDLIBS)

$(BUILD):
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD)
