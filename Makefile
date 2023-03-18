CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99\

build:
	gcc client.c -o ipkcpc
clean:
	rm ipkcpc

