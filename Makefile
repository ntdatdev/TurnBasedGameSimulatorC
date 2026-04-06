CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
OBJ = main.o queue.o file.o
TARGET = battle

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

main.o: main.c queue.h file.h
	$(CC) $(CFLAGS) -c main.c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c

file.o: file.c file.h queue.h
	$(CC) $(CFLAGS) -c file.c

clean:
	rm -f $(OBJ) $(TARGET)