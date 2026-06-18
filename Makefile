# Top-level Makefile for x86-64-asm-mooc.

EXERCISES := $(sort $(dir $(wildcard part*/*/Makefile)))

.PHONY: help test-all solve-all check-all objdump-all clean
.DEFAULT_GOAL := help

help:
	@echo "x86-64-asm-mooc targets:"
	@echo "  make test-all    - run stub tests (RED by design)"
	@echo "  make solve-all   - run reference solutions (must pass)"
	@echo "  make check-all   - compile stubs and solutions"
	@echo "  make objdump-all - disassemble reference binaries"
	@echo "  make clean       - remove build artifacts"
	@echo ""
	@echo "Exercises discovered:"
	@for d in $(EXERCISES); do echo "  $$d"; done

test-all:
	@for d in $(EXERCISES); do 		echo "==> $$d (stub: RED until implemented)"; 		$(MAKE) -C $$d test || true; 	done

solve-all:
	@set -e; for d in $(EXERCISES); do echo "==> $$d (solution)"; $(MAKE) -C $$d solve; done

check-all:
	@set -e; for d in $(EXERCISES); do echo "==> $$d (check)"; $(MAKE) -C $$d check; done

objdump-all:
	@set -e; for d in $(EXERCISES); do echo "==> $$d (objdump)"; $(MAKE) -C $$d objdump; done

clean:
	@for d in $(EXERCISES); do $(MAKE) -C $$d clean >/dev/null 2>&1 || true; done
	@echo "cleaned."
