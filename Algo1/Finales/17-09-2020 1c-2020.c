/* ATENCION!
 * ESTE PARCIAL FUE RESUELTO POR UN ALUMNO PERO CARECE DE CORRECCION
 * POR UN DOCENTE, EL CODIGO PUEDE CONTENER ERRORES PARACTICOS COMO CONCEPTUALES
*/

// EJERCICIO 1

// VERSION 1

/* Merry es un gran fanático de los juegos de mesa, aprovecha cada tiempito libre
 * que tiene para jugar una partida de lo que sea, con quien sea.
 * Tal es su fanatismo que lleva registro de cada partida de cada juego que jugó,
 * como le fue y contra quién jugó en un archivo de texto llamado partidas.csv, el cual
 * está ordenado ascendentemente por nombre del contrincante y luego por fecha.
 * Cada línea del archivo contiene la siguiente información: */

// fecha;nombre del contrincante;id_juego;resultado de la partida //

/* Se cuenta tambíen un archivo binario de acceso directo ordenado por id_juego, 
 * llamado juegos.dat, que cuenta con todos los nombres de los juegos que Merry puede jugar.
 * En este archivo, los id_juego son números enteros correlativos que comienzan desde el 1
 * y tiene registros del tipo juego_t: */

#define MAX_NOMBRE 50
typedef struct juego
{
    int id_juego;
    char nombre[MAX_NOMBRE];
} juego_t;

/* Listar todas las partidas jugadas por Merry, agrupadas por contrincante,
 * mostrando al finalizar cada uno, la cantidad de veces que ganó, perdió y empató,
 * como se muestra a continuacíon: */

/* 
Bilbo
Damas - Ganó.
Backgammon - Perdió.
Ajedrez - Perdió.
...
Ganó 15 veces, perdió 30, empató 10.
-------------------------------------------
Frodo
Palitos chinos - Ganó.
Batalla naval - Ganó.
Palitos chinos - Perdió.
...
Ganó 43 veces, perdió 5, empató 18.
-------------------------------------------
*/

// RESOLUCION
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_FECHA 9

// CONVENCION! los resultados de la partida se representan de la siguiente manera
#define GANO 1 
#define PERDIO -1
#define EMPATO 0

typedef struct partidas
{
    int fecha[MAX_FECHA];
    char nombre_contrincante[MAX_NOMBRE];
    int id_juego;
    int resultado;
} partidas_t;

/* Esta funcion no recive o devuelve 
 * argumentos/parametros
*/ 
void listar_partidas()
{
    FILE* partidas = fopen("partidas.csv", "r");
    if (!partidas)
    {
        printf("No se encontro el archivo de partidas!\n");
        return;
    }

    partidas_t listado_partidas;
    fscanf(partidas, "%i; %[^;], %i, %i", listado_partidas.fecha, listado_partidas.nombre_contrincante, listado_partidas.id_juego, listado_partidas.resultado);
    while(!feof(partidas))
    {
        char contrincante_actual[MAX_NOMBRE];
        strcpy(contrincante_actual, listado_partidas.nombre_contrincante);

        int veces_ganadas = 0;
        int veces_perdidas = 0;
        int veces_empatadas = 0;

        printf("%s\n", contrincante_actual);
        while(strcmp(contrincante_actual, listado_partidas.nombre_contrincante) == 0 && !feof(partidas))
        {
            char nombre_juego[MAX_NOMBRE];
            nombre_segun_id(nombre_juego, listado_partidas.id_juego);
            printf("%s - ", nombre_juego);
            evaluar_resultado(listado_partidas.resultado, &veces_ganadas, &veces_perdidas, &veces_empatadas);   

            fscanf(partidas, "%i; %[^;], %i, %i", listado_partidas.fecha, listado_partidas.nombre_contrincante, listado_partidas.id_juego, listado_partidas.resultado);
        }
        printf("Ganó: %i veces, perdió %i, empató %i.\n", veces_ganadas, veces_perdidas, veces_empatadas);
        printf("---------------------------\n");
    }

    fclose(partidas);
    return;
}

