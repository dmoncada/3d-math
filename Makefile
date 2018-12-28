# The Makefile used for building the 3D math library.
# Author: David Moncada

CXX           ?= clang++

SRC_DIR       := src
OBJ_DIR       := bin
LIB_DIR       := lib

SRC           := $(wildcard $(SRC_DIR)/*.cpp)
OBJ           := $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRC:.cpp=.o))
LIB           := $(LIB_DIR)/lib3d-math.a

TESTS         := tests

TESTS_SRC_DIR := test/src
TESTS_OBJ_DIR := test/bin

TESTS_SRC     := $(wildcard $(TESTS_SRC_DIR)/*.cpp)
TESTS_OBJ     := $(patsubst $(TESTS_SRC_DIR)/%,$(TESTS_OBJ_DIR)/%,$(TESTS_SRC:.cpp=.o))

DOC_DIR       := doc

CXXFLAGS      += -Wall -Wextra -Werror -std=c++11 -Iinclude
LDFLAGS       += -lgtest -Llib -l3d-math

.PHONY: all clean doc help lib tags test

# #######
# Targets
# #######

all: doc tags test

clean:
	@rm -fr $(OBJ_DIR) $(LIB_DIR) $(TESTS_OBJ_DIR) $(TESTS) $(DOC_DIR) tags

doc:
	@doxygen Doxyfile

help:
	@echo 'Targets:'
	@echo ''
	@echo ' all      - Builds all targets marked with [*].'
	@echo ' clean    - Removes all generated files.'
	@echo ' *doc     - Builds the documentation.'
	@echo ' help     - Show this help message.'
	@echo ' *lib     - Builds the statically-linked library.'
	@echo ' *tags    - Builds tags for vim.'
	@echo ' *test    - Builds the test suite.'
	@echo ' print-%  - Prints the value of variable %.'

lib: $(LIB)

tags:
	@find include -type f -and -iname '*.h' | xargs ctags
	@find $(SRC_DIR) -type f -and -iname '*.cpp' | xargs ctags -a

test: $(TESTS)

$(TESTS): $(LIB) $(TESTS_OBJ)
	$(CXX) $(CPPFLAGS) $(TESTS_OBJ) $(LDFLAGS) -o $@
	./$@ # Execute the test suite.

$(LIB): $(OBJ)
	@mkdir -p $(LIB_DIR)
	$(AR) rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TESTS_OBJ_DIR)/%.o: $(TESTS_SRC_DIR)/%.cpp
	@mkdir -p $(TESTS_OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

print-%:
	@echo '$*=$($*)'
