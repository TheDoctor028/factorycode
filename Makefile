BUILD_DIR ?= cmake-build-debug
SOURCE_FILES := $(shell find game lib/channel tests main.cpp -name "*.cpp" -o -name "*.hpp" -o -name "*.h" 2>/dev/null)

# Detect tools
CLANG_TIDY := $(shell which clang-tidy 2>/dev/null || echo /opt/homebrew/opt/llvm/bin/clang-tidy)
CLANG_FORMAT := $(shell which clang-format 2>/dev/null || echo /opt/homebrew/opt/llvm/bin/clang-format)
NINJA := $(shell which ninja 2>/dev/null || ls /Applications/CLion.app/Contents/bin/ninja/mac/*/ninja 2>/dev/null | head -n 1)

CMAKE_GEN_FLAGS :=
ifneq ($(NINJA),)
    CMAKE_GEN_FLAGS := -G Ninja -DCMAKE_MAKE_PROGRAM="$(NINJA)"
endif

.PHONY: all config build test test-verbose test-bdd test-integration lint tidy tidy-fix format format-check run clean help

all: build

help:
	@echo "Available Makefile targets:"
	@echo "  make config           - Configure CMake build directory ($(BUILD_DIR))"
	@echo "  make build            - Build all targets (factorycode and unit_tests)"
	@echo "  make test             - Run all tests via CTest"
	@echo "  make test-verbose     - Run all tests with detailed Catch2 output"
	@echo "  make test-bdd         - Run BDD scenario tests"
	@echo "  make test-integration - Run integration tests"
	@echo "  make lint / make tidy - Run clang-tidy static analysis on project sources"
	@echo "  make tidy-fix         - Run clang-tidy and automatically apply suggested fixes"
	@echo "  make format           - Format all C++ source files in-place using clang-format"
	@echo "  make format-check     - Check code formatting without modifying files"
	@echo "  make run              - Execute the main factorycode binary"
	@echo "  make clean            - Remove build artifacts from $(BUILD_DIR)"

config:
	cmake -B $(BUILD_DIR) -S . $(CMAKE_GEN_FLAGS)

build: config
	cmake --build $(BUILD_DIR) --target factorycode unit_tests

test: build
	ctest --test-dir $(BUILD_DIR) --output-on-failure

test-verbose: build
	./$(BUILD_DIR)/tests/unit_tests -s -d yes

test-bdd: build
	./$(BUILD_DIR)/tests/unit_tests "[bdd]" -s

test-integration: build
	./$(BUILD_DIR)/tests/unit_tests "[integration]" -s

lint: tidy

tidy: config
	@echo "Running clang-tidy..."
	@find game -name "*.cpp" -exec $(CLANG_TIDY) -p $(BUILD_DIR) {} +

tidy-fix: config
	@echo "Running clang-tidy with -fix..."
	@find game -name "*.cpp" -exec $(CLANG_TIDY) -p $(BUILD_DIR) -fix {} +

format:
	@echo "Formatting source files..."
	$(CLANG_FORMAT) -i $(SOURCE_FILES)

format-check:
	@echo "Checking source files format..."
	$(CLANG_FORMAT) --dry-run --Werror $(SOURCE_FILES)

run: build
	./$(BUILD_DIR)/factorycode

clean:
	rm -rf $(BUILD_DIR)
