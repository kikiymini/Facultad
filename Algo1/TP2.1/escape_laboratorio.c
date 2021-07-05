#include "escape_laboratorio.h"
#include "utiles.h"
#include <stdlib.h> // Para usar rand
#include <time.h> // Para obtener una semilla desde el reloj
#define MAX_DIMENSIONES 17

// Constante de Personajes
const char JOHNNY = 'J';
const char BELLOTA = 'S';
const char POLLITO = 'P'; 
const char BLUE = 'B'; 
const char PURO_HUESO = 'H';
const char CORAJE = 'C';

// Constante de caracteristicas de personajes
const char DOBLE = 'D';
const char RESISTENTE = 'R';
const char ATRACTIVO = 'A'; 

// Constantes objetos interactivos
const char BALDOSA_PINCHE = 'P';
const char MONEDA = 'M';
const char LLAVE = 'L';
const char BOMBA = 'B';
const char INTERRUPTOR = 'I';
const char ENTRADA = 'E';
const char SALIDA = 'S';
const char BALDOSA_TELETRANSPORTADORA = 'T';
const char GUARDIA = 'G';

// Constantes dibujo de mapa
const char PAREDES = '#';
const char VACIO = ' ';

// Constantes movimiento
const char ARRIBA = 'w'; 
const char ABAJO = 's'; 
const char DERECHA = 'd'; 
const char IZQUIERDA = 'a'; 

/*
 *
 * 
*/
void cambiar_posicion_guardias(juego_t* juego,char mapa[][MAX_DIMENSIONES])
{
    // TODO
}

/*
 *
 * 
*/
void obtener_posicion_vacia(char mapa[][MAX_DIMENSIONES], int* fila, int* columna, int dimension)
{
    do
    {
        *fila = rand() % (dimension-2) + 1;
        *columna = rand() % (dimension-2) + 1;
    } while (mapa[*fila][*columna] != VACIO);
}

/*
 *
 * 
 * 
*/ 
int obtener_dimension(juego_t juego)
{
    int dimension = 12;
    if ((juego.nivel_actual +1)% 2 == 0)
        dimension = 17;

    return dimension;
}

/*
 *
 * 
*/ 
void evaluar_interacciones(juego_t* juego, char mapa[][MAX_DIMENSIONES])
{
    personaje_t personaje = juego->personaje;

    char objeto = mapa[personaje.posicion.fil][personaje.posicion.col];

    if (objeto == BALDOSA_PINCHE)
    {
        juego->personaje.movimientos = personaje.movimientos -2;
        if (juego->personaje.movimientos < 0) juego->personaje.movimientos = 0;
    }

    else if (objeto == MONEDA)
        juego->personaje.movimientos++;

    else if (objeto == LLAVE)
        juego->personaje.tiene_llave = true;

    else if (objeto == BOMBA)
        juego->personaje.movimientos = 0;

    else if (objeto == INTERRUPTOR)
        personaje.presiono_interruptor = true;

    else if (objeto == SALIDA)
    {
        if (juego->nivel_actual < MAX_NIVELES)
        {
            juego->personaje.movimientos = personaje.movimientos +10;
            juego->personaje.posicion.fil = juego->niveles[juego->nivel_actual+1].entrada.fil;
            juego->personaje.posicion.col = juego->niveles[juego->nivel_actual+1].entrada.col;
            juego->nivel_actual = juego->nivel_actual +1;
        }
    }

    else if (objeto == BALDOSA_TELETRANSPORTADORA)
    {
        int nueva_fila;
        int nueva_columna;
        obtener_posicion_vacia(mapa, &nueva_fila, &nueva_columna, obtener_dimension(*juego));
        juego->personaje.posicion.fil = nueva_fila;
        juego->personaje.posicion.col = nueva_columna;
    }
    
    else if (objeto == GUARDIA)
        juego->personaje.movimientos = 0;
}

