CC=gcc
CFLAGS=-ggdb -Wall -Wextra -O0
DEPS = shellfuncts.h helperfuncts.h
OBJ = myshell.o shellfuncts.o helperfuncts.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

myshell: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean

clean:
	rm -f *.o *~ myshell 
