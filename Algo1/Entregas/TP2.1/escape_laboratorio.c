#include "escape_laboratorio.h"
#include "detector_personajes.h"

#include "utiles.h"
#include <stdlib.h> // Para usar rand
#include <time.h> // Para obtener una semilla desde el reloj
#include <string.h>
#define MAX_DIMENSIONES 17

// Constante de caracteristicas de personajes
const char DOBLE = 'D';
const char RESISTENTE = 'R';
const char ATRACTIVO = 'A'; 

// Constantes objetos interactivos
const char OBSTACULO = 'O';
const char HERRAMIENTA = 'H';
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
const char JUGADOR = 'J';

// Constantes movimiento
const char ARRIBA = 'w'; 
const char ABAJO = 's'; 
const char DERECHA = 'd'; 
const char IZQUIERDA = 'a'; 

// Constantes de dicultad
const char FACIL = 'f';
const char MEDIO = 'm';
const char DIFICIL = 'd';

// Para imprimir con color
#define NORMAL "\e[0m"
#define COLOR_ROJO "\e[31m" 
#define COLOR_ROJO_CLARO "\e[91m" 
#define COLOR_AMARILLO "\e[33m" 
#define COLOR_VERDE "\e[32m"
#define COLOR_MAGENTA "\e[95m"
#define COLOR_AZUL "\e[94m"
#define COLOR_NEGRO "\e[30m"
#define COLOR_CYAN "\e[36m"
#define COLOR_BLANCO "\e[97m"
#define FONDO_BLANCO "\e[100m"
#define FONDO_VERDE "\e[42m"

#define MARGEN_IZQUIEDO 28
#define MAX_TEXTO 50

/*
 *
 * 
*/ 
void eliminar_objeto(nivel_t* nivel, int fila, int columna)
{
    for (int i = 0; i < nivel->tope_herramientas; i++)
        if (nivel->herramientas[i].posicion.fil == fila && nivel->herramientas[i].posicion.col == columna)
            nivel->herramientas[i] = nivel->herramientas[nivel->tope_herramientas -1];

    nivel->tope_herramientas--;
}

/*
 *
 * 
*/
char obtener_objeto(nivel_t nivel, int fila, int columna)
{
    char objeto = VACIO;

    if (nivel.salida.fil == fila && nivel.salida.col == columna)
        objeto = SALIDA;
    
    for (int i = 0; i < nivel.tope_obstaculos; i++)
        if (nivel.obstaculos[i].posicion.fil == fila && nivel.obstaculos[i].posicion.col == columna)
            objeto = nivel.obstaculos[i].tipo;

    for (int i = 0; i < nivel.tope_herramientas; i++)
        if (nivel.herramientas[i].posicion.fil == fila && nivel.herramientas[i].posicion.col == columna)
            objeto = nivel.herramientas[i].tipo;
    
    return objeto;
}

/* Recibe los datos de un nivel con sus obstaculos, herramientas, entrada o salida
 * posicion_jugador sera -1 para ambos valores (fil, col) si el mismo no ha sido asignado
 * Devuelve false si uno de los elementos del mapa ya ocupa las
 * coordenadas a ser analizada, devuelve true si ninguno de los elementos
 * ocupan dicho espacio
*/ 
bool espacio_vacio(nivel_t nivel, int fila, int columna, bool entrada_asignada, bool salida_asignada, coordenada_t posicion_jugador)
{
    bool esta_vacio = true;

    // PAREDES
    for (int i = 0; i < nivel.tope_paredes; i++)
        if (nivel.paredes[i].fil == fila && nivel.paredes[i].col == columna)
            esta_vacio = false;

    // ENTRADA
    else if (nivel.entrada.fil == fila && nivel.entrada.col == columna && entrada_asignada)
        esta_vacio = false;
    
    // SALIDA
    else if (nivel.salida.fil == fila && nivel.salida.col == columna && salida_asignada)
        esta_vacio = false;

    // JUGADOR
    else if (posicion_jugador.fil == fila && posicion_jugador.col == columna)
        esta_vacio = false;

    // OBSTACULOS
    for (int i = 0; i < nivel.tope_obstaculos; i++)
        if (nivel.obstaculos[i].posicion.fil == fila && nivel.obstaculos[i].posicion.col == columna)
            esta_vacio = false;

    // HERRAMIENTAS
    for (int i = 0; i < nivel.tope_herramientas; i++)
        if (nivel.herramientas[i].posicion.fil == fila && nivel.herramientas[i].posicion.col == columna)
            esta_vacio = false;
    
    return esta_vacio;
}

