PREFIX = /usr/local
TARGET = $(DESTDIR)$(PREFIX)

CC = gcc
IDIR = include
CFLAGS = -Wall -I$(IDIR)

CDIR = src
ODIR = src

_DEPS = helpers.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
_OBJ = helpers.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

EXEC = todo

$(ODIR)/%.o: $(CDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: install clean

install: $(EXEC)
	install -Dm 755 $(EXEC) $(TARGET)/bin/$(EXEC)
clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ $(EXEC)
