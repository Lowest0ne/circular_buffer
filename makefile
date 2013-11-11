SRCD := src
OBJD := obj
BIND := bin

CC = gcc
CFLAGS =
VPATH = src

OBJS := $(patsubst $(SRCD)/%.c,$(OBJD)/%.o,$(wildcard $(SRCD)/*.c))
EXEC = $(BIND)/prog

all: $(OBJD) $(BIND) | $(EXEC)

$(EXEC): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJD)/main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJD):
	mkdir $@

$(BIND):
	mkdir $@

.PHONY : clean
clean:
	rm $(OBJS) $(EXEC)