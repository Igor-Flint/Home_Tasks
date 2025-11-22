CC = gcc
CFLAGS = -Wall -Wextra -std=c99
CFLAGS = -g -O2 -lm
OBJ = Task3_main.o Task3_struct.o
TARGET = Task3

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

Task3_main.o: Task3_main.c Task3_struct.h
	$(CC) $(CFLAGS) -c Task3_main.c

Task3_struct.o: Task3_struct.c Task3_struct.h
	$(CC) $(CFLAGS) -c Task3_struct.c

clean:
	rm -f $(OBJ) $(TARGET)
