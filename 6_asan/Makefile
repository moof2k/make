# Adds support for multi-level directory structures.

# Override build STYLE on the command line using make STYLE=debug.
STYLE ?= opt
TARGET = $(shell uname -s)_$(STYLE)

ifeq ($(filter debug opt asan, $(STYLE)), )
$(error Invalid build style $(STYLE))
endif

CFLAGS_debug = -DDEBUG -g
CFLAGS_opt = -O3
CFLAGS_asan = -O1 -fsanitize=address -fno-omit-frame-pointer
LDFLAGS_asan = -fsanitize=address

CC = clang++
CFLAGS = -I. -MMD -Wall -Werror
LDFLAGS = -lm

CFLAGS += ${CFLAGS_${STYLE}}
LDFLAGS += ${LDFLAGS_${STYLE}}

# Find all project modules.
MODULES = $(shell find * -type d -not -path "bin*" -not -path "obj*" -not -path "lib*")

# Find all binary targets located within the project.
BINS = $(patsubst %.cc, bin/$(TARGET)/%, $(shell find * -name *_bin.cc))

# Find all test targets located within the project.
TESTS = $(patsubst %.cc, bin/$(TARGET)/%, $(shell find * -name *_test.cc))
TEST_STAMPS = $(patsubst %, %.stamp, $(TESTS))

# The 'all' target builds all of the discovered binary and test targets.
all: $(BINS) $(TESTS)

# Build and run all tests
test: $(TEST_STAMPS)

%_test.stamp: %_test
	@echo === $^
	@rm -f $@
	@$^
	@touch $@

# Given a binary ($1) and a list of dependencies ($2), create a rule
# to build this binary.
define BIN_RULE
$1: $2
	@mkdir -p $(dir $1)
	$(CC) $(LDFLAGS) -o $$@ $$^ 
endef

# Given $(MODULE), create a rule to build a lib for all code in this
# module that doesn't end with _bin.cc. For each of the _bin.cc files,
# create a binary target.
define MODULE_RULE
-include $(patsubst %.cc, obj/$(TARGET)/%.d, $(wildcard $(MODULE)/*.cc))

lib/$(TARGET)/$(MODULE).a: $(patsubst %.cc, obj/$(TARGET)/%.o, $(filter-out %_bin.cc %_test.cc, $(wildcard $(MODULE)/*.cc)))
	@mkdir -p $(dir lib/$(TARGET)/$(MODULE))
	ar rcs $$@ $$^

# For each _bin/_test found within this module, invoke the BIN_RULE on it,
# supplying it with the list of dependencies found in the module/deps file.
$(foreach BIN, $(patsubst %.cc, %, $(wildcard $(MODULE)/*_bin.cc) $(wildcard $(MODULE)/*_test.cc)), \
	$(eval $(call BIN_RULE, bin/$(TARGET)/$(BIN), \
		$(patsubst %, lib/$(TARGET)/%.a, $(shell cat $(MODULE)/deps)) lib/$(TARGET)/$(MODULE).a obj/$(TARGET)/$(BIN).o)))

endef

# Invoke the MODULE_RULE for each of the MODULES.
$(foreach MODULE, $(MODULES), $(eval $(MODULE_RULE)))

obj/$(TARGET)/%.o: %.cc
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf obj lib bin

