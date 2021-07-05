VALGRIND_FLAGS=--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2
CC = gcc
CFLAGS =-g -O0 -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror  -I cabeceras

pruebas: interfaz.c pruebas.c
	$(CC) $(CFLAGS) interfaz.c pruebas.c -o pruebas 2>&1

valgrind: pruebas
	valgrind $(VALGRIND_FLAGS) ./pruebas 2>&1