/*
 *
 * 
 * 
*/ 
bool no_hay_pared_proxima(juego_t juego,char mapa[][MAX_DIMENSIONES],char direccion, int dimension)
{
    if (direccion == ARRIBA)
        if (mapa[juego.personaje.posicion.fil -1][juego.personaje.posicion.col] != PAREDES && juego.personaje.posicion.fil > 1)
            return true;

    if (direccion == ABAJO)
        if (mapa[juego.personaje.posicion.fil +1][juego.personaje.posicion.col] != PAREDES && juego.personaje.posicion.fil < dimension -1)
            return true;

    if (direccion == IZQUIERDA)
        if (mapa[juego.personaje.posicion.fil][juego.personaje.posicion.col -1] != PAREDES && juego.personaje.posicion.col > 1)
            return true;

    if (direccion == DERECHA)
        if (mapa[juego.personaje.posicion.fil][juego.personaje.posicion.col +1] != PAREDES && juego.personaje.posicion.col < dimension -1)
            return true;
    
    return false;
}

/*
 *
 * 
 * 
*/ 
void avanzar(juego_t* juego, char direccion, char mapa[][MAX_DIMENSIONES], int dimension)
{
    if (juego->personaje.movimientos > 0)
    {
        if (direccion == ARRIBA)
            juego->personaje.posicion.fil--;

        if (direccion == ABAJO)
            juego->personaje.posicion.fil++;

        if (direccion == IZQUIERDA)
            juego->personaje.posicion.col--;

        if (direccion == DERECHA)
            juego->personaje.posicion.col++;
    }
}

/*
 *
 * 
 * 
*/
void llenar_mapa(char mapa[][MAX_DIMENSIONES], int dimension, nivel_t nivel, personaje_t personaje)
{
    // Mapa Vacio
    for (int i = 0; i < dimension; i++)
        for (int j = 0; j < dimension; j++)
            mapa[i][j] = VACIO;

    // Poner paredes
    for (int i = 0; i < nivel.tope_paredes; i++)
        mapa[nivel.paredes[i].fil][nivel.paredes[i].col] = PAREDES;

    // Entrada
    mapa[nivel.entrada.fil][nivel.entrada.col] = ENTRADA; 

    // Salida
    mapa[nivel.salida.fil][nivel.salida.col] = SALIDA; 

    // Obstaculos
    for (int i = 0; i < nivel.tope_obstaculos; i++)
        mapa[nivel.obstaculos[i].posicion.fil][nivel.obstaculos[i].posicion.col] = nivel.obstaculos[i].tipo; 

    // Herramientas
    for (int i = 0; i < nivel.tope_herramientas; i++)
        mapa[nivel.herramientas[i].posicion.fil][nivel.herramientas[i].posicion.col] = nivel.herramientas[i].tipo; 

    // Posicion personaje
    mapa[personaje.posicion.fil][personaje.posicion.col] = 'J';     

}

/*
 *
 * 
*/
bool no_tiene_objeto_continuo(char mapa[][MAX_DIMENSIONES], int fila, int columna, char objeto)
{
    if (mapa[fila +1][columna] == objeto)
        return false;
    else if (mapa[fila -1][columna] == objeto)
        return false;
    else if (mapa[fila][columna +1] == objeto)
        return false;
    else if (mapa[fila][columna -1] == objeto)
        return false;

    return true;
}

/*
 *
 * 
*/
void agregar_al_nivel(nivel_t* nivel, char mapa[][MAX_DIMENSIONES], char tipo, int fila, int columna, int orden)
{
    mapa[fila][columna] = tipo;

    if (tipo == ENTRADA)
    {
        nivel->entrada.fil = fila;
        nivel->entrada.col = columna;
    }

    else if (tipo == SALIDA)
    {
        nivel->salida.fil = fila;
        nivel->salida.col = columna;
    }

    else if (tipo == BALDOSA_PINCHE || tipo == GUARDIA || tipo == BOMBA)
    {
        nivel->obstaculos[orden].tipo = tipo;
        nivel->obstaculos[orden].posicion.fil = fila;
        nivel->obstaculos[orden].posicion.col = columna;        
    }

    else if (tipo == MONEDA || tipo == BALDOSA_TELETRANSPORTADORA || tipo == INTERRUPTOR || tipo == LLAVE)
    {
        nivel->herramientas[orden].tipo = tipo;
        nivel->herramientas[orden].posicion.fil = fila;
        nivel->herramientas[orden].posicion.col = columna;        
    }
}

