#include "escape_laboratorio.h"
#include "utiles.h"

// Constante de Personajes
const char JOHNNY = 'J';
const char BELLOTA = 'S';
const char POLLITO = 'P'; 
const char BLUE = 'B'; 
const char PURO_HUESO = 'H';
const char CORAJE = 'C';

// Constantes de tipo de personaje
const char DOBLE = 'D';
const char RESISTENTE = 'R';
const char ATRACTIVO = 'A';

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

    // CARGAS DATOS NIVELES
    for (int i = 1; i <= MAX_NIVELES; i++)
    {
        obtener_paredes(i, juego->niveles[i].paredes,&juego->niveles[i].tope_paredes);
    }
}

int estado_juego(juego_t juego)
{
    // TODO
    return 0;
}

int estado_nivel(nivel_t nivel)
{
    // TODO
    return 0;
}

void inicializar_nivel(nivel_t* nivel, int cantidad_baldosas_pinches, int cantidad_guardia, bool hay_bomba)
{
    // TODO
}

void mover_personaje(juego_t* juego, char movimiento)
{
    // TODO
}

void mostrar_juego(juego_t juego)
{
    // TODO
}