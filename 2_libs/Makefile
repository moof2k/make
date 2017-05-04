# Builds a static library for each subdirectory in lib/
# Stores all temporary files in obj/

CC = clang++ -I.
CFLAGS = -MMD -g -Wall -Werror
LDFLAGS = -lm

# Find all project modules.
EXCLUDE_MODULES = obj bin lib
MODULES = $(filter-out $(EXCLUDE_MODULES), $(patsubst %/, %, $(wildcard */)))

# Find all binary targets located within the project.
BINS = $(patsubst %.cc, bin/%, $(shell find * -name *_bin.cc))

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
-include $(patsubst %.cc, obj/%.d, $(wildcard $(MODULE)/*.cc))

lib/lib$(MODULE).a: $(patsubst %.cc, obj/%.o, $(filter-out %_bin.cc, $(wildcard $(MODULE)/*.cc)))
	@mkdir -p lib
	ar rcs $$@ $$^

# For each _bin.cc found within this module, invoke the BIN_RULE on it,
# supplying it with the list of dependencies found in the module/deps file.
$(foreach BIN, $(patsubst %.cc, %, $(wildcard $(MODULE)/*_bin.cc)), \
	$(eval $(call BIN_RULE, bin/$(BIN), \
		$(patsubst %, lib/%, $(shell cat $(MODULE)/deps)) obj/$(BIN).o)))
endef

# Invoke the MODULE_RULE for each of the MODULES.
$(foreach MODULE, $(MODULES), $(eval $(MODULE_RULE)))

# The 'all' target builds all of the discovered binary targets.
all: $(BINS)

obj/%.o: %.cc
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf obj lib bin