IDIR =../include
CC = gcc
CFLAGS = -I$(IDIR)

ODIR = obj

_DEPS = helpers.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
_OBJ = helpers.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -ggdb -c -o $@ $< $(CFLAGS)

todo: $(OBJ)
	$(CC) -ggdb -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
