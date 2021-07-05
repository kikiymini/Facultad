#include <stdio.h>
#include <stdlib.h>

#define PRECISION 0.0001

long double absoluto(long double numero)
{
    if (numero < 0)
        return numero*(-1);

    return numero;
}

long double mejor_estimacion(long double numero, long double estimacion)
{
    return ((estimacion + numero/estimacion)/2);
}

long double root(long double numero, long double estimacion)
{
    if (absoluto(estimacion*estimacion - numero) < PRECISION)
        return estimacion; 

    return root(numero, mejor_estimacion(numero, estimacion));
}

int main()
{
    long double numero = 9;
    //long double aprox_inicial = numero/2;
    long double raiz = root(numero, numero/2);
    printf("%Lf\n", raiz);

    return 0;
}

