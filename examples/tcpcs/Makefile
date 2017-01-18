CC=gcc
CFLAGS=  -pedantic -ansi
LIBS = wrapsock.o writen.o

server: wrapsock.o writen.o
	$(CC) $(CFLAGS) -o server $(LIBS) server.c
.c: 
	$(CC) -o $@ $(LIBS) $<
.c.o:
	$(CC) -c $<

