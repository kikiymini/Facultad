#include "pruebas.h"
#include <stdio.h>
#include "distanciamento.h"
#include <stdbool.h>
#include <string.h>

#define BLANCO "\x1b[37;1m"
#define VERDE "\x1b[32;1m"
#define ROJO "\x1b[31;1m"
#define AMARILLO "\x1b[33;1m"
#define NORMAL "\x1b[0m"

#define TILDE "✓"
#define CRUZ "✗"

#define CANTIDAD_PRUEBAS 1

void verificar(bool ejecutada_correctamente, char* prueba);


//GIVEN_WHEN_DADO

// MATRIZ 1x3
bool DadaUnaMatrizDeUnoPorTres_CuandoSeQuiereOrdenar_NoSeAgranda(int tope_columnas)
{
    if (tope_columnas == 3)
        return true;

    return false;
}

bool DadaUnaMatrizDeUnoPorTresLlena_CuandoSeQuiereOrdenar_QuedaOrdenada(char formacion[MAX_FILAS][MAX_COLUMNAS])
{
    if( formacion[0][0] == ENEMIGO &&
        formacion[0][1] == VACIO &&
        formacion[0][2] == ENEMIGO &&
        formacion[0][3] == VACIO &&
        formacion[0][4] == ENEMIGO )
            return true;

    return false;
}

bool DadaUnaMatrizDeUnoPorTres_CuandoSeQuiereOrdenar_QuedaOrdenada(char formacion[MAX_FILAS][MAX_COLUMNAS])
{
    if( formacion[0][0] == ENEMIGO &&
        formacion[0][1] == VACIO &&
        formacion[0][2] == ENEMIGO )
            return true;

    return false;
}

bool DadaUnaMatrizDeUnoPorTresLlena_CuandoSeQuiereOrdenar_QuedaOrdenadaYAgrandada(char formacion[MAX_FILAS][MAX_COLUMNAS])
{
    if( formacion[0][0] == ENEMIGO &&
        formacion[0][1] == VACIO &&
        formacion[0][2] == ENEMIGO )
            return true;

    return false;
}

void pruebas_matriz_uno_por_tres()
{
    printf(BLANCO"Prueba matriz de una fila con tres columnas:\n");
    int tope_filas = 1;
    int tope_columnas = 3;
    char formacion[MAX_FILAS][MAX_COLUMNAS];
    formacion[0][0] = ENEMIGO;
    formacion[0][1] = ENEMIGO;
    formacion[0][2] = VACIO;

    distanciar_formacion(formacion, &tope_filas, &tope_columnas);

    verificar(DadaUnaMatrizDeUnoPorTres_CuandoSeQuiereOrdenar_NoSeAgranda(tope_columnas),
     "No se agranda la Matriz si no es necesario");

    verificar(DadaUnaMatrizDeUnoPorTres_CuandoSeQuiereOrdenar_QuedaOrdenada(formacion),
     "Se ordena la matriz correctamente");

    formacion[0][1] = ENEMIGO;
    distanciar_formacion(formacion, &tope_filas, &tope_columnas);

    verificar(DadaUnaMatrizDeUnoPorTresLlena_CuandoSeQuiereOrdenar_QuedaOrdenada(formacion),
     "Si la fila esta llena elimina un enemigo");

    verificar(DadaUnaMatrizDeUnoPorTresLlena_CuandoSeQuiereOrdenar_QuedaOrdenadaYAgrandada(formacion),
     "Si la fila esta llena se agranda sin superar el maximo posible");


    printf("\n");
    return;
}
// FIN MATRIZ 1x3

void verificar(bool ejecutada_correctamente, char* prueba)
{
    if (ejecutada_correctamente)
        printf(VERDE TILDE BLANCO" %s!\n", prueba);
    
    else
        printf(ROJO CRUZ BLANCO" %s!\n", prueba);

    printf(NORMAL);
    return;
}

void iniciar_pruebas()
{
    printf(AMARILLO"Iniciando pruebas:\n\n"NORMAL);
    pruebas_matriz_uno_por_tres();

    
    return;
}

