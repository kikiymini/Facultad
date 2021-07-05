#include "salon.h"
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include <stdbool.h>

const char separador = ';';
const int linea_entrenador = 2;
const int linea_pokemon = 6;

// Para imprimir con color
#define NORMAL "\x1b[0m"
#define COLOR_ROJO "\x1b[31m" 
#define COLOR_ROJO_CLARO "\x1b[91m" 
#define COLOR_AMARILLO "\x1b[33m" 
#define COLOR_VERDE "\x1b[32m"
#define COLOR_MAGENTA "\x1b[95m"
#define COLOR_AZUL "\x1b[94m"
#define COLOR_NEGRO "\x1b[30m"
#define COLOR_CYAN "\x1b[36m"
#define COLOR_BLANCO "\x1b[97m"
#define FONDO_BLANCO "\x1b[100m"
#define FONDO_VERDE "\x1b[42m"

/**
 * Carga los datos de un entrenador con los 
 * strings pertenecientes a elementos_linea
 * 
 * Asigna en el orden seguido por las instrucciones 
 * nombre_entrenador;victorias
 */ 
void llenar_entrenador(entrenador_t* entrenador, char** elementos_linea)
{
    if (entrenador == NULL)
        return;

    strcpy(entrenador->nombre,*elementos_linea);
    elementos_linea++;
    entrenador->victorias = atoi(*elementos_linea);

    return;
}

/**
 * Carga los datos de un pokemos con los 
 * strings pertenecientes a elementos_linea
 * 
 * Asigna en el orden seguido por las instrucciones 
 * nombre_pokemon;nivel;defensa;fuerza;inteligencia;velocidad
 */ 
void llenar_pokemon(pokemon_t* pokemon, char** elementos_linea)
{
    if (pokemon == NULL)
        return;

    strcpy(pokemon->nombre, *elementos_linea);
    elementos_linea++;
    pokemon->nivel = atoi(*elementos_linea);
    elementos_linea++;
    pokemon->defensa = atoi(*elementos_linea);
    elementos_linea++;
    pokemon->fuerza = atoi(*elementos_linea);
    elementos_linea++;
    pokemon->inteligencia = atoi(*elementos_linea);
    elementos_linea++;
    pokemon->velocidad = atoi(*elementos_linea);

    return;
}

/**
 * De ser existente, libera la memoria reservada
 * para la linea y su forma partida 
 */ 
void liberar_memoria_linea(char* linea, char** elementos_linea)
{
    if (elementos_linea != NULL)
        vtrfree(elementos_linea);
    if (linea != NULL)
        free(linea);

    return;
}

/**
 * Libera memoria asignada al entrenador y a su equipo
 */
void liberar_entrenador(entrenador_t* entrenador, pokemon_t** equipo)
{
    if (equipo != NULL)
        vtrfree(equipo);

    if (entrenador != NULL)
        free(entrenador);

    return;
}

/**
 * Libera memoria previamente asignada 
 * y carga la siguiente linea del archivo
 */ 
char* actualizar_linea(FILE* archivo, char* linea, char** elementos_linea)
{
    liberar_memoria_linea(linea, elementos_linea);
    char* nueva_linea = fgets_alloc(archivo);
    return nueva_linea;
}

/**
 * Imprime en pantalla el pokemon enviado
 * con sus respectivas caracteristicas
*/ 
void imprimir_pokemon(pokemon_t* pokemon)
{
    if (pokemon == NULL)
        return;

    printf("%s\n", pokemon->nombre);
    printf(COLOR_VERDE"Nivel: %i\n", pokemon->nivel);
    printf(COLOR_AZUL"Defensa: %i\n", pokemon->defensa);
    printf(COLOR_ROJO"Fuerza: %i\n", pokemon->fuerza);
    printf(COLOR_CYAN"Inteligencia: %i\n", pokemon->inteligencia);
    printf(COLOR_AMARILLO"Velocidad %i\n\n"NORMAL, pokemon->velocidad);

    return;
}

/**
 * Imprime en pantalla el entrenador enviado
 * con sus respectivas caracteristicas
*/ 
void imprimir_entrenador(entrenador_t* entrenador)
{
    if (entrenador == NULL)
        return;

    printf("---------------\n");
    printf("Entrenador: %s\nVictorias: %i\n\n", entrenador->nombre, entrenador->victorias);
    printf(COLOR_MAGENTA"\tEquipo:\n\n"NORMAL);

    return;
}

/**
 * Posiciona el ultimo entrenador del salon en
 * su posicion adecuada acorde a la cantidad
 * de victorias del mismo
 */ 
void ordenar_salon(salon_t* salon)
{
    if (salon == NULL)
        return;
    
    size_t cantidad_entrenadores = vtrlen(salon->entrenadores);
    if (cantidad_entrenadores > 1)
    {
        size_t pos_entrenador_agregador = cantidad_entrenadores -1;
        size_t evaluaciones = 0;
        while(evaluaciones != (cantidad_entrenadores-1) && salon->entrenadores[pos_entrenador_agregador]->victorias < salon->entrenadores[pos_entrenador_agregador -1]->victorias)
        {
            entrenador_t* entrenador_aux = salon->entrenadores[pos_entrenador_agregador -1];
            salon->entrenadores[pos_entrenador_agregador -1] = salon->entrenadores[pos_entrenador_agregador];
            salon->entrenadores[pos_entrenador_agregador] = entrenador_aux;
            pos_entrenador_agregador--;
            evaluaciones++;
        } 
    }

    return;
}

