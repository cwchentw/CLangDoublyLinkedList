CC=gcc
MEM_CHECK=valgrind
RM=rm
RMFLAG=-rf
TARGET=test_list

all: run

check: compile
	$(MEM_CHECK) ./$(TARGET)
	echo $$?

run: compile
	./$(TARGET)
	echo $$?

compile:
	$(CC) -Wall -g -o $(TARGET) test_list.c test_manipulation.c test_traversal.c list.c -std=c11

clean:
	$(RM) $(RMFLAG) $(TARGET)