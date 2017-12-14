CC=gcc
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS=
EXEC=test test-format test_general test_write_and_read_int test_write_and_read_string
TEST_FILES=resultat input output input_test resultat_etape1 liste_number chaines

all: $(EXEC)

exec:
	make clean
	make
	touch input
	touch resultat
	touch liste_number
	touch chaines
	echo test 10 dix lecture vingt 20 > output
	echo "Bonjour, ceci est le test de l'étape 1 !" > input_test
	touch resultat_etape1
	./test_general input_test resultat_etape1
	./test test.c resultat
	cat resultat
	./test-format input output
	cat input
	./test_write_and_read_int liste_number
	./test_write_and_read_string chaines

test: test.o stdes.o
	$(CC) -o test test.o stdes.o $(LDFLAGS)

test-format: test-format.o stdes.o
	$(CC) -o test-format test-format.o stdes.o $(LDFLAGS)

test_general: test_general.o stdes.o
	$(CC) -o test_general test_general.o stdes.o $(LDFLAGS)

test_write_and_read_int: test_write_and_read_int.o stdes.o
	$(CC) -o test_write_and_read_int test_write_and_read_int.o stdes.o $(LDFLAGS)

test_write_and_read_string: test_write_and_read_string.o stdes.o
	$(CC) -o test_write_and_read_string test_write_and_read_string.o stdes.o $(LDFLAGS)

test.o: test.c
	$(CC) -o test.o -c test.c $(CFLAGS)



stdes.o: stdes.c stdes.h
	$(CC) -o stdes.o -c stdes.c $(CFLAGS)

clean:
	rm -rf *.o $(EXEC) $(TEST_FILES)
