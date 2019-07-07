CC=gcc
CFLAGS=-Wall -Ofast -march=native -funroll-all-loops
LDFLAGS=-lm

OBJS=main.o decimator.o
TARGET=decimatortest

all: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
