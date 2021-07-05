#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // Para usar rand
#include <time.h> // Para obtener una semilla desde el reloj

// Bibleotecas
#include "escape_laboratorio.h"
#include "utiles.h"
// #include "detector_personaje.h"

int main()
{
    // Semilla para obtener numeros aleatorios
    srand (( unsigned)time(NULL));

    // Preguntar al usuario el personaje que desea usar
    char personaje_seleccionado = 'J';

    // Inicializar juego cargando niveles
    juego_t juego;
    inicializar_juego(&juego, personaje_seleccionado);
    juego.nivel_actual = 0;
    juego.personaje.posicion.fil = juego.niveles[juego.nivel_actual].entrada.fil;
    juego.personaje.posicion.col = juego.niveles[juego.nivel_actual].entrada.col;

    while(estado_juego(juego) != -1)
    {
        mostrar_juego(juego);

        // Movimiento
        if (juego.personaje.movimientos > 0)
        {
            char direccion;
            printf("proximo movimiento:\n(w)arriba - (s)abajo - (a)izquierda - (d)derecha: ");
            scanf(" %c", &direccion); // FORZAR BUEN USO
            mover_personaje(&juego, direccion);
        }
    }
    return 0;
}

