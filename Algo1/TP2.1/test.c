#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // Para usar rand
#include <time.h> // Para obtener una semilla desde el reloj
#define MAX_DIMENSIONES 17
const char VACIO = ' ';
const char OCUPADO = '#';

void esta_vacio(char mapa[][MAX_DIMENSIONES], int* fila, int* columna)
{
    do
    {
        *fila = rand() % 12;
        *columna = rand() % 12;
    } while (mapa[*fila][*columna] != VACIO);
}

int main()
{
    // Semilla para obtener numeros aleatorios
    srand (( unsigned)time(NULL));

    char mapa[MAX_DIMENSIONES][MAX_DIMENSIONES];

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 5; j++)
            mapa[i][j] = OCUPADO;
    
    mapa[4][4] = VACIO;

    printf("antes:\n");
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 5; j++)
            printf(" %c", mapa[i][j]);
        printf("\n");
    }

    int fila;
    int columna;
    esta_vacio(mapa, &fila, &columna);

    mapa[fila][columna] = 's';

    printf("despues:\n");
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 5; j++)
            printf(" %c", mapa[i][j]);
        printf("\n");
    }

}