void inicializar_juego(juego_t* juego, char tipo_personaje)
{
    // CARGAR DATOS PERSONAJE
    // Tipo personaje 1
    if (tipo_personaje == BLUE || tipo_personaje == BELLOTA)
    {
        juego->personaje.tipo = DOBLE;
    }

    // Tipo personaje 2
    else if (tipo_personaje == PURO_HUESO || tipo_personaje == POLLITO)
    {
        juego->personaje.tipo = RESISTENTE;
    }

    // Tipo personaje 3 
    else // Bravo y Coraje
    {
        juego->personaje.tipo = ATRACTIVO;
    }

    juego->personaje.movimientos = 10;
    // CARGAS DATOS NIVELES
    for (int i = 0; i < MAX_NIVELES; i++)
    {
        int cantidad_baldosas_pinches = 0;
        int cantidad_guardia = 0;
        bool hay_bomba = false;
        if (i == 0)
        {
            cantidad_baldosas_pinches = 4;
            cantidad_guardia = 2;
            hay_bomba = false;
        }
        else if (i == 1)
        {
            cantidad_baldosas_pinches = 6;
            cantidad_guardia = 3;
            hay_bomba = false;
        }
        else if (i == 2)
        {
            cantidad_baldosas_pinches = 6;
            cantidad_guardia = 3;
            hay_bomba = true;
        }
        else // i == 3
        {
            cantidad_baldosas_pinches = 10;
            cantidad_guardia = 4;
            hay_bomba = true;
        }
        inicializar_nivel(&juego->niveles[i], i+1, cantidad_baldosas_pinches, cantidad_guardia, hay_bomba);
    }         

}

int estado_juego(juego_t juego)
{
    personaje_t personaje = juego.personaje;
    nivel_t nivel = juego.niveles[juego.nivel_actual];

    if ((juego.nivel_actual == (MAX_NIVELES -1)) && (personaje.posicion.fil == nivel.salida.fil) && (personaje.posicion.col == nivel.salida.col))
        return 1;
    else if (juego.personaje.movimientos == 0)
        return -1;
    return 0;
}

int estado_nivel(personaje_t personaje, coordenada_t salida)
{
    if (personaje.tiene_llave && personaje.posicion.fil == salida.fil && personaje.posicion.col == salida.col)
        return 1;
    return 0;
}

