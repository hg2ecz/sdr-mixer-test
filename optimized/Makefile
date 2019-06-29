CC=gcc
CFLAGS=-Wall -Ofast -march=native -funroll-all-loops
CFLAGS+=-DSAMPLELEN4=2500 -DITERATION=10000
CFLAGS+=-DFLOATVECBENCH
LDFLAGS=-lm

OBJS=main.o mixer_rotate_float.o mixer_rotate.o mixer_table.o mixer_rotate_float_vec.o
TARGET=mixertest

all: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
