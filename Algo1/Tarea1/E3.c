#include <stdio.h>

const char CANDE = 'c';
const char TOMI = 't';
const char DELFI = 'd';

const char SI = 's';
const char NO = 'n';

int main()
{
    char cook;

    printf("Que rico tiramisu que hizo...\n");
    printf("Escribir c para Cande, t para Tomi o d para Delfi\n");
    scanf(" %c", &cook);
    
    if (cook == CANDE)
    {
        printf("Ñam ñam ñam delicious...\n");
    }
    else if (cook == TOMI)
    {
        printf("Te quiero mucho Tom, pero prefiero quedarme con hambre.\n");
        printf("Igual si no lo hizo hace mucho puede estar safable, hace cuantos dias lo hizo? ");
        unsigned int dias = 0;
        scanf(" %i", &dias);
        if (dias < 5)
        {
            printf("A comer!\n");
        }
        else
        {
            printf("Mejor me pido algo por Rappi\n");
        }
    }
    else if (cook == DELFI) 
    {
        printf("Gracias delfi, pero estoy a dieta.\n"); /* La guia aca repite el dialogo de tomi asi que improvise */
        printf("Bah, pero tiene Castañas de Caju? [s/n] ");
        char taju;
        scanf(" %c", &taju);
        
        if (taju == SI)
        {
            printf("mmm bueno entonces me lo como.\n");
        }
        else if (taju == NO)
        {
            printf("mejor voy y me compro algo en el kiosko\n");
        }
        
    }
    else printf("No conozco a esa persona");

    return 0;
}