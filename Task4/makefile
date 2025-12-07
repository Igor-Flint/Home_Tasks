CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -O0
OBJ = echo.o cat.o cmp.o cp.o pwd.o

all: $(OBJ)

echo.o: echo.c
	$(CC) $(CFLAGS) -c echo.c

cat.o: cat.c
	$(CC) $(CFLAGS) -c cat.c

cmp.o: cmp.c
	$(CC) $(CFLAGS) -c cmp.c

cp.o: cp.c
	$(CC) $(CFLAGS) -c cp.c

pwd.o: pwd.c
	$(CC) $(CFLAGS) -c pwd.c

clean:
	rm -f $(OBJ)
