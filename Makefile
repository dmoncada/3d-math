# The Makefile used for building the 3D math library.
# Author: David Moncada

CXX            := clang++

# Where to find the source code.
SRC_DIR        := src

# Where to place the compiled code.
OBJ_DIR        := obj

# Build the list of object files to compile.
_OBJS          := $(subst .cpp,.o,$(wildcard $(SRC_DIR)/*.cpp))
OBJS           := $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(_OBJS))

TESTS          := tests

# Where to find the source test code.
TESTS_SRC_DIR  := test/src

# Where to place the compiled test code.
TESTS_OBJS_DIR := test/obj

# Build the list of object test files to compile.
_TESTS_OBJS    := $(subst .cpp,.o,$(wildcard $(TESTS_SRC_DIR)/*.cpp))
TESTS_OBJS     := $(patsubst $(TESTS_SRC_DIR)/%,$(TESTS_OBJS_DIR)/%,$(_TESTS_OBJS))

# Where to place the documentation.
DOC_DIR        := doc

# Flags passed to the C++ compiler.
CXXFLAGS += -Wall -Wextra -Werror -std=c++11 -Iinclude

# Flags passed to the linker.
LDFLAGS  += -lgtest

.PHONY: all clean doc help test

# #######
# Targets
# #######

all: doc test

clean:
	@rm -fr $(DOC_DIR) $(OBJ_DIR) $(TESTS_OBJS_DIR) $(TESTS)

doc:
	@doxygen Doxyfile

help:
	@echo 'Targets:'
	@echo ''
	@echo ' all      - Builds all targets marked with [*].'
	@echo ' clean    - Removes all generated files.'
	@echo ' *doc     - Builds the documentation.'
	@echo ' help     - Show this help message.'
	@echo ' *test    - Builds the test suite.'
	@echo ' print-%  - Prints the value of variable %.'

test: $(TESTS)

# The following rule will build and run the test suite after building every
# required .o file.

$(TESTS): $(OBJS) $(TESTS_OBJS)
	$(CXX) $(CPPFLAGS) $(OBJS) $(TESTS_OBJS) $(LDFLAGS) -o $@
	./$@ # Execute the test suite.

# The following two rules will build every .o file that is to be placed in
# OBJ_DIR from its corresponding .cpp file living in SRC_DIR. They will also
# create OBJ_DIR if it doesn't exist.

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TESTS_OBJS_DIR)/%.o: $(TESTS_SRC_DIR)/%.cpp
	@mkdir -p $(TESTS_OBJS_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

print-%:
	@echo '$*=$($*)'
