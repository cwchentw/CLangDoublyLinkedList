CFLAGS=-Wall -Wextra -g -std=c99

MEM_CHECK=valgrind --quiet
OBJS=test_list.o test_manipulation.o test_traversal.o \
	list.o
TEST_PROG=test_list.out

.PHONY: all memo test compile trim clean

all: test

memo: compile
	$(MEM_CHECK) ./$(TEST_PROG)
	echo $$?

test: compile
	./$(TEST_PROG)
	echo $$?

compile: $(TEST_PROG)

$(TEST_PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $(TEST_PROG) *.o

%.o: %.c
	$(CC) $(CFLAGS) -c $<

trim:
	perl -lpi -e "s{\s+$$}{}g;" *

clean:
	$(RM) $(TEST_PROG) *.o