/* Recibe un string nombre_juego inicializado pero con basura en su interior
 * id_juego_listado es recibido con su previa inicializacion correcta
*/
void nombre_segun_id(char nombre_juego[MAX_NOMBRE], int id_juego_listado)
{
    FILE* juegos = fopen("juegos.dat", "r");
    if (!juegos)
    {
        printf("No se encontro el archivo de juegos!\n");
        return;
    }

    juego_t juego_actual;
    fread(&juego_actual, sizeof(juego_t), 1, juegos);
    while(!feof(juegos))
    {
        if(juego_actual.id_juego == id_juego_listado)
            strcpy(nombre_juego, juego_actual.nombre);

        fread(&juego_actual, sizeof(juego_t), 1, juegos);
    }

    fclose(juegos);
    return;
}

/* Recibe el resultado con un valor posible de GANO, PERDIO o EMPATO
 * veces_ganadas, veces_perdidas y veces_empatadas estaran previamente inicializadas
 * y con un valor igual o mayor a cero
*/
void evaluar_resultado(int resultado, int* veces_ganadas, int* veces_perdidas, int* veces_empatadas)
{
    if (resultado == GANO)
    {
        printf("Ganó.\n");
        (*veces_ganadas)++;
    }
    else if (resultado == PERDIO)
    {
        printf("Perdió.\n");
        (*veces_perdidas)++;
    }
    else // EMPATO
    {
        printf("Empató.\n");
        (*veces_empatadas)++;
    }

    return;
}

// FIN RESOLUCION



// VERSION 2

/* Merry es un gran fanático de los juegos de mesa, aprovecha cada tiempito libre
 * que tiene para jugar una partida de lo que sea, con quien sea.
 * Tal es su fanatismo que lleva registro de cada partida de cada juego que jugó,
 * como le fue y contra quién jugó en un archivo de texto llamado partidas.csv, el cual
 * está ordenado ascendentemente por nombre del contrincante y luego por fecha.
 * Cada línea del archivo contiene la siguiente información: */

// fecha;nombre del contrincante;id_juego;resultado de la partida //

/* Se cuenta tambíen un archivo binario de acceso secuencial, llamado juegos.dat,
 * que cuenta con todos los nombres de los juegos que Merry puede jugar.
 * Este archivo no está ordenado, pero se sabe que no contiene más de 100 registros del tipo juego_t: */

/* typedef struct juego
{
    int id_juego;
    char nombre[MAX_NOMBRE];
} juego_t;*/

/* Listar todas las partidas jugadas por Merry, agrupadas por contrincante,
 * y luego por fecha, mostrando al finalizar cada uno, la cantidad de veces que jugó cada
 * día, como se muestra a continuacion: */

/*
Bilbo
20200110
Damas - Ganó.
Backgammon - Perdió.
Ajedrez - Perdió.
El 20200101 jugó 10 veces.
-----------------------------
20200123
Quien es quien - Ganó.
Ajedrez - Ganó.
Truco - Perdió.
El 20200123 jugó 6 veces.
...
-------------------------------------------
Frodo
20200101
Damas - Ganó.
Backgammon - Perdió.
Ajedrez - Perdió.
El 20200101 jugó 10 veces.
-----------------------------
20200123
Quien es quien - Ganó.
Ajedrez - Ganó.
Truco - Perdió.
El 20200123 jugó 6 veces.
...
-------------------------------------------
*/

// RESOLUCION
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_FECHA 9
#define MAX_REGISTROS 100

// CONVENCION! los resultados de la partida se representan de la siguiente manera
#define GANO 1 
#define PERDIO -1
#define EMPATO 0

typedef struct partidas
{
    int fecha[MAX_FECHA];
    char nombre_contrincante[MAX_NOMBRE];
    int id_juego;
    int resultado;
} partidas_t;

