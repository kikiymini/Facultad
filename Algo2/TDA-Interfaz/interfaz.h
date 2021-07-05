#ifndef __INTERFAZ_H__
#define __INTERFAZ_H__

#include <stdio.h>

// Funcion para cada elemento
typedef void (*ejecutar)(void*, void*);

typedef struct elemento {
    char* nombre;
    ejecutar funcion;
    void* extra1;
    void* extra2;
}elemento_t;

typedef struct pagina {
    char* nombre;
    elemento_t** elementos;
    size_t cantidad_elementos;
}pagina_t;

typedef struct intefaz {
    pagina_t* pagina_inicio;
    pagina_t* pagina_actual;
    pagina_t** paginas; // Se puede cambiar por un hash probablemente
    size_t cantidad_paginas;
}interfaz_t;

/*
 * Crea un elemento
 * extra1 y extra2 son parametros adicionales para la funcion recibida
 */
elemento_t* crear_elemento(char* nombre, ejecutar funcion, void* extra1, void* extra2);

/*
 * Agrega un elemento a la pagina recibida como argumento
 */
int agregar_elemento(pagina_t* pagina, elemento_t* elemento);

/*
 * Crea una pagina con los elementos creados por pantalla
 */
pagina_t* crear_pagina(char* nombre);

/*
 * Agrega una pagina a la interfaz
 */
int agregar_pagina(interfaz_t* interfaz, pagina_t* pagina);

/*
 * Imprime por pantalla la pagina actual
 */
void mostrar_pagina_actual(interfaz_t* interfaz);

/*
 * Reserva memoria para una interfaz
 */
interfaz_t* crear_interfaz();

/*
 * Libera toda la memoria reservada por la interfaz
 */
void destruir_interfaz(interfaz_t* interfaz);

/*
 * Evalua el input del usuario
 */
void evaluar_input(interfaz_t* interfaz, char input[32]);

/*
 *  cambia la pagina a la del nombre recibido
 */
void cambiar_pagina(void* interfaz, void* nombre_pagina);

// IMPLEMENTAR DESTRUCTORES

#endif /* __INTERFAZ_H__ */