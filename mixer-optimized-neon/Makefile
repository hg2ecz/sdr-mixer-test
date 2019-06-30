CC=gcc
CFLAGS=-Wall -Ofast -march=native -funroll-all-loops
#SAMPLELEN4 = 1/4 SAMPLELEN
CFLAGS+=-DSAMPLELEN4=25000 -DITERATION=10000
CFLAGS+=-DFLOATVECBENCH
LDFLAGS=-lm

OBJS = main.o mixer_rotate_float.o mixer_rotate.o mixer_table.o
OBJS+= mixer_rotate_float_vec.o mixer_table_vec.o
TARGET=mixertest

all: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
