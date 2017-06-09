
OBJECTS = 
CFLAGS = -std=c99 -g -Wall  
LDLIBS = 
CC=gcc


all: main 

imagecipher2.o: imagecipher2.c imagecipher2.h 
	$(CC) $(CFLAGS) $(LDLIBS) -c imagecipher2.c -lm

test.o: test.c 
	$(CC) $(CFLAGS) $(LDLIBS) -c test.c 

test: clean imagecipher2.o test.o 
	$(CC) $(CFLAGS) $(LDLIBS) imagecipher2.o test.o -lm -o test 

main.o: main.c 
	$(CC) $(CFLAGS) $(LDLIBS) -c main.c 

main: imagecipher2.o main.o 
	$(CC) $(CFLAGS) $(LDLIBS) imagecipher2.o main.o -lm -o main 

clean:
	rm -f *.o main test

