#include <stdio.h>

const char WHILE = 'w';
const char DO = 'd';
const char FOR  = 'f';



int main()
{
    /* metodo a usar */
    char method;
    printf("elegir iteracion deseada:\nw para while \nd para do-while \nf para for\n");
    scanf(" %c", &method);

    /* molestar al kioskero */
    int costo = 0;
    do
    {
        printf("Cuanto es?\n$");
        scanf(" %i", &costo);
        if (costo <= 10) printf("Solo eso? jijiji ");
    } while (costo <= 10);

    int pago = 1;
    /* metodo while */
    if (method == WHILE)
    {
        while(pago <= costo)
        {
            /* dar monedas */
            if (pago % 2 != 0)
            {
                printf("Sírvase %i\n", pago);
            }
            else
            {
                printf("Aquí tiene %i\n", pago);
            }
            pago++;
        }
    }
    /* metodo do */
    else if (method == DO)
    {
        do
        {
            /* dar monedas */
            if (pago % 2 != 0)
            {
                printf("Sírvase %i\n", pago);
            }
            else
            {
                printf("Aquí tiene %i\n", pago);
            }
            pago++;
        } while (pago <= costo);        
    }
    /* metodo for */
    else if (method == FOR)
    {
        for (;pago <= costo; pago++)
        {
            /* dar monedas */
            if (pago % 2 != 0)
            {
                printf("Sírvase %i\n", pago);
            }
            else
            {
                printf("Aquí tiene %i\n", pago);
            }
        }
    }        
    return 0;
}

