#include <stdio.h>

const int cuadra = 100;

int main()
{
    int altura_berni = 0;
    int altura_mia = 0;

    /* Preguntarle a Berni donde vive */
    printf("Che berni, a que altura era tu casa?\n");
    scanf("%i", &altura_berni);

    /* Fijarme en que altura estoy yo */
    printf("Y yo estoy en calle falsa al ");
    scanf("%i", &altura_mia);

    /* Calcular a cuantas cuadras estoy de lo de Berni */
    int cuadras = (altura_berni - altura_mia) / 100;
    printf("Estoy a %i cuadras de lo de Berni", cuadras);

    return 0;
}