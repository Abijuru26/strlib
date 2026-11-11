CC = gcc
CFLAGS = -Wall -Wextra -g

strlib: strlib.c
	$(CC) $(CFLAGS) -o strlib strlib.c

clean:
	rm -f strlib
