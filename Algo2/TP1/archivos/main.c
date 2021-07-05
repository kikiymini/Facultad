#include "salon.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "util.h"

int main(){
    printf("Crear un salon usando el archivo 'salon_original.sal'\n");
    salon_t* salon = salon_leer_archivo("salon_original.sal");
    if (salon == NULL)
    {
        printf("No se pudo crear el salon!\n");
        return 1;
    }

    printf("\nObtener los entrenadores con al menos 3 ligas ganadas y mostrarlos por pantalla.\n");
    int cant_victorias_min = 3;
    entrenador_t** entrenadores_ganadores = salon_obtener_entrenadores_mas_ganadores(salon, cant_victorias_min);
    if (entrenadores_ganadores == NULL)
    {
        printf("No se pudieron obtener entrenadores!\n");
        salon_destruir(salon);
        return 1;
    }

    size_t cantidad_entrenadores = vtrlen(entrenadores_ganadores);
    for (size_t i = 0; i < cantidad_entrenadores; i++)
        salon_mostrar_entrenador(entrenadores_ganadores[i]);
    free(entrenadores_ganadores);

    printf("\nAgregar 2 entrenadores al salon con 5 y 7 victorias respectivamente.\n");
    entrenador_t* entrenador_nuevo1 = calloc(1, sizeof(entrenador_t));
    if (entrenador_nuevo1 == NULL)
    {
        printf("No se pudo crear un nuevo entrenador!\n");
        salon_destruir(salon);
        return 1;
    }
    strcpy(entrenador_nuevo1->nombre, "Juan");
    entrenador_nuevo1->victorias = 5;
    salon_agregar_entrenador(salon, entrenador_nuevo1);

    entrenador_t* entrenador_nuevo2 = calloc(1, sizeof(entrenador_t));
    if (entrenador_nuevo2 == NULL)
    {
        printf("No se pudo crear un nuevo entrenador!\n");
        salon_destruir(salon);
        return 1;
    }
    strcpy(entrenador_nuevo2->nombre, "Daniel");
    entrenador_nuevo2->victorias = 7;
    salon_agregar_entrenador(salon, entrenador_nuevo2);

    printf("\nObtener los entrenadores con al menos 5 ligas ganadas y mostrarlos por pantalla.\n");
    cant_victorias_min = 5;
    entrenadores_ganadores = salon_obtener_entrenadores_mas_ganadores(salon, cant_victorias_min);
    if (entrenadores_ganadores == NULL)
    {
        printf("No se pudieron obtener entrenadores!\n");
        salon_destruir(salon);
        return 1;
    }

    cantidad_entrenadores = vtrlen(entrenadores_ganadores);
    for (size_t i = 0; i < cantidad_entrenadores; i++) 
        salon_mostrar_entrenador(entrenadores_ganadores[i]);
    free(entrenadores_ganadores);

    printf("\nGuardar el salon a un nuevo archivo 'salon_modificado.sal'\n");
    int guardar = salon_guardar_archivo(salon, "salon_modificado.sal");
    if (guardar == -1)
    {
        printf("No se pudo guardar el archivo!\n");
        return 1;
    }


    salon_destruir(salon);
    printf("\nSalir con valor de retorno 0\n");
    return 0;
}
