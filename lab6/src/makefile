CC=gcc
CFLAGS=-I. -std=c99

all : server client

server : server.c
	$(CC) -lpthread -o server server.c -L. -lmultmod $(CFLAGS)

client : client.c
	$(CC) -o client client.c -L. -lmultmod $(CFLAGS)

clean :
	rm -f client server