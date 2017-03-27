CC=gcc
CFLAGS=-Wall -g

fib: main.o fib.o
	$(CC) -o fib main.o fib.o $(CFLAGS)

.c.o:
	$(CC) -c $<

clean:
	rm *.o fib
