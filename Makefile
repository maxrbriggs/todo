IDIR =include
CC = gcc
CFLAGS = -I$(IDIR)

CDIR = src

ODIR = src/obj

_DEPS = helpers.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
_OBJ = helpers.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(CDIR)/%.c $(DEPS)
	$(CC) -Wall -c -o $@ $< $(CFLAGS)

todo: $(OBJ)
	$(CC) -Wall -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
