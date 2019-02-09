CC = g++
CC_FLAGS = -g

SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
EXEC = car

$(EXEC): $(OBJECTS)
	$(CC) -Wall -pthread -c $(OBJECTS) -o $(EXEC) -lwiringPi -lcrypt -lrt
	rm -f *.o *~

%.o: %.c
	$(CC) -c $(CC_FLAGS) $< -o $@