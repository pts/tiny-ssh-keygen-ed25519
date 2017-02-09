# by pts@fazekas.hu at Tue Feb  7 15:44:55 CET 2017

CC = gcc
CFLAGS = -s -Os -ansi -pedantic \
    -W -Wall -Wextra -Werror=implicit -Werror=implicit-function-declaration \
    -Werror=implicit-int -Werror=pointer-sign -Werror=pointer-arith
CDEFS =
SOURCES = ssh_keygen_ed25519.c

.PHONY: all clean

all: ssh_keygen_ed25519

clean:
	rm -f core *.o ssh_keygen_ed25519

ssh_keygen_ed25519: $(SOURCES)
	$(CC) $(CFLAGS) -o ssh_keygen_ed25519 $(CDEFS) $(SOURCES)
	ls -ld ssh_keygen_ed25519
