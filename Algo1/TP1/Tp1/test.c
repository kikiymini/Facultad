#include <stdio.h>
#define MAX_COLUMNAS 5

char mover(char array[], int posicion, int tope)
{
    // Condicion de corte
    // Ejecutar la funcion hasta llegar al tope o un espacio vacio
    if (posicion == tope -1 || array[posicion] == '-')
    {
        return '-';
    }

    // Si al lado tiene # 
    else return mover(array, posicion +1, tope);
}

int main()
{
    int tope_columnas = 9;
    char fila[tope_columnas];

    for (int i = 0; i < tope_columnas; i++)
    {
        if (i == 6 || i == 7 || i == 2) fila[i] = '-';
        else fila[i] = '#';
    }

    for (int i = 0; i < tope_columnas; i++)
    {
        if (fila[i] == '#' && fila[i] == fila[i+1]) 
        {
            fila[i+1] = mover(fila, i+1, tope_columnas);
        }
    }

    for (int i = 0; i < tope_columnas; i++)
    {
        printf("%c", fila[i]);
    }
    printf("\n");

    return 0;
}