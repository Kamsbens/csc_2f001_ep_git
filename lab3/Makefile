.SUFFIXES:
.SECONDARY:
.PHONY: all clean

CC = gcc
CFLAGS = -Wall -Werror -g
LDFLAGS =
LIBS =

all: army-pokemon army-zombie

army-%: main.o monster.o army-%.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Recompiler si un des headers utilises a change.
main.o monster.o army-pokemon.o army-zombie.o: monster.h macro.h
main.o army-pokemon.o army-zombie.o: army.h

clean:
	rm -f *.o army-pokemon army-zombie
