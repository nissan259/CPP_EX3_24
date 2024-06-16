# Compiler and flags
CXX = g++
CXXFLAGS = -g -std=c++11 -Wall -Wextra -pedantic `pkg-config --cflags opencv4`

# Directories
SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = bin
INC_DIR = .

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
SRC_FILES_WITHOUT_DEMO = $(filter-out $(SRC_DIR)/Demo.cpp, $(SRC_FILES))
SRC_FILES_TEST = $(SRC_DIR)/test.cpp $(SRC_DIR)/test_counter.cpp

# Object files
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))
OBJ_FILES_WITHOUT_DEMO = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES_WITHOUT_DEMO))
OBJ_FILES_TEST = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES_TEST))

# Executable name
TARGET = $(BIN_DIR)/catan
TARGET_TEST = $(BIN_DIR)/catan_tests

# Create directories if they don't exist
$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJ_FILES_WITHOUT_DEMO)
	$(CXX) $(CXXFLAGS) -o $@ $^ `pkg-config --libs opencv4`

# Link object files to create test executable
$(TARGET_TEST): $(OBJ_FILES_TEST) $(filter-out $(OBJ_DIR)/Demo.o, $(OBJ_FILES))
	$(CXX) $(CXXFLAGS) -o $@ $^ `pkg-config --libs opencv4`

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c -o $@ $<

# Clean up object files and executable
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET) $(TARGET_TEST)

# Phony targets
.PHONY: all clean test

# Test target
test: $(TARGET_TEST)
	./$(TARGET_TEST)
