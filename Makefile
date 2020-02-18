
CFLAGS = -Wall -g
CC     = gcc $(CFLAGS)

commando: commando.o cmd.o cmdcol.o util.o
	$(CC) -o commando.o cmd.o cmdcol.o util.o

commando.o: commando.c
	$(CC) -c $<

cmd.o: cmd.c
	$(CC) -c $<

cmdcol.o: cmdcol.c
	$(CC) -c $<

util.o: util.c
	$(CC) -c $^
