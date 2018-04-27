CC = gcc
CFLAGS = -Wall -ansi -pedantic
MAIN = fw
OBJS = fw.c hash.c node.c resize.c
all : $(MAIN)


$(MAIN) : $(OBJS) fw.h
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

fw.o : fw.c fw.h
	$(CC) $(CFLAGS) -c fw.c

hash.o : hash.c fw.h
	$(CC) $(CFLAGS) -c hash.c

node.o : node.c fw.h
	$(CC) $(CFLAGS) -c node.c

resize.o : resize.c fw.h
	$(CC) $(CFLAGS) -c resize.c

clean :
	rm *.o $(MAIN) core
