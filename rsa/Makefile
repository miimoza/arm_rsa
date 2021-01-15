CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -lsodium 
CLIBS = -lsodium
OBJS = rsa.o

.PHONY: all check clean

all: rsa
check: all
	./rsa
clean:
	rm -rf $(OBJS) rsa.o
