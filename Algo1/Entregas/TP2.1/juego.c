#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // Para usar rand
#include <time.h> // Para obtener una semilla desde el reloj

// Bibleotecas
#include "detector_personajes.h"
#include "escape_laboratorio.h"
#include "utiles.h"

// Colores
#define NORMAL "\e[0m"
#define COLOR_VERDE "\e[32m"
#define COLOR_ROJO "\e[31m" 

/* Selecciona el personaje de cartoon netword adecuado
 *
*/
void seleccionar_personaje(char* personaje_seleccionado);

/* Solicita al usuario una direccion de movimiento y 
 * actualiza el juego mientras este se mantenga en curso
*/ 
void actualizar_juego(juego_t* juego);

/* Imprime en pantalla la imagen del juego
*/
void imprimir_titulo();

/* Imprime el titulo en pantalla i le indica al usuario
 * sus opciones para jugar
*/ 
void comenzar();

int main()
{
    // Semilla para obtener numeros aleatorios
    srand (( unsigned)time(NULL));

    // Inicio
    comenzar();

    // Preguntar al usuario el personaje que desea usar
    char personaje_seleccionado;
    //seleccionar_personaje(&personaje_seleccionado);
    personaje_seleccionado = 'B';

    // Inicializar juego cargando niveles
    juego_t juego;
    inicializar_juego(&juego, personaje_seleccionado);

    // Movimiento
    mostrar_juego(juego);
    while((estado_juego(juego) != -1) && (estado_juego(juego) != 1))
        actualizar_juego(&juego);    

    // Mostrar ultima pantalla
    mostrar_juego(juego);
    return 0;
}

void actualizar_juego(juego_t* juego)
{
    if (juego->personaje.movimientos > 0)
    {
        char direccion;
        printf(COLOR_VERDE "PROXIMO MOVIMIENTO:\n(w)arriba - (s)abajo - (a)izquierda - (d)derecha: ");
        scanf(" %c", &direccion); 
        while(direccion != 'a' && direccion != 's' && direccion != 'd' && direccion != 'w')
        {
            printf("ERROR! INGRESE UN CARACTER VALIDO:\n(w)arriba - (s)abajo - (a)izquierda - (d)derecha:");
            scanf(" %c", &direccion); 
        }
        mover_personaje(juego, direccion);
        }
}

void comenzar()
{
    imprimir_titulo();
    char comenzar;
    printf("COMENZAR (c): ");
    scanf(" %c", &comenzar);
    while (comenzar != 'c')
    {
        printf("ERROR! INGRESE UN CARACTER VALIDO:\nescriba 'c' para comenzar: ");
        scanf(" %c", &comenzar);
    }
    printf(NORMAL);
}

void imprimir_titulo()
{
    system("clear");
    printf(COLOR_ROJO
    " Dexter's laboratory"COLOR_VERDE"                                                                 .-:::.         \n"COLOR_ROJO
    "   By Juan Martin Muñoz"COLOR_VERDE"                                                         -/:/://///+/.       \n"COLOR_ROJO
    "       Algoritmos1 - Catedra Mendez"COLOR_VERDE"                                          .-:/::ooooooooo/o:     \n"
    "                                                                         .---`  :.sooooooooos-y     \n" 
    "                                                                     .---`     `:.sooooooooos:o     \n" 
    "                                                                 `---.`         :`:oooooooo++o`     \n" 
    "                                                           .--:--.`              ----:///+//-       \n" 
    "                                                       `-:/+:-`             `.----::++::-``         \n" 
    "                                                   `.://:::/:`   `.....------.``                    \n" 
    "                                  ``            .-//::----+..://+++/                                \n" 
    "           -                    :ssso.`.  /---: :+----:/--:-o//:-.`                                 \n"    
    "        `:oys/`                `ys.-o:-+.../o/s///o:+-   :o                                         \n"
    "      `/o/::s:/+-/:.           `ys`.o::+sssysoydyy.``:o:+    :o                                     \n"
    "    `/o/::+o+s-s/:++/           :sshhhyyooosydsdhy+/o/o+/-`...+:-                                   \n"
    "    `ho:+o/:-+o-s-://o-....`.-/--ssyhsy+yssyh/ohhhyo:/`      ..                                     \n"
    "     `oy/-/+o/+o+/////-`.--:`os.-..:/+/::-:://o++syoyo+::-  ``.`.:                                  \n"
    "       :ss+/--:+soo.`:.  . - ydoh+/:/`/-.--::--+os+/:-:///--..                                      \n"
    "        .s+:/++//o-:`/   .`:../:/:ohoyy+////odmddh+:.-.`                                            \n"
    "         `+y/:://-+//-..-:o//o/../smmNho...`-oh/.     `.-.`                                         \n"
    "           -oo/:-/o/::::---:-`   `:/:+s:      //:.`      `.-.                                       \n"
    "            `....``     `--`   `:::/+-`        -+:-.`       .--.``                                  \n"
    "                     ``//-.--:/+::/-            `+/::-``.--::`./                                    \n"
    "                     s..``   :/:s-                /o::o//..`    ``:-`                               \n"
    "                     o.```  .s/y`                   .o/o-+`:.`   `-:.`                              \n"
    "                     `:s.........+-                 `+y-::/-`         -::.                          \n"
    "                       .+`        :/`                 :///:-:-`         `-/:`                       \n"
    "                        .o`        `::`                `-s/---:-.          `:/:`                    \n"
    "                       `-o:          `::`                `os:---::-`          .://.`                \n"
    "                     .oo+.----:.`      `::`                :y+:---:::.           .+ss+`             \n"
    "                   `:/+-` .::/:://` `..-:+s-                `ss:-----:/:----....`./+y+`             \n"
    "                  :y:---:+::::::::++oo+/o+                    /d:::::/s/:-    `..---:+s+            \n"
    "                   s/////+::------.``                         `ss+++/+:--:+:::::---:::/s            \n"
    "                                                                .::/+++/:+:://+++////::-            \n"
    "                                                                       .::--.`                      \n");
}

void seleccionar_personaje(char* personaje_seleccionado)
{
    printf(COLOR_VERDE);
    detectar_personaje(personaje_seleccionado);
    printf("PRESIONE ENTER PARA CONTINUAR");
    while(getchar() != '\n');    
}
