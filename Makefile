# ===== Project =====
TARGET = bin/main

# ===== Compiler =====
CXX = g++
CXXFLAGS = -Wall -std=c++14 -g -O0

# ===== Directories =====
SRC_DIR = src
INC_DIR = include
BIN_DIR = bin

# ===== Raylib paths (kept from your original working setup) =====
RAYLIB_SRC = C:/raylib/raylib/src

INCLUDES = -I. -I$(INC_DIR) -I$(RAYLIB_SRC) -I$(RAYLIB_SRC)/external
LIBS = -L. -Llib -L$(RAYLIB_SRC) -lraylib -lopengl32 -lgdi32 -lwinmm

# ===== Source files =====
SRC = $(wildcard $(SRC_DIR)/*.cpp) main.cpp

# ===== Object files → bin/ =====
OBJ = $(patsubst %.cpp,$(BIN_DIR)/%.o,$(notdir $(SRC)))

# ===== Default target =====
all: $(TARGET)

# ===== Link =====
$(TARGET): $(OBJ)
	$(CXX) -o $@ $(OBJ) $(LIBS)

# ===== Compile rules =====
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(INCLUDES)

$(BIN_DIR)/main.o: main.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(INCLUDES)

# ===== Ensure bin/ exists =====
$(shell if not exist $(BIN_DIR) mkdir $(BIN_DIR))

# ===== Clean =====
clean:
	del /Q bin\*.o bin\*.exe 2>nul || exit 0

.PHONY: all clean