/**
 * Guarda en el archivo el entrenador
 * y sus pokemones, con sus respectivas
 * caracteristicas
 */ 
void guardar_entrenador(FILE* archivo, entrenador_t* entrenador)
{
    if(archivo == NULL || entrenador == NULL)
        return;

    fprintf(archivo, "%s;%i\n", entrenador->nombre, entrenador->victorias);
    size_t cantidad_pokemones = vtrlen(entrenador->equipo);
    for (size_t j = 0; j < cantidad_pokemones; j++)
        fprintf(archivo, "%s;%i;%i;%i;%i;%i\n",entrenador->equipo[j]->nombre, entrenador->equipo[j]->nivel, entrenador->equipo[j]->defensa, entrenador->equipo[j]->fuerza, entrenador->equipo[j]->inteligencia, entrenador->equipo[j]->velocidad);

    return;
}

salon_t* salon_leer_archivo(const char* nombre_archivo){
    FILE* archivo_salon = fopen(nombre_archivo, "r");
    if (!archivo_salon)
        return NULL;

    salon_t* salon_leido = calloc(1, sizeof(salon_t));
    if (!salon_leido)
    {
        fclosen(archivo_salon);
        return NULL;
    }

    char* linea_leida = fgets_alloc(archivo_salon);
    if (linea_leida == NULL)
    {
        fclosen(archivo_salon);
        salon_destruir(salon_leido);
        return NULL;
    }

    char** elementos_linea = split(linea_leida, separador); 
    if (elementos_linea == NULL)
    {
        fclosen(archivo_salon);
        salon_destruir(salon_leido);
        free(linea_leida);        
        return NULL;
    }

    size_t cantidad_elementos_linea = vtrlen(elementos_linea);

    while(linea_leida != NULL)
    {
        entrenador_t* entrenador_leido = calloc(1, sizeof(entrenador_t));
        if (!entrenador_leido)
        {
            salon_destruir(salon_leido);
            liberar_memoria_linea(linea_leida, elementos_linea);
            fclosen(archivo_salon);
            return NULL;
        }

        llenar_entrenador(entrenador_leido, elementos_linea);

        linea_leida = actualizar_linea(archivo_salon, linea_leida, elementos_linea);
        elementos_linea = split(linea_leida, separador); 
        cantidad_elementos_linea = vtrlen(elementos_linea);

        while(cantidad_elementos_linea == linea_pokemon)
        {
            pokemon_t* pokemon_leido = calloc(1, sizeof(pokemon_t));
            if (!pokemon_leido)
            {
                salon_destruir(salon_leido);
                liberar_memoria_linea(linea_leida, elementos_linea);
                free(entrenador_leido);
                fclosen(archivo_salon);
                return NULL;
            }

            llenar_pokemon(pokemon_leido, elementos_linea);
            entrenador_leido->equipo = vtradd(entrenador_leido->equipo, pokemon_leido);
            
            linea_leida = actualizar_linea(archivo_salon, linea_leida, elementos_linea);
            elementos_linea = split(linea_leida, separador); 
            cantidad_elementos_linea = vtrlen(elementos_linea);
        }
        salon_agregar_entrenador(salon_leido, entrenador_leido);  
    }

    liberar_memoria_linea(linea_leida, elementos_linea);
    fclosen(archivo_salon);
    return salon_leido;
}

int salon_guardar_archivo(salon_t* salon, const char* nombre_archivo){
    if (salon == NULL)
        return -1;
    
    FILE* nuevo_archivo = fopen(nombre_archivo, "w");
    if (!nuevo_archivo)
        return -1;

    size_t tamanio_salon = vtrlen(salon->entrenadores);
    for (size_t i = 0; i < tamanio_salon; i++)
        guardar_entrenador(nuevo_archivo, salon->entrenadores[i]);

    fclose(nuevo_archivo);
    return (int)tamanio_salon;
}

salon_t* salon_agregar_entrenador(salon_t* salon, entrenador_t* entrenador){
    if (salon == NULL || entrenador == NULL)
        return NULL;

    salon->entrenadores = vtradd(salon->entrenadores, entrenador);
    ordenar_salon(salon);

    return salon;
}

entrenador_t** salon_obtener_entrenadores_mas_ganadores(salon_t* salon, int cantidad_minima_victorias){
    if (salon == NULL)
        return NULL;
    
    entrenador_t** entrenadores_compatibles = NULL;
    
    size_t cantidad_entrenadores = vtrlen(salon->entrenadores);
    for (size_t i = 0; i < cantidad_entrenadores; i++)
        if (salon->entrenadores[i]->victorias >= cantidad_minima_victorias)
            entrenadores_compatibles = vtradd(entrenadores_compatibles, salon->entrenadores[i]);

    return entrenadores_compatibles;
}

void salon_mostrar_entrenador(entrenador_t* entrenador){
    if (entrenador == NULL)
        return;

    imprimir_entrenador(entrenador);    
    size_t cantidad_pokemones = vtrlen(entrenador->equipo);
    for(size_t i = 0; i < cantidad_pokemones; i++)
        imprimir_pokemon(entrenador->equipo[i]);

    return;
}

void salon_destruir(salon_t* salon){
    if (salon == NULL)
        return;

    size_t cantidad_entrenadores = vtrlen(salon->entrenadores);
    for (size_t i = 0; i < cantidad_entrenadores; i++)
        liberar_entrenador(salon->entrenadores[i], salon->entrenadores[i]->equipo);

    free(salon->entrenadores);
    free(salon);
    return;
}