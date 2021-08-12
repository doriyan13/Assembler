Assembler: assembler.o commandsHandler.o binaryHandler.o utilities.o
	gcc -o Assembler assembler.o commandsHandler.o binaryHandler.o utilities.o
assembler.o: assembler.c commandsHandler.h binaryHandler.h utilities.h
	gcc -ansi -Wall -pedantic -c assembler.c
commandsHandler.o: commandsHandler.c commandsHandler.h binaryHandler.h utilities.h
	gcc -ansi -Wall -pedantic -c commandsHandler.c
binaryHandler.o: binaryHandler.c commandsHandler.h binaryHandler.h
	gcc -ansi -Wall -pedantic -c binaryHandler.c
utilities.o: utilities.c utilities.h commandsHandler.h
	gcc -ansi -Wall -pedantic -c utilities.c
