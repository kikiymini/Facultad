#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // Para usar rand
#include <time.h> // Para obtener una semilla desde el reloj

// Bibleotecas
#include "escape_laboratorio.h"
// #include "detector_personaje.h"

void renderizar_nivel(int nivel, coordenada_t paredes_laboratorio[MAX_PAREDES], int tope);

int main()
{
    // Preguntar al usuario el personaje que desea usar
    char personaje_seleccionado = 'A';

    // Inicializar juego cargando niveles
    juego_t juego;

    inicializar_juego(&juego, personaje_seleccionado);

    // Imprimir niveles
    renderizar_nivel(3, juego.niveles[3].paredes, juego.niveles[3].tope_paredes);

    return 0;
}

void renderizar_nivel(int nivel, coordenada_t paredes_laboratorio[MAX_PAREDES], int tope)
{
    int dimension = 12; 
    if (nivel % 2 == 0) dimension = 17;

    char mapa[dimension][dimension];

    // Sacar basura
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            mapa[i][j] = ' ';
        }
    }

    // Rellenar donde existan paredes
    for (int i = 0; i < tope; i++)
        mapa[paredes_laboratorio[i].fil][paredes_laboratorio[i].col] = '#';

    // Imprimir
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            printf(" %c", mapa[i][j]);
        }
        printf("\n");
    }
}
