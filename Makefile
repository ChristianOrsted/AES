
# Makefile for AES Encryption/Decryption System
# Project Structure with separate directories

# Compiler settings
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2 -I./include

# Directories
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
BIN_DIR = bin

# Target executable
TARGET = $(BIN_DIR)/aes_system

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

# Header files
HEADERS = $(wildcard $(INC_DIR)/*.h)

# Colors for output (optional, makes it prettier)
COLOR_RESET = \033[0m
COLOR_GREEN = \033[32m
COLOR_YELLOW = \033[33m
COLOR_CYAN = \033[36m

# Default target
all: directories $(TARGET)

# Create necessary directories
directories:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)

# Link object files to create executable
$(TARGET): $(OBJECTS)
	@echo "$(COLOR_GREEN)Linking...$(COLOR_RESET)"
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "$(COLOR_GREEN)Build complete! Run with: $(TARGET)$(COLOR_RESET)"

# Compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@echo "$(COLOR_CYAN)Compiling $<...$(COLOR_RESET)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	@echo "$(COLOR_YELLOW)Cleaning...$(COLOR_RESET)"
	rm -rf $(BUILD_DIR)/*.o $(TARGET)
	@echo "$(COLOR_GREEN)Clean complete!$(COLOR_RESET)"

# Deep clean (remove all generated directories)
distclean:
	@echo "$(COLOR_YELLOW)Deep cleaning...$(COLOR_RESET)"
	rm -rf $(BUILD_DIR) $(BIN_DIR)
	@echo "$(COLOR_GREEN)Deep clean complete!$(COLOR_RESET)"

# Run the program
run: all
	@echo "$(COLOR_CYAN)Running AES System...$(COLOR_RESET)"
	@echo ""
	@$(TARGET)

# Rebuild everything
rebuild: clean all

# Show project structure
tree:
	@echo "$(COLOR_CYAN)Project Structure:$(COLOR_RESET)"
	@tree -L 2 -I 'build|bin' || ls -R

# Show help
help:
	@echo "$(COLOR_CYAN)Available targets:$(COLOR_RESET)"
	@echo "  make all       - Build the project (default)"
	@echo "  make clean     - Remove object files and executable"
	@echo "  make distclean - Remove all generated files and directories"
	@echo "  make run       - Build and run the program"
	@echo "  make rebuild   - Clean and rebuild"
	@echo "  make tree      - Show project structure"
	@echo "  make help      - Show this help message"

# Debug: print variables
debug:
	@echo "$(COLOR_CYAN)Build Configuration:$(COLOR_RESET)"
	@echo "CXX       = $(CXX)"
	@echo "CXXFLAGS  = $(CXXFLAGS)"
	@echo "SRC_DIR   = $(SRC_DIR)"
	@echo "INC_DIR   = $(INC_DIR)"
	@echo "BUILD_DIR = $(BUILD_DIR)"
	@echo "BIN_DIR   = $(BIN_DIR)"
	@echo "TARGET    = $(TARGET)"
	@echo "SOURCES   = $(SOURCES)"
	@echo "OBJECTS   = $(OBJECTS)"
	@echo "HEADERS   = $(HEADERS)"

.PHONY: all directories clean distclean run rebuild tree help debug
