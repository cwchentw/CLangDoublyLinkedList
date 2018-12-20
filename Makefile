CFLAGS=-Wall -Wextra -g -std=c99

MEM_CHECK=valgrind --quiet
OBJS=test_list.o test_manipulation.o test_traversal.o \
	list.o
TEST_PROG=test_list.out

RM=del

.PHONY: all memo test compile trim clean

all: test

memo: compile
	$(MEM_CHECK) ./$(TEST_PROG)
	echo $$?

test: compile
	./$(TEST_PROG)
	echo %errorlevel%

compile: $(TEST_PROG)

$(TEST_PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $(TEST_PROG) *.o

%.o: %.c
	$(CC) $(CFLAGS) -c $<

trim:
	for %%f in (*.c *.h) do perl -lp -i.bak -e "s{\s+$$}{}g;" %%f
	del *.bak

clean:
	$(RM) $(TEST_PROG) *.o
