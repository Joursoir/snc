CC = gcc
CFLAGS = -Wall -lm
PREFIX ?= /usr/local/bin
EXECUTABLE = snc

.PHONY: all clean install uninstall
all:
	@$(CC) $(CFLAGS) snc.c -o $(EXECUTABLE)

clean:
	@rm -f $(EXECUTABLE) *.o

install: all
	@echo installing snc to $(PREFIX)
	@install -m 755 $(EXECUTABLE) $(PREFIX)

uninstall:
	@rm -vf $(PREFIX)/$(EXECUTABLE) 