.PHONY: all clean debug release

# Define required raylib variables
PROJECT_NAME       ?= main
RAYLIB_VERSION     ?= 5.1-dev
RAYLIB_PATH        ?= C:/raylib/raylib

# Define compiler path on Windows
COMPILER_PATH      ?= C:/raylib/w64devkit/bin

# Define default options
# One of PLATFORM_DESKTOP, PLATFORM_ANDROID, PLATFORM_WEB
PLATFORM           ?= PLATFORM_DESKTOP

# Library type used for raylib: STATIC (.a) or SHARED (.so/.dll)
RAYLIB_LIBTYPE     ?= STATIC

# Build mode for project: DEBUG or RELEASE
BUILD_MODE         ?= RELEASE

# Build folders
BUILD_DIR          ?= bin
OBJ_ROOT           ?= obj
OBJ_DIR            ?= $(OBJ_ROOT)/$(BUILD_MODE)

# Determine PLATFORM_OS in case PLATFORM_DESKTOP selected
ifeq ($(PLATFORM),PLATFORM_DESKTOP)
    ifeq ($(OS),Windows_NT)
        PLATFORM_OS=WINDOWS
        export PATH := $(COMPILER_PATH):$(PATH)
        MAKE = $(COMPILER_PATH)/mingw32-make.exe
        SHELL = $(COMPILER_PATH)/sh.exe
    else
        UNAMEOS=$(shell uname)
        ifeq ($(UNAMEOS),Linux)
            PLATFORM_OS=LINUX
            MAKE = make
        endif
        ifeq ($(UNAMEOS),Darwin)
            PLATFORM_OS=OSX
            MAKE = make
        endif
    endif
endif

# Define raylib release directory for compiled library.
RAYLIB_RELEASE_PATH ?= $(RAYLIB_PATH)/src

# Define compiler
CC = g++

ifeq ($(PLATFORM_OS),OSX)
    CC = clang++
endif

# Define compiler flags
CFLAGS += -Wall -std=c++14 -D_DEFAULT_SOURCE -Wno-missing-braces

ifeq ($(BUILD_MODE),DEBUG)
    CFLAGS += -g -O0
else
    CFLAGS += -s -O1
endif

ifeq ($(PLATFORM),PLATFORM_DESKTOP)
    ifeq ($(PLATFORM_OS),WINDOWS)
        RESOURCE_FILE = $(RAYLIB_PATH)/src/raylib.rc.data
    endif
endif

# Define include paths for required headers
INCLUDE_PATHS = -I. -Iinclude -I$(RAYLIB_PATH)/src -I$(RAYLIB_PATH)/src/external

# Define library paths containing required libs.
LDFLAGS = -L. -Llib -L$(RAYLIB_RELEASE_PATH) -L$(RAYLIB_PATH)/src

# Define libraries required on linking
ifeq ($(PLATFORM),PLATFORM_DESKTOP)
    ifeq ($(PLATFORM_OS),WINDOWS)
        LDLIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
        TARGET_EXT = .exe
    endif
    ifeq ($(PLATFORM_OS),LINUX)
        LDLIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
    endif
    ifeq ($(PLATFORM_OS),OSX)
        LDLIBS = -lraylib -framework OpenGL -framework OpenAL -framework Cocoa -framework IOKit
    endif
endif

TARGET = $(BUILD_DIR)/$(PROJECT_NAME)$(TARGET_EXT)

# Define a recursive wildcard function
rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

# Find every .cpp file in the project, including nested source folders.
SRC := $(sort $(patsubst ./%,%,$(call rwildcard,./,*.cpp)))
SRC := $(filter-out $(OBJ_ROOT)/% $(BUILD_DIR)/%,$(SRC))
OBJS := $(addprefix $(OBJ_DIR)/,$(SRC:.cpp=.o))

# Default target entry
all: $(TARGET)

debug:
	$(MAKE) BUILD_MODE=DEBUG

release:
	$(MAKE) BUILD_MODE=RELEASE

# Project target defined by PROJECT_NAME
$(TARGET): $(OBJS)
	@mkdir -p "$(BUILD_DIR)"
	$(CC) -o $@ $(OBJS) $(RESOURCE_FILE) $(CFLAGS) $(INCLUDE_PATHS) $(LDFLAGS) $(LDLIBS) -D$(PLATFORM)

# Compile source files, preserving source folders inside obj/
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p "$(dir $@)"
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE_PATHS) -D$(PLATFORM)

# Clean build outputs
clean:
	rm -rf "$(OBJ_ROOT)"
ifeq ($(PLATFORM_OS),WINDOWS)
	rm -f "$(BUILD_DIR)"/*.exe
else
	rm -f "$(BUILD_DIR)/$(PROJECT_NAME)"
endif
	@echo Cleaning done
