CC=gcc
CFLAGS=-Wall -Ofast -march=native -funroll-all-loops
CFLAGS+=-DFLOATBENCH
LDFLAGS=-lm

OBJS=main.o mixer_rotate_float.o mixer_rotate.o mixer_table.o
TARGET=mixertest

all: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
