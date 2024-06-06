# Compiler and flags
CXX = g++
CXXFLAGS = -g -std=c++11 -Wall -Wextra -pedantic

# Directories
SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = bin
INC_DIR = .

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Executable name
TARGET = $(BIN_DIR)/catan

# Create directories if they don't exist
$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c -o $@ $<

# Clean up object files and executable
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

# Phony targets
.PHONY: all clean
