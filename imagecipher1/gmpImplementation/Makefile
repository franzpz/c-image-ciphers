
OBJECTS = 
CFLAGS = -std=c99 -g -Wall  
LDLIBS = 
CC=gcc


all: main 

imagecipher1.o: imagecipher1.c imagecipher1.h 
	$(CC) $(CFLAGS) $(LDLIBS) -c imagecipher1.c -lm -lgmp

test.o: test.c 
	$(CC) $(CFLAGS) $(LDLIBS) -c test.c 

test: clean imagecipher1.o test.o 
	$(CC) $(CFLAGS) $(LDLIBS) imagecipher1.o test.o -lm -lgmp -o test 

main.o: main.c 
	$(CC) $(CFLAGS) $(LDLIBS) -c main.c 

main: imagecipher1.o main.o 
	$(CC) $(CFLAGS) $(LDLIBS) imagecipher1.o main.o -lm -lgmp -o main 

clean:
	rm -f *.o main test