/*
 *
 * 
*/
void obtener_posicion_vacia(nivel_t nivel, int* fila, int* columna, int dimension, bool entrada_asignada, bool salida_asignada, coordenada_t posicion_jugador)
{
    do
    {
        *fila = rand() % (dimension-2) + 1;
        *columna = rand() % (dimension-2) + 1;
    } while (!espacio_vacio(nivel, *fila, *columna, entrada_asignada, salida_asignada, posicion_jugador));
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
void cambiar_posicion_guardias(nivel_t* nivel, int dimension, coordenada_t posicion_jugador)
{
    for (int i = 0; i < nivel->tope_obstaculos; i++)
        if (nivel->obstaculos[i].tipo == GUARDIA)
            obtener_posicion_vacia(*nivel, &nivel->obstaculos[i].posicion.fil, &nivel->obstaculos[i].posicion.col, dimension, true, true, posicion_jugador);
            
}

/*
 *
 * 
*/ 
void evaluar_interacciones(juego_t* juego, bool* detenerse)
{
    personaje_t personaje = juego->personaje;

    char objeto = obtener_objeto(juego->niveles[juego->nivel_actual], juego->personaje.posicion.fil, juego->personaje.posicion.col);

    if (objeto == BALDOSA_PINCHE && juego->personaje.tipo != RESISTENTE)
        juego->personaje.movimientos = juego->personaje.movimientos -2;

    else if (objeto == MONEDA)
    {
        juego->personaje.movimientos++;
        eliminar_objeto(&juego->niveles[juego->nivel_actual], personaje.posicion.fil, personaje.posicion.col);
    }

    else if (objeto == LLAVE && (juego->nivel_actual < 2 || juego->personaje.presiono_interruptor))
    {
        juego->personaje.tiene_llave = true;
        eliminar_objeto(&juego->niveles[juego->nivel_actual], personaje.posicion.fil, personaje.posicion.col);
    }

    else if (objeto == BOMBA)
        juego->personaje.movimientos = 0;

    else if (objeto == INTERRUPTOR)
    {
        juego->personaje.presiono_interruptor = true;
        eliminar_objeto(&juego->niveles[juego->nivel_actual], personaje.posicion.fil, personaje.posicion.col);
    }

    else if (objeto == SALIDA)
    {
        if (juego->nivel_actual < MAX_NIVELES -1 && juego->personaje.tiene_llave)
        {
            mostrar_juego(*juego); // MUESTRA LA POSICION ANTES DE AVANZAR DE NIVEL
            juego->personaje.movimientos = personaje.movimientos +10;
            juego->personaje.posicion.fil = juego->niveles[juego->nivel_actual+1].entrada.fil;
            juego->personaje.posicion.col = juego->niveles[juego->nivel_actual+1].entrada.col;
            juego->nivel_actual = juego->nivel_actual +1;
            juego->personaje.tiene_llave = false;
            juego->personaje.presiono_interruptor = false;
        }
    }

    else if (objeto == BALDOSA_TELETRANSPORTADORA)
    {
        int nueva_fila;
        int nueva_columna;
        obtener_posicion_vacia(juego->niveles[juego->nivel_actual], &nueva_fila, &nueva_columna, obtener_dimension(*juego), true, true, juego->personaje.posicion);
        mostrar_juego(*juego); // MUESTRA LA POSICION ANTES DE TELETRANSPORTAR AL JUGADOR
        juego->personaje.posicion.fil = nueva_fila;
        juego->personaje.posicion.col = nueva_columna;
        *detenerse = true;
    }
    
    else if (objeto == GUARDIA && juego->personaje.tipo != ATRACTIVO)
        juego->personaje.movimientos = 0;

}

/*
 *
 * 
 * 
*/ 
bool no_hay_pared_proxima(juego_t juego,char direccion, int dimension)
{
    bool no_hay_pared = true;
    nivel_t nivel_pared = juego.niveles[juego.nivel_actual];
    personaje_t personaje_pared = juego.personaje;
    for (int i = 0; i < nivel_pared.tope_paredes; i++)
    {
        if (direccion == ARRIBA)
            if (nivel_pared.paredes[i].fil == personaje_pared.posicion.fil -1 && nivel_pared.paredes[i].col == personaje_pared.posicion.col)
                no_hay_pared = false;

        if (direccion == ABAJO)
            if (nivel_pared.paredes[i].fil == personaje_pared.posicion.fil +1 && nivel_pared.paredes[i].col == personaje_pared.posicion.col)
                no_hay_pared = false;

        if (direccion == IZQUIERDA)
            if (nivel_pared.paredes[i].fil == personaje_pared.posicion.fil && nivel_pared.paredes[i].col == personaje_pared.posicion.col -1)
                no_hay_pared = false;

        if (direccion == DERECHA)
            if (nivel_pared.paredes[i].fil == personaje_pared.posicion.fil && nivel_pared.paredes[i].col == personaje_pared.posicion.col +1)
                no_hay_pared = false;
    }

    return no_hay_pared;
}

/*
 *
 * 
 * 
*/ 
void avanzar(juego_t* juego, char direccion, int dimension)
{
    if (juego->personaje.movimientos >= 0)
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
void llenar_mapa(int numero_nivel, char mapa[][MAX_DIMENSIONES], int dimension, nivel_t nivel, personaje_t personaje, bool tiene_llave)
{
    // Mapa Vacio
    for (int i = 0; i < dimension; i++)
        for (int j = 0; j < dimension; j++)
            mapa[i][j] = VACIO;

    // Poner paredes
    for (int i = 0; i < nivel.tope_paredes; i++)
        mapa[nivel.paredes[i].fil][nivel.paredes[i].col] = PAREDES;

    // Entrada
    //mapa[nivel.entrada.fil][nivel.entrada.col] = ENTRADA; 

    // Salida
    if (tiene_llave)
        mapa[nivel.salida.fil][nivel.salida.col] = SALIDA; 

    // Obstaculos
    for (int i = 0; i < nivel.tope_obstaculos; i++)
        mapa[nivel.obstaculos[i].posicion.fil][nivel.obstaculos[i].posicion.col] = nivel.obstaculos[i].tipo; 

    // Herramientas
    for (int i = 0; i < nivel.tope_herramientas; i++)
        if (nivel.herramientas[i].tipo != LLAVE || personaje.presiono_interruptor || numero_nivel < 3)
            mapa[nivel.herramientas[i].posicion.fil][nivel.herramientas[i].posicion.col] = nivel.herramientas[i].tipo; 

    // Posicion personaje
    mapa[personaje.posicion.fil][personaje.posicion.col] = JUGADOR;     

}

/*
 *
 * 
*/
bool no_tiene_objeto_continuo(nivel_t nivel, int fila, int columna, char objeto)
{
    bool no_hay_objeto = true;
    
    for (int i = 0; i < nivel.tope_obstaculos; i++)
    {
        if (nivel.obstaculos[i].tipo == objeto)
        {
            if ((nivel.obstaculos[i].posicion.fil +1 == fila) && (nivel.obstaculos[i].posicion.col == columna))
                no_hay_objeto = false;
            else if ((nivel.obstaculos[i].posicion.fil -1 == fila) && (nivel.obstaculos[i].posicion.col == columna))
                no_hay_objeto = false;
            else if ((nivel.obstaculos[i].posicion.fil == fila) && (nivel.obstaculos[i].posicion.col +1 == columna))
                no_hay_objeto = false;
            else if ((nivel.obstaculos[i].posicion.fil == fila) && (nivel.obstaculos[i].posicion.col -1 == columna))
                no_hay_objeto = false;
        }
    }
    return no_hay_objeto;
}

/*
 *
 * 
*/
void agregar_al_nivel(nivel_t* nivel, char tipo, int fila, int columna, int orden)
{
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

/* Le asigna el valor a multiplicador_dificultad dependiendo del caracter ingresado por el usuario
 * FACIL: cambio_monedas = 2, cambio_pinches = -2, cambio_movimientos = 5, cambio_guardias = -1
 * MEDIO: No produce cambios
 * FACIL: cambio_monedas = -2, cambio_pinches = 2, cambio_movimientos = -2, cambio_guardias = 1
*/
void obtener_dificultad(int* cambio_pinches, int* cambio_movimientos, int* cambio_guardias)
{
    char dificultad;
    printf(COLOR_VERDE"SELECCIONAR DIFICULTAD\nFACIL(f) - MEDIO(m) - DIFICIL(d)\n");
    scanf(" %c", &dificultad);
    while (dificultad != FACIL && dificultad != MEDIO && dificultad != DIFICIL)
    {
        printf("PARAMETRO INVALIDO: INGRESE UNA DIFICULTAD VALIDA\nFACIL(f) - MEDIO(m) - DIFICIL(d)\n");
        scanf(" %c", &dificultad);
    } 
    printf(NORMAL);

    if (dificultad == FACIL)
    {
        *cambio_pinches = -2;
        *cambio_movimientos = 5;
        *cambio_guardias = -1;
    }

    else if (dificultad == DIFICIL)
    {
        *cambio_pinches = 2;
        *cambio_movimientos = -2;
        *cambio_guardias = 1;
    }

}

void inicializar_juego(juego_t* juego, char tipo_personaje)
{
    int cambio_pinches = 0; int cambio_movimientos = 0; int cambio_guardias = 0;
    
    obtener_dificultad(&cambio_pinches, &cambio_movimientos, &cambio_guardias);

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

    juego->personaje.movimientos = 10 + cambio_movimientos;
    juego->personaje.tiene_llave = false;
    juego->personaje.presiono_interruptor = false;
    juego->personaje.murio = false;

    // CARGAR DATOS NIVELES
    for (int i = 0; i < MAX_NIVELES; i++)
    {
        int cantidad_baldosas_pinches = 0;
        int cantidad_guardia = 0;
        bool hay_bomba = false;
        if (i == 0)
        {
            cantidad_baldosas_pinches = 4 + cambio_pinches;
            cantidad_guardia = 2 + cambio_guardias;
            hay_bomba = false;
        }
        else if (i == 1)
        {
            cantidad_baldosas_pinches = 6 + cambio_pinches;
            cantidad_guardia = 3 + cambio_guardias;
            hay_bomba = false;
        }
        else if (i == 2)
        {
            cantidad_baldosas_pinches = 6 + cambio_pinches;
            cantidad_guardia = 3 + cambio_guardias;
            hay_bomba = true;
        }
        else // i == 3
        {
            cantidad_baldosas_pinches = 10 + cambio_pinches;
            cantidad_guardia = 4 + cambio_guardias;
            hay_bomba = true;
        }
        inicializar_nivel(&juego->niveles[i], i+1, cantidad_baldosas_pinches, cantidad_guardia, hay_bomba);
    }         

    juego->nivel_actual = 3;
    juego->personaje.posicion.fil = juego->niveles[juego->nivel_actual].entrada.fil;
    juego->personaje.posicion.col = juego->niveles[juego->nivel_actual].entrada.col;

}

int estado_juego(juego_t juego)
{
    personaje_t personaje = juego.personaje;
    nivel_t nivel = juego.niveles[juego.nivel_actual];

    if ((juego.nivel_actual == (MAX_NIVELES -1)) && (personaje.posicion.fil == nivel.salida.fil) && (personaje.posicion.col == nivel.salida.col) && juego.personaje.tiene_llave)
        return 1;
    else if (juego.personaje.movimientos <= 0)
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

    nivel->tope_herramientas = 0;
    nivel->tope_obstaculos = 0;
    bool entrada_asignada = false;
    bool salida_asignada = false;

    coordenada_t jugador_no_asignado;
    jugador_no_asignado.fil = -1;
    jugador_no_asignado.col = -1;

    // Paredes
    nivel->tope_paredes = 0;
    obtener_paredes(numero_nivel, nivel->paredes, &nivel->tope_paredes);

    // Entrada - posicion aleatoria -
    obtener_posicion_vacia(*nivel, &fila, &columna, dimension, entrada_asignada, salida_asignada, jugador_no_asignado);
    entrada_asignada = true;
    agregar_al_nivel(nivel, ENTRADA, fila, columna, 0);

    // Salida - posicion aleatoria -
    obtener_posicion_vacia(*nivel, &fila, &columna, dimension, entrada_asignada, salida_asignada, jugador_no_asignado);
    salida_asignada = true;
    agregar_al_nivel(nivel, SALIDA, fila, columna, 0);

    // OBSTACULOS
    int cantidad_bomba = 0;
    if (hay_bomba) cantidad_bomba++;
    int tope_obstaculos = cantidad_baldosas_pinches + cantidad_guardia + cantidad_bomba;

    while (nivel->tope_obstaculos < tope_obstaculos)
    {
        obtener_posicion_vacia(*nivel, &fila, &columna, dimension, entrada_asignada, salida_asignada, jugador_no_asignado);

        // Baldosas pinche - posicion aleatoria y continuo - //CORREGIR
        if (nivel->tope_obstaculos < cantidad_baldosas_pinches)
        {
            if (nivel->tope_obstaculos == 0)
                agregar_al_nivel(nivel, BALDOSA_PINCHE, fila, columna, nivel->tope_obstaculos);      
            else
            {
                do
                {
                    obtener_posicion_vacia(*nivel, &fila, &columna, dimension, entrada_asignada, salida_asignada, jugador_no_asignado);
                } 
                while (no_tiene_objeto_continuo(*nivel, fila, columna, BALDOSA_PINCHE));
                agregar_al_nivel(nivel, BALDOSA_PINCHE, fila, columna, nivel->tope_obstaculos);      
            } 
        }

        // Guardias - posicion aleatoria -
        else if(nivel->tope_obstaculos < cantidad_baldosas_pinches + cantidad_guardia)
        {
            agregar_al_nivel(nivel, GUARDIA, fila, columna, nivel->tope_obstaculos);                
        }

        // Bomba - posicion aleatoria -
        else
        {
            agregar_al_nivel(nivel, BOMBA, fila, columna, nivel->tope_obstaculos);                
        }
        nivel->tope_obstaculos++;             
    }

    // HERRAMIENTAS
    int cantidad_monedas = cantidad_baldosas_pinches / 2;
    int cantidad_baldosa_teletransportadora = cantidad_guardia;
    int cantidad_interruptores = cantidad_bomba;
    int tope_herramientas = cantidad_monedas + cantidad_baldosa_teletransportadora + cantidad_interruptores + 1;
    
    while (nivel->tope_herramientas < tope_herramientas)
    {
        obtener_posicion_vacia(*nivel, &fila, &columna, dimension, entrada_asignada, salida_asignada, jugador_no_asignado);
        
        // Llave
        if (nivel->tope_herramientas == 0)
            agregar_al_nivel(nivel, LLAVE, fila, columna, nivel->tope_herramientas);  

        // Monedas - posicion aleatoria -
        else if (nivel->tope_herramientas < 1 + cantidad_monedas)
            agregar_al_nivel(nivel, MONEDA, fila, columna, nivel->tope_herramientas);                
        
        // Baldosa teletransportadora - posicion aleatoria -
        else if(nivel->tope_herramientas < 1 + cantidad_monedas + cantidad_baldosa_teletransportadora)
            agregar_al_nivel(nivel, BALDOSA_TELETRANSPORTADORA, fila, columna, nivel->tope_herramientas);                

        // Interruptor - posicion aleatoria -
        else
            agregar_al_nivel(nivel, INTERRUPTOR, fila, columna, nivel->tope_herramientas); 

        nivel->tope_herramientas++;
    }
}

void mover_personaje(juego_t* juego, char movimiento)
{   
    int dimension = obtener_dimension(*juego);

    int progreso_nivel = 0;
    bool detenerse = false;
    do
    {
        if (no_hay_pared_proxima(*juego, movimiento, dimension)) avanzar(juego, movimiento, dimension);
        progreso_nivel = estado_nivel(juego->personaje, juego->niveles[juego->nivel_actual].salida);
        evaluar_interacciones(juego, &detenerse);

        // Revivir personaje
        if (juego->personaje.tipo == DOBLE && juego->personaje.movimientos <= 0 && !juego->personaje.murio)
        {
            juego->personaje.movimientos = 10;
            juego->personaje.murio = true;
            detenerse = true;
        }

        mostrar_juego(*juego);

    } while(no_hay_pared_proxima(*juego, movimiento, dimension) && progreso_nivel == 0 && juego->personaje.movimientos > 0 && !detenerse);

    if (juego->personaje.movimientos > 0) juego->personaje.movimientos = juego->personaje.movimientos -1;

    cambiar_posicion_guardias(&juego->niveles[juego->nivel_actual], dimension, juego->personaje.posicion);
    //evaluar_interacciones(juego, &detenerse);
    mostrar_juego(*juego);

}

/* Agrega color al juego dependiendo del valor de objeto (caracter con valor de un obstaculo, herramienta, pared o jugador)
 * el bool tiene llave chequa si se le debe agregar color a la salida solo si ya fue descubierta
*/ 
void agregar_color(char objeto, bool tiene_llave)
{
    //printf(FONDO_BLANCO);
    if (objeto == MONEDA) printf(COLOR_AMARILLO);
    else if (objeto == PAREDES) printf(COLOR_VERDE);            
    else if (objeto == BALDOSA_PINCHE) printf(COLOR_ROJO);
    else if (objeto == BOMBA) printf(COLOR_ROJO);
    else if (objeto == BALDOSA_TELETRANSPORTADORA) printf(COLOR_MAGENTA);
    else if (objeto == GUARDIA) printf(COLOR_AZUL);
    else if (objeto == LLAVE || objeto == INTERRUPTOR) printf(COLOR_CYAN);
    else if (objeto == JUGADOR) printf(COLOR_BLANCO);
    else if(tiene_llave && objeto == SALIDA) printf(FONDO_VERDE COLOR_BLANCO);
}

/* Imprime los espacios restantes para que la linea
 * ocupe un total de MARGEN_IZQUIERDO caracteres
*/ 
void imprimir_margen(char palabra[])
{
    size_t espacio = MARGEN_IZQUIEDO;
    size_t margen = espacio - strlen(palabra);

    for (int i = 0; i < margen; i++)
        printf(" ");
}

/* Imprime la interfaz del juego mientras el mismo esta transcurriendo, numero de fila tiene un valor entre 0 y 16
 * lado sera DERECHA o IZQUIERDA
*/
void imprimir_interfaz(juego_t juego, int fila, char lado)
{

    printf(COLOR_VERDE);
    if (fila == 0)
    {
        if (lado == DERECHA)
        {
            printf("      HABILIDAD DEL PERSONAJE: ");
            if (juego.personaje.tipo == DOBLE) printf("DOBLE VIDA");
            else if (juego.personaje.tipo == RESISTENTE) printf("INMUNE A LOS PINCHES");
            else printf("INMUNE A LOS GUARDIAS");

        }
        else
        {
            printf("GLOSARIO:");
            imprimir_margen("GLOSARIO:");
        }
    }

    else if(fila == 1)
    {
        if (lado == DERECHA && juego.personaje.murio && juego.personaje.tipo == DOBLE)
            printf(COLOR_ROJO"      ATENCION: YA NO QUEDAN VIDAS"COLOR_VERDE);
        else if (lado == IZQUIERDA)
            imprimir_margen("");
    }  

    else if(fila == 2)
    {
        if (lado == IZQUIERDA)
        {
            printf(COLOR_BLANCO "J: JUGADOR");
            imprimir_margen("J: JUGADOR");  
        } 
    }  

    else if (fila == 3) 
    {
        if (lado == DERECHA)
            printf("      NIVEL: %i", juego.nivel_actual +1);
        else
        {
            printf(COLOR_CYAN "L: LLAVE");
            imprimir_margen("L: LLAVE");                
        }                              
    }

    else if (fila == 4)
    {
        if (lado == DERECHA)
            printf("      CANTIDAD DE MOVIMIENTOS RESTANTES: %i", juego.personaje.movimientos);
        else 
        {            
            printf(COLOR_AMARILLO "M: MONEDA (+1 mov)");
            imprimir_margen("M: MONEDA (+1 mov)");        
        }        
    } 
    
    else if (fila == 5) 
    {
        if (lado == DERECHA)
        {
            printf("      "FONDO_VERDE COLOR_BLANCO"SALIDA:"NORMAL);
            if (juego.personaje.tiene_llave) printf(COLOR_VERDE" DISPONIBLE");
            else printf(COLOR_ROJO " OCULTA - SE NECESITA AGARRAR LLAVE" COLOR_VERDE);
        }
        else 
        {
            printf(COLOR_ROJO "P: PINCHE (-1 mov)");
            imprimir_margen("P: PINCHE (-1 mov)");        
        }
    }

    else if (fila == 6)
    {
        if (lado == IZQUIERDA)
        {
            printf(COLOR_ROJO "G: GUARDIA (-todos mov)");
            imprimir_margen("G: GUARDIA (-todos mov)");        
        }    
    }

    else if (fila == 7)
    {
        if (lado == IZQUIERDA)
        {
            printf(COLOR_MAGENTA "T: TELETRANSPORTADOR");
            imprimir_margen("T: TELETRANSPORTADOR");        
        }
        else if (lado == DERECHA && (juego.nivel_actual == 2 || juego.nivel_actual == 3))
            printf("      ACCIONAR EL INTERRUPTOR REVELA LA LLAVE");
    }

    else if (fila == 8)
    {
        if (lado == IZQUIERDA && (juego.nivel_actual == 2 || juego.nivel_actual == 3))
        { 
            printf(COLOR_CYAN "I: INTERRUPTOR");
            imprimir_margen("I: INTERRUPTOR");        
        }
        else if (lado == IZQUIERDA)
            imprimir_margen("");
    }

    else if (fila == 9)
    {
        if (lado == IZQUIERDA && (juego.nivel_actual == 2 || juego.nivel_actual == 3))
        {
            printf(COLOR_ROJO "B: BOMBA (-todos mov)");
            imprimir_margen("B: BOMBA (-todos mov)");        
        }
        else if (lado == IZQUIERDA)
            imprimir_margen("");
    }

    else imprimir_margen("");
    printf(NORMAL);
}

/* Recibe el juego cargado; numero_nivel entre 0 y 3; dimension valdra 12 o 17
 * Imprime en pantalla un mapa de dos dimensiones ademas de datos utiles para el usuario
*/ 
void mostrar_nivel(juego_t juego, int numero_nivel, int dimension)
{
    detener_el_tiempo((float) 0.128);
    system("clear");

    char mapa[MAX_DIMENSIONES][MAX_DIMENSIONES];

    llenar_mapa(juego.nivel_actual +1,mapa, dimension, juego.niveles[juego.nivel_actual], juego.personaje, juego.personaje.tiene_llave);
    printf(COLOR_ROJO"                                   DEXTER'S LABORATORY\n\n");
    for (int i = 0; i < dimension; i++)
    {
        imprimir_interfaz(juego, i, IZQUIERDA);
            
        for (int j = 0; j < dimension; j++)
        {
            agregar_color(mapa[i][j], juego.personaje.tiene_llave);
            printf(" %c" NORMAL, mapa[i][j]);
        }
        imprimir_interfaz(juego, i, DERECHA);
        printf("\n"); 
    } 
}

/* imprime el signo de victoria si el usuario completo el juego (true)
 * imprime el signo de derrota si el usuario no pudo completar el juego (false)
*/ 
void imprimir_final(bool gano, int dimension)
{
    if(gano)
        printf(COLOR_VERDE"              _____  _____  _____   ___  ______   ___   _____  _____  _____  _ \n"  
                          "             |  ___|/  ___|/  __ | / _ | | ___ | / _ | /  ___||_   _||  ___|| |\n"   
                          "             | |__  | `--. | /  ||/ /_| || |_/ // /_| \\ `--.   | |  | |__  | |\n"
                          "             |  __|  `--. || |    |  _  ||  __/ |  _  | `--. |  | |  |  __| | |\n"
                          "             | |___ /|__/ /| |__/|| | | || |    | | | |/|__/ /  | |  | |___ |_|\n"
                          "             |____/ |____/  |____/|_| |_/|_|    |_| |_/|____/   |_/  |____/ (_)\n"
                          "                                                                           \n\n\n"
        );

    else // perdio
        printf(COLOR_ROJO"               _____                                                    \n"  
                         "              |  __ |                                                   \n"   
                         "              | |      __ _  _ __ ___    ___    ___  __   __  ___  _ __ \n"
                         "              | | __  / _` || '_ ` _  | / _ |  / _ | | | / / / _ || '__|\n"
                         "              | |_| || (_| || | | | | ||  __/ | (_) | | V / |  __/| |   \n"
                         "              |_____/ |__,_||_| |_| |_| |___|  |___/   |_/   |___||_|   \n"
                         "                                                                    \n\n\n"
        );
}

void mostrar_juego(juego_t juego)
{
    int estado = estado_juego(juego);

    // Jugando
    mostrar_nivel(juego, juego.nivel_actual, obtener_dimension(juego));

    // Gano
    if(estado == 1)
    {
        imprimir_final(true, obtener_dimension(juego));
        juego.personaje.movimientos = 0;
    }
    // Perdio    
    else if (estado == -1)
        imprimir_final(false, obtener_dimension(juego));
}