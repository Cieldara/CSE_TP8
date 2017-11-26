CC=gcc
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS=
EXEC=test test-format test-many-open test-rand

all: $(EXEC)

test: test.o stdes.o
	$(CC) -o test test.o stdes.o $(LDFLAGS)

test-format: test-format.o stdes.o
	$(CC) -o test-format test-format.o stdes.o $(LDFLAGS)

test-many-open: test-many-open.o stdes.o
	$(CC) -o test-many-open test-many-open.o stdes.o $(LDFLAGS)

test-rand: test-rand.o stdes.o
	$(CC) -o test-rand test-rand.o stdes.o $(LDFLAGS)

test.o: test.c
	$(CC) -o test.o -c test.c $(CFLAGS)

stdes.o: stdes.c stdes.h
	$(CC) -o stdes.o -c stdes.c $(CFLAGS)

clean:
	rm -rf *.o $(EXEC)
