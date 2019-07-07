CC = gcc
CFLAGS = -g
OBJ = main.o scanner.o parser.o tree.o stack.o
TARGET = statSem

$(TARGET): $(OBJ)
	$(CC) -o $(CFLAGS) -o $(TARGET) $(OBJ) 

clean:
	rm *.o
