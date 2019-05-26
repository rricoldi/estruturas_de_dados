
CC = gcc
COMPILER_FLAGS = -std=c99
LINKER_FLAGS = -lm
OBJ_NAME = siguel


siguel: main.o leitura.o
	$(CC) main.o leitura.o qry.o svg.o lista.o $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

main.o: main.c leitura.o leitura.h qry.o qry.h svg.o svg.h lista.o lista.h 
	$(CC) -c main.c

leitura.o: leitura.c leitura.h svg.o svg.h lista.o lista.h 
	$(CC) -c leitura.c

qry.o: qry.c qry.h svg.o svg.h leitura.o leitura.h lista.o lista.h 
	$(CC) -c qry.c

svg.o: svg.c svg.h lista.o lista.h 
	$(CC) -c svg.c

lista.o: lista.c lista.h qry.o qry.h svg.o svg.h leitura.o leitura.h
	$(CC) -c lista.c