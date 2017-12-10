CC=gcc
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS=
EXEC=test test-format test_general
TEST_FILES=resultat input output input_test resultat_etape1

all: $(EXEC)

exec:
	touch input
	touch resultat
	./test test.c resultat
	echo test 10 dix lecture vingt 20 > output
	./test-format input output
	echo "Bonjour, ceci est le test de l'étape 1 !" > input_test
	touch resultat_etape1
	./test_general input_test resultat_etape1

test: test.o stdes.o
	$(CC) -o test test.o stdes.o $(LDFLAGS)

test-format: test-format.o stdes.o
	$(CC) -o test-format test-format.o stdes.o $(LDFLAGS)

test-many-open: test-many-open.o stdes.o
	$(CC) -o test-many-open test-many-open.o stdes.o $(LDFLAGS)

test_general: test_general.o stdes.o
	$(CC) -o test_general test_general.o stdes.o $(LDFLAGS)

test-rand: test-rand.o stdes.o
	$(CC) -o test-rand test-rand.o stdes.o $(LDFLAGS)

test.o: test.c
	$(CC) -o test.o -c test.c $(CFLAGS)



stdes.o: stdes.c stdes.h
	$(CC) -o stdes.o -c stdes.c $(CFLAGS)

clean:
	rm -rf *.o $(EXEC) $(TEST_FILES)
