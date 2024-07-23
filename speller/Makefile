CC = clang
CFLAGS = -ggdb3 -gdwarf-4 -O0 -Qunused-arguments -std=c11 -Wall -Werror -Wextra -Wno-gnu-folding-constant -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow
LIBS = -lm

# Target: speller
speller: speller.o dictionary.o
	$(CC) $(CFLAGS) -o speller speller.o dictionary.o $(LIBS)

# Compile speller.o
speller.o: speller.c dictionary.h
	$(CC) $(CFLAGS) -c speller.c

# Compile dictionary.o
dictionary.o: dictionary.c dictionary.h
	$(CC) $(CFLAGS) -c dictionary.c

# Clean
clean:
	rm -f *.o speller
