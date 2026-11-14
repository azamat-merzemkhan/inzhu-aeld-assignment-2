CC = $(CROSS_COMPILE)gcc
CFLAGS ?= -Wall -Wextra -Werror -std=c11 -O2
LDFLAGS ?=
.PHONY: all clean
all: writer
writer: writer.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)
clean:
	rm -f writer *.o
