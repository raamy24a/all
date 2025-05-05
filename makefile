SRC := $(wildcard *.c)
HEADERS := $(wildcard *.h)
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: program

program: $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) $(SRC) -c $@

clean:
	rm -f program