/* Esta funcion no recive o devuelve 
 * argumentos/parametros
*/ 
void listar_partidas()
{
    FILE* partidas = fopen("partidas.csv", "r");
    if (!partidas)
    {
        printf("No se encontro el archivo de partidas!\n");
        return;
    }

    partidas_t listado_partidas;
    fscanf(partidas, "%i; %[^;], %i, %i", &listado_partidas.fecha, listado_partidas.nombre_contrincante, &listado_partidas.id_juego, &listado_partidas.resultado);
    while(!feof(partidas))
    {
        char contrincante_actual[MAX_NOMBRE];
        strcpy(contrincante_actual, listado_partidas.nombre_contrincante);
        printf("%s\n", contrincante_actual);
        while(strcmp(contrincante_actual, listado_partidas.nombre_contrincante) == 0 && !feof(partidas))
        {
            int fecha_actual[MAX_FECHA] = listado_partidas.fecha;
            int cantidad_partidas_fecha = 0;
            printf("%i\n", fecha_actual);
            while(fecha_actual == listado_partidas.fecha && strcmp(contrincante_actual, listado_partidas.nombre_contrincante) == 0 && !feof(partidas))
            {
                char nombre_juego[MAX_NOMBRE];
                nombre_segun_id(nombre_juego, listado_partidas.id_juego); // IR A LINEA 117 PARA VER FUNCION
                printf("%s - ", nombre_juego);
                evaluar_resultado_v2(listado_partidas.resultado);
                cantidad_partidas_fecha++;

                fscanf(partidas, "%i; %[^;], %i, %i", &listado_partidas.fecha, listado_partidas.nombre_contrincante, &listado_partidas.id_juego, &listado_partidas.resultado);
            }
            printf("el %i jugo %i veces\n", fecha_actual, cantidad_partidas_fecha);
            printf("---------------------------\n");
        }
    }

    fclose(partidas);
    return;
}

/* Recibe el resultado con un valor posible de GANO, PERDIO o EMPATO
*/
void evaluar_resultado_v2(int resultado)
{
    if (resultado == GANO)
        printf("Ganó.\n");
    else if (resultado == PERDIO)
        printf("Perdió.\n");
    else // EMPATO
        printf("Empató.\n");

    return;
}

// FIN RESOLUCION



// EJERCICIO 2

// VERSION 1

/* Faramir dejó un testamento, porque sabía que, con la personalidad que tiene, algún día no volvería a casa.
 * Tuvo la precaución de encriptarlo, para que solo los herederos puedan descifrarlo ya que incluye indicaciones para llegar una fortuna oculta.
 * Siendo un merecido heredero de la herencia de Faramir se cuenta con el archivo de texto testamento.txt
 * y se quiere desencriptar para acceder a la fortuna.
 * Se sabe que: - Las a fueron cambiadas por s. - Las s fueron cambiadas por n. - Las n fueron cambiadas por r. - Las r fueron cambiadas por a.
 * A su vez, por cada e que aparacía en el estamento, se agregó una risa socarrona jeje.*/

// Crear un programa que desencripte el testamento de Faramir.

/* Frase encriptada:
 * Ejejer ejejentejeje humildejeje scto, dejejejo min cejejertsvon dejejebsjo dejeje ls gasr T.
 * Frase desencriptada:
 * En este humilde acto, dejo mis centavos debajo de la gran T. */

#include <stdlib.h>
#include <stdbool.h>

#define MAX_CARACTER 1

const char S = 's';
const char A = 'a';
const char N = 'n';
const char R = 'r';
const char E = 'e';

void desencriptar_testamento();

int main()
{
    desencriptar_testamento();

    return 0;
}

void desencriptar_testamento()
{
    FILE* testamento = fopen("testamento.txt", "r");
    if (!testamento)
    {
        printf("Testamento no encontrado!\n");
        return;
    }

    FILE* testamento_temporal = fopen("testamento_temporal.txt", "w");
    if (!testamento_temporal)
    {
        printf("No se pudo crear el testamento temporal, memoria insuficiente!\n");
        return;
    }
 
    char caracter_actual;
    fscanf(testamento, "%c", &caracter_actual);
    while(!feof(testamento))
    {
        // Por falta de informacion en el enunciado, asumo que todo caracter es en minuscula - se puede corregir agregando ifs para lo mismo pero en mayuscula
        if (caracter_actual == S) caracter_actual = A;
        else if (caracter_actual == N) caracter_actual = S;
        else if (caracter_actual == R) caracter_actual = N;
        else if (caracter_actual == A) caracter_actual = R;
        else if (caracter_actual == E)
        {
            for (int i = 0; i < 4; i++) fscanf(testamento, "%c", &caracter_actual); // POSIBLE MALA PRACTICA - BUSCAR ALTERNATIVA
        }
    
        fwrite(&caracter_actual, sizeof(char), 1, testamento_temporal);
        fscanf(testamento, "%c", &caracter_actual);
    }

    fclose(testamento);
    fclose(testamento_temporal);
    rename("testamento_temporal.txt", "testamento.txt");

    return;
}

// FIN RESOLUCION
