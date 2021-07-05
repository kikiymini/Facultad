#include "distanciamento.h"
#include <stdio.h>

// funcion re piola y re recursiva    
char mover(char array[][MAX_COLUMNAS], int posicion, int tope, int fila)
{
    // Condicion de corte
    // Ejecutar la funcion hasta llegar al tope o un espacio vacio
    if (posicion == (tope -1) || array[fila][posicion] == VACIO)
    {
        array[fila][posicion] = ENEMIGO;
        return VACIO;
    }

    // Si al lado tiene # 
    else return mover(array, posicion +1, tope, fila);
}


int distanciar_formacion(char formacion[MAX_FILAS][MAX_COLUMNAS], int* tope_filas, int* tope_columnas) 
{   
    if (!formacion)
        return -1;

    // Fila con maxima cantidad de enemigos 
    int max_enemigos = 0;
    for (int i = 0; i < *tope_filas; i++)
    {
        int enemigos_fila = 0;
        for (int j = 0; j < *tope_columnas; j++)
            if (formacion[i][j] == ENEMIGO) enemigos_fila++;

        if (enemigos_fila > max_enemigos) max_enemigos = enemigos_fila;
    }
    
    // Veo el espacio minimo necesario entre ellos y si es posible agrandarlo
    int espacio_necesario = (max_enemigos * 2) -1;
    int viejo_tope = *tope_columnas;
    if (espacio_necesario > *tope_columnas)
    {
        if (espacio_necesario < MAX_COLUMNAS) *tope_columnas = espacio_necesario;
        else *tope_columnas = MAX_COLUMNAS;
    } 
   
    // Agrando matriz
    for (int i = 0; i < *tope_filas; i++)
        for (int j = viejo_tope; j < *tope_columnas; j++)
            formacion[i][j] = VACIO;           

    // Reordeno dejando espacios
    for (int i = 0; i < *tope_filas; i++)
        for (int j = 0; j < *tope_columnas -1; j++)
            if (formacion[i][j] == ENEMIGO)
                if (formacion[i][j+1] == ENEMIGO)
                    formacion[i][j+1] = mover(formacion, j +1, *tope_columnas, i);

    return 0;
}
