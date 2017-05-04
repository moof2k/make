# Allows CFLAGS overrides using STYLE=debug or STYLE=opt
# Build separate binaries based on STYLE, stores temporaries in obj/

# Override build STYLE on the command line using make STYLE=debug.
STYLE ?= opt
TARGET = $(shell uname -s)_$(STYLE)
$(info Building for $(TARGET))

CC = clang++ -I.
CFLAGS = -MMD -Wall -Werror
LDFLAGS = -lm

# Modify build variables based on selected build STYLE.
ifeq ($(STYLE), debug)
CFLAGS += -DDEBUG -g
else
ifeq ($(STYLE), opt)
CFLAGS += -O3
else
$(error Unsupported build style $(STYLE))
endif
endif

# Find all project modules.
EXCLUDE_MODULES = obj bin lib
MODULES = $(filter-out $(EXCLUDE_MODULES), $(patsubst %/, %, $(wildcard */)))

# Find all binary targets located within the project.
BINS = $(patsubst %.cc, bin/$(TARGET)/%, $(shell find * -name *_bin.cc))

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

lib/$(TARGET)/lib$(MODULE).a: $(patsubst %.cc, obj/$(TARGET)/%.o, $(filter-out %_bin.cc, $(wildcard $(MODULE)/*.cc)))
	@mkdir -p lib/$(TARGET)
	ar rcs $$@ $$^

# For each _bin.cc found within this module, invoke the BIN_RULE on it,
# supplying it with the list of dependencies found in the module/deps file.
$(foreach BIN, $(patsubst %.cc, %, $(wildcard $(MODULE)/*_bin.cc)), \
	$(eval $(call BIN_RULE, bin/$(TARGET)/$(BIN), \
		$(patsubst %, lib/$(TARGET)/%, $(shell cat $(MODULE)/deps)) obj/$(TARGET)/$(BIN).o)))

endef

# Invoke the MODULE_RULE for each of the MODULES.
$(foreach MODULE, $(MODULES), $(eval $(MODULE_RULE)))

# The 'all' target builds all of the discovered binary targets.
all: $(BINS)

obj/$(TARGET)/%.o: %.cc
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf obj lib bin