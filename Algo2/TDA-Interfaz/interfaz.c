#include "interfaz.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

elemento_t* crear_elemento(char* nombre, ejecutar funcion, void* extra1, void* extra2)
{
    if(!nombre)
        return NULL;

    elemento_t* nuevo_elemento = calloc(1, sizeof(elemento_t));
    if(!nuevo_elemento)
        return NULL;

    nuevo_elemento->nombre = nombre; // strcpy(nombre, nuevo_elemento->nombre);
    nuevo_elemento->funcion = funcion;
    nuevo_elemento->extra1 = extra1;
    nuevo_elemento->extra2 = extra2;

    return nuevo_elemento;
}

int agregar_elemento(pagina_t* pagina, elemento_t* elemento)
{
    if(!pagina || !elemento)
        return -1;

    pagina->elementos = realloc(pagina->elementos, sizeof(elemento_t)*(pagina->cantidad_elementos+1));
    if(!pagina->elementos)
        return -1;


    pagina->elementos[pagina->cantidad_elementos] = elemento;
    pagina->cantidad_elementos++;

    return 0;
}

pagina_t* crear_pagina(char* nombre)
{
    if(!nombre)
        return NULL;

    pagina_t* nueva_pagina = malloc(sizeof(pagina_t));
    if(!nueva_pagina)
        return NULL;

    nueva_pagina->elementos = malloc(sizeof(elemento_t*));
    if(!nueva_pagina->elementos)
    {
        free(nueva_pagina);
        return NULL;
    }

    nueva_pagina->nombre = nombre;
    nueva_pagina->cantidad_elementos = 0;

    return nueva_pagina;
}

void mostrar_pagina_actual(interfaz_t* interfaz)
{
    if(!interfaz)
        return;

    system("clear");
    pagina_t* pagina = interfaz->pagina_actual;

    printf("-- %s --\n\n", pagina->nombre);
    //printf("Cantidad de elementos: %ld\n", pagina->cantidad_elementos);
    for(size_t i = 0; i < pagina->cantidad_elementos; i++)
        printf("%ld. %s\n", i+1, pagina->elementos[i]->nombre);

    printf("\nexit para salir\n");
}

interfaz_t* crear_interfaz()
{
    interfaz_t* nueva_interfaz = calloc(1, sizeof(interfaz_t));
    if(!nueva_interfaz)
        return NULL;

    return nueva_interfaz;
}

int agregar_pagina(interfaz_t* interfaz, pagina_t* pagina)
{
    interfaz->paginas = realloc(interfaz->paginas, sizeof(pagina_t)*(interfaz->cantidad_paginas +1));
    if(!interfaz->paginas)
        return -1;

    if(interfaz->cantidad_paginas == 0)
    {
        interfaz->pagina_inicio = pagina;
        interfaz->pagina_actual = pagina; 
    }    

    interfaz->paginas[interfaz->cantidad_paginas] = pagina;
    interfaz->cantidad_paginas++;

    return 0;
}

void cambiar_pagina(void* interfaz, void* nombre_pagina)
{
    interfaz_t* interfaz_aux = (interfaz_t*)interfaz;
    
    size_t i = 0;
    while (i < interfaz_aux->cantidad_paginas)
    {
        if (strcmp(interfaz_aux->paginas[i]->nombre, (char*)nombre_pagina) == 0)
        {
            ((interfaz_t*)interfaz)->pagina_actual = interfaz_aux->paginas[i];
            return;
        }
        i++;
    }

    printf("Pagina no encontrada!\n");
    return;
}

void evaluar_input(interfaz_t* interfaz, char input[32])
{
    if(!interfaz)
    {
        printf("Error al evaluar el input!\n");
        return;
    }

    int input_int = input[0] - '0';
    
    // AGREGAR UN IF PARA CHEQUEAR QUE EL USUARIO
    // INGRESE UNA OPCION VALIDA. SI SE HACE EL 
    // PIOLA PONIENDO CUALQUIER COSA F.
    if(input_int < 1 || input_int > interfaz->pagina_actual->cantidad_elementos)
    {
        printf("Input invalido\n");
        return;
    }

    elemento_t* elemento = interfaz->pagina_actual->elementos[input_int-1];
    if(elemento->funcion != NULL)
        elemento->funcion(interfaz, elemento->extra2);
    
    return;
} 