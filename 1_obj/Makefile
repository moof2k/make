# Stores all temporary files in obj/

CC = g++ -I.
CFLAGS = -MMD -g -Wall -Werror
LDFLAGS = -lm

OBJ_SRC = $(wildcard *.cc)
OBJ = $(OBJ_SRC:%.cc=obj/%.o)

BIN_SRC = $(filter %_bin.cc, $(OBJ_SRC))
BIN = $(BIN_SRC:.cc=)

all: $(BIN)

obj/.dirstamp:
	mkdir -p obj
	touch $@

obj/%.o: %.cc obj/.dirstamp
	$(CC) $(CFLAGS) -o $@ -c $<

%_bin: obj/%_bin.o $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -rf obj
	rm -rf *_bin

-include $(BIN_SRC:%.cc=obj/%.d)
