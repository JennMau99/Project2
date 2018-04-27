CC = gcc
CFLAGS = -g  -Wall -ansi -pedantic
MAIN = fw
OBJS = fw.o
all : $(MAIN)

$(MAIN) : $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

fw.o : fw.c fw.h
	$(CC) $(CFLAGS) -c fw.c

clean :
	rm *.o $(MAIN)
