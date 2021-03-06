SRCD := src
OBJD := obj
BIND := bin

CC = gcc
CFLAGS = -Wall -Wextra
VPATH = src

OBJS := $(patsubst $(SRCD)/%.c,$(OBJD)/%.o,$(wildcard $(SRCD)/*.c))
EXEC = $(BIND)/prog

release: CFLAGS += -DNDEBUG
release: all

debug: all

all: $(OBJD) $(BIND) | $(EXEC)

$(EXEC): $(OBJS)
	$(CC) -o $@ $^

$(OBJD)/main.o: main.c circular_buffer.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJD)/circular_buffer.o: circular_buffer.c circular_buffer.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJD):
	mkdir $@

$(BIND):
	mkdir $@

.PHONY : clean
clean:
	rm $(OBJS) $(EXEC)
