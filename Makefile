
CFLAGS = -Wall -g
CC     = gcc $(CFLAGS)

commando: commando.o cmd.o cmdcol.o util.o commando.h
	$(CC) -o commando commando.o cmd.o cmdcol.o util.o commando.h

commando.o: commando.c
	$(CC) -c $<

cmd.o: cmd.c
	$(CC) -c $<

cmdcol.o: cmdcol.c
	$(CC) -c $<

util.o: util.c
	$(CC) -c $^

clean:
	rm -f *.o commando