void inicializar_nivel(nivel_t* nivel, int numero_nivel, int cantidad_baldosas_pinches, int cantidad_guardia, bool hay_bomba)
{
    int fila = 0;
    int columna = 0;

    int dimension = 12;
    if ((numero_nivel % 2) == 0)
        dimension = 17;

    char mapa_ocupado[MAX_DIMENSIONES][MAX_DIMENSIONES];
    // Vaciar mapa por defecto
    for (int i = 0; i < dimension; i++)
        for (int j = 0; j < dimension; j++)
            mapa_ocupado[i][j] = VACIO;

    // Paredes
    nivel->tope_paredes = 0;
    obtener_paredes(numero_nivel, nivel->paredes, &nivel->tope_paredes);
    for (int i = 0; i < nivel->tope_paredes; i++)
        mapa_ocupado[nivel->paredes[i].fil][nivel->paredes[i].col] = PAREDES;

    // Entrada - posicion aleatoria -
    obtener_posicion_vacia(mapa_ocupado, &fila, &columna, dimension);    
    agregar_al_nivel(nivel, mapa_ocupado, ENTRADA, fila, columna, 0);

    // Salida - posicion aleatoria -
    obtener_posicion_vacia(mapa_ocupado, &fila, &columna, dimension);    
    agregar_al_nivel(nivel, mapa_ocupado, SALIDA, fila, columna, 0);

    // OBSTACULOS
    int cantidad_bomba = 0;
    if (hay_bomba) cantidad_bomba++;
    nivel->tope_obstaculos = cantidad_baldosas_pinches + cantidad_guardia + cantidad_bomba;

    int obstaculos_puestos = 0;
    while (obstaculos_puestos < nivel->tope_obstaculos)
    {
        obtener_posicion_vacia(mapa_ocupado, &fila, &columna, dimension);    

        // Baldosas pinche - posicion aleatoria y continuo - //CORREGIR
        if (obstaculos_puestos < cantidad_baldosas_pinches)
        {
            if (obstaculos_puestos == 0)
                agregar_al_nivel(nivel, mapa_ocupado, BALDOSA_PINCHE, fila, columna, obstaculos_puestos);      
            else
            {
                do
                {
                    obtener_posicion_vacia(mapa_ocupado, &fila, &columna, dimension);               
                } 
                while (no_tiene_objeto_continuo(mapa_ocupado, fila, columna, BALDOSA_PINCHE));
                agregar_al_nivel(nivel, mapa_ocupado, BALDOSA_PINCHE, fila, columna, obstaculos_puestos);      
            }              
        }

        // Guardias - posicion aleatoria -
        else if(obstaculos_puestos < cantidad_baldosas_pinches + cantidad_guardia)
        {
            agregar_al_nivel(nivel, mapa_ocupado, GUARDIA, fila, columna, obstaculos_puestos);                
        }

        // Bomba - posicion aleatoria -
        else
        {
            agregar_al_nivel(nivel, mapa_ocupado, BOMBA, fila, columna, obstaculos_puestos);                
        }
        obstaculos_puestos++;    
    }

    // HERRAMIENTAS
    int cantidad_monedas = cantidad_baldosas_pinches / 2;
    int cantidad_baldosa_teletransportadora = cantidad_guardia;
    int cantidad_interruptores = cantidad_bomba;
    nivel->tope_herramientas = cantidad_monedas + cantidad_baldosa_teletransportadora + cantidad_interruptores + 1;
    
    int herramientas_puestas = 0;
    while (herramientas_puestas < nivel->tope_herramientas)
    {
        obtener_posicion_vacia(mapa_ocupado, &fila, &columna, dimension);    
        
        // Llave
        if (herramientas_puestas == 0)
            agregar_al_nivel(nivel, mapa_ocupado, LLAVE, fila, columna, herramientas_puestas);  

        // Monedas - posicion aleatoria -
        else if (herramientas_puestas < 1 + cantidad_monedas)
            agregar_al_nivel(nivel, mapa_ocupado, MONEDA, fila, columna, herramientas_puestas);                
        
        // Baldosa teletransportadora - posicion aleatoria -
        else if(herramientas_puestas < 1 + cantidad_monedas + cantidad_baldosa_teletransportadora)
            agregar_al_nivel(nivel, mapa_ocupado, BALDOSA_TELETRANSPORTADORA, fila, columna, herramientas_puestas);                

        // Interruptor - posicion aleatoria -
        else
            agregar_al_nivel(nivel, mapa_ocupado, INTERRUPTOR, fila, columna, herramientas_puestas); 

        herramientas_puestas++;
    }

}

void mover_personaje(juego_t* juego, char movimiento)
{   
    int dimension = obtener_dimension(*juego);

    char mapa[MAX_DIMENSIONES][MAX_DIMENSIONES];
    llenar_mapa(mapa, dimension, juego->niveles[juego->nivel_actual], juego->personaje);

    juego->personaje.movimientos = juego->personaje.movimientos -1; 

    int progreso_nivel = 0;
    while(no_hay_pared_proxima(*juego, mapa, movimiento, dimension) && progreso_nivel == 0)
    {
        detener_el_tiempo((float) 0.064);
        avanzar(juego, movimiento, mapa, dimension);
        progreso_nivel = estado_nivel(juego->personaje, juego->niveles[juego->nivel_actual].salida);
        evaluar_interacciones(juego, mapa);
        mostrar_juego(*juego);
        cambiar_posicion_guardias(juego, mapa);
    }
}

void mostrar_juego(juego_t juego)
{
    system("clear");

    int nivel_actual = juego.nivel_actual;
    nivel_t nivel = juego.niveles[nivel_actual];

    int dimension = obtener_dimension(juego);
    
    char mapa[MAX_DIMENSIONES][MAX_DIMENSIONES];

    llenar_mapa(mapa, dimension, juego.niveles[juego.nivel_actual], juego.personaje);
  
    printf("Nivel: %i        movimientos: %i\n", nivel_actual +1, juego.personaje.movimientos); // imprimir espacios segun longitud de texto 
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            printf(" %c", mapa[i][j]);
        }
        printf("\n"); 
    } 
}