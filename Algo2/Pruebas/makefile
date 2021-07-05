CFLAGS=-g -O0 -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror
VFLAGS=--leak-check=full --track-origins=yes --show-reachable=yes

compilar:
	gcc $(CFLAGS) -o pruebas main.c pruebas.c distanciamento.c

test: compilar
	./pruebas

valgrind: compilar
	valgrind $(VFLAGS) ./pruebas

