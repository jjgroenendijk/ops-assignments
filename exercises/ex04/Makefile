# Makefile for OPS exercise 2
# Use tabs for indentation, not spaces!

all: printversion parent

# Link object files and create a binary executable:
parent: parent.o displayFunctions.o syntaxCheck.o
	${CC} -Wall -o parent parent.o displayFunctions.o syntaxCheck.o

# Compile C-files and create object files (.o).
# The option -c ensures no linking takes place:
parent.o: parent.c displayFunctions.h errorCodes.h
	${CC} -c -Wall parent.c

displayFunctions.o: displayFunctions.c displayFunctions.h syntaxCheck.h errorCodes.h
	${CC} -c -Wall displayFunctions.c

syntaxCheck.o: syntaxCheck.c syntaxCheck.h errorCodes.h
	${CC} -c -Wall syntaxCheck.c

clean:
	rm -f *.o

cleanall: clean
	rm -f parent

printversion:
	${CC} --version | grep ${CC}
