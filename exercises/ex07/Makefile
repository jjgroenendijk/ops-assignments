# Makefile for OPS exercise 8: filter/redirect


# Make both programs by default:
all: filter redirect


# Link and create binary executable
filter: filter.o
	${CC} -Wall -o filter filter.o

# Compile .c files to object files (.o files)
filter.o: filter.c
	${CC} -c -Wall filter.c


# Link and create binary executable
redirect: redirect.o
	${CC} -Wall -o redirect redirect.o

# Compile .c files to object files (.o files)
redirect.o: redirect.c
	${CC} -c -Wall redirect.c


clean:
	rm -f *.o

cleanall: clean
	rm -f filter redirect