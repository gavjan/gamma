CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2
LDFLAGS	=

.PHONY: all clean

all: gamma

gamma: gamma_test.o gamma.o safe_malloc.o ufind.o
	$(CC) $(LDFLAGS) -o $@ $^
gamma.o: src/gamma.c src/gamma.h src/ufind.h src/safe_malloc.h
	$(CC) $(CFLAGS) -c $<
safe_malloc.o: src/safe_malloc.c src/safe_malloc.h
	$(CC) $(CFLAGS) -c $<
ufind.o: src/ufind.c src/ufind.h
	$(CC) $(CFLAGS) -c $< 
gamma_test.o: src/gamma_test.c src/gamma.h src/ufind.h src/safe_malloc.h
	$(CC) $(CFLAGS) -c $<

run: gamma
	./$<

valgrind: gamma
	valgrind --error-exitcode=15 --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all ./$<

# For testing with binary file 'gamma' and tests folder 'tests'.
test: gamma test.sh
	./test.sh $< tests

clean:
	-@$(RM) gamma *.out *.err *.o vgcore.*
