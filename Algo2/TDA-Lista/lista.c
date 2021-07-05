#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

lista_t* lista_crear(){ 
    lista_t* lista_nueva = calloc(1, sizeof(lista_t));
    if (!lista_nueva)
        return NULL;
    
    lista_nueva->nodo_inicio = NULL;
    lista_nueva->nodo_fin = NULL;
    lista_nueva->cantidad = 0;

    return lista_nueva;
}

int lista_insertar(lista_t* lista, void* elemento){
    if (!lista)
        return -1;

    nodo_t* nodo_nuevo = calloc(1, sizeof(nodo_t));
    if (!nodo_nuevo)
        return -1;
    nodo_nuevo->elemento = elemento;
    nodo_nuevo->siguiente = NULL;

    if(lista->cantidad == 0)
        lista->nodo_inicio = nodo_nuevo;
    else
        lista->nodo_fin->siguiente = nodo_nuevo;

    lista->nodo_fin = nodo_nuevo;
    lista->cantidad++;

    return 0;
}

int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){
    if(!lista)
        return -1;

    if (posicion >= lista->cantidad)
        lista_insertar(lista, elemento);
    else
    {
        lista_iterador_t* nuevo = lista_iterador_crear(lista);
        for(size_t i = 0; i < posicion; i++)
            lista_iterador_avanzar(nuevo);

        nodo_t* desplazado = calloc(1, sizeof(nodo_t));
        if (!desplazado)
            return -1;

        desplazado->elemento = nuevo->corriente->elemento;
        desplazado->siguiente = nuevo->corriente->siguiente;

        nuevo->corriente->elemento = elemento;
        nuevo->corriente->siguiente = desplazado;
        
        if (posicion == lista->cantidad -1)
            lista->nodo_fin = desplazado;

        else if (posicion == 0)
            lista->nodo_inicio = nuevo->corriente;

        lista->cantidad++;
        lista_iterador_destruir(nuevo);        
    }

    return 0;
}

int lista_borrar(lista_t* lista){
    if (!lista || lista->cantidad == 0)
        return -1;

    lista->cantidad--;
    lista_iterador_t* iterador_lista = lista_iterador_crear(lista);
    for(int i = 0; i < (int)lista->cantidad -1; i++)
        lista_iterador_avanzar(iterador_lista);

    free(lista->nodo_fin);

    if (!lista_vacia(lista))
    {
        iterador_lista->corriente->siguiente = NULL;
        lista->nodo_fin = iterador_lista->corriente;
        lista->nodo_fin->elemento = iterador_lista->corriente->elemento;
    }

    lista_iterador_destruir(iterador_lista);
    return 0;
}

int lista_borrar_de_posicion(lista_t* lista, size_t posicion){
    if(!lista || lista->cantidad == 0)
        return -1;
    
    if(posicion >= lista->cantidad)
        lista_borrar(lista);
    else if (posicion == 0)
    {
        nodo_t* nodo_inicio_viejo = lista->nodo_inicio;
        lista->nodo_inicio = lista->nodo_inicio->siguiente;
        free(nodo_inicio_viejo);
        lista->cantidad--;
    }
    else // elemento en el medio
    {
        lista_iterador_t* nodo_anterior = lista_iterador_crear(lista);
        if (!nodo_anterior)
            return -1;
        for (int i = 0; i < (int)posicion -1; i++)
            lista_iterador_avanzar(nodo_anterior);
        nodo_t* nodo_a_borrar = nodo_anterior->corriente->siguiente;
        nodo_anterior->corriente->siguiente = nodo_anterior->corriente->siguiente->siguiente;

        free(nodo_a_borrar);
        lista->cantidad--;
        lista_iterador_destruir(nodo_anterior);
    }

    return 0;
}

void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){
    if (!lista || posicion >= lista->cantidad)
        return NULL;

    lista_iterador_t* iterador = lista_iterador_crear(lista);
    if(!iterador)
        return NULL;
    for (size_t i = 0; i < posicion; i++)
        lista_iterador_avanzar(iterador);

    void* elemento = iterador->corriente->elemento;  
    lista_iterador_destruir(iterador);
    return elemento; 
}

void* lista_ultimo(lista_t* lista){
    if (!lista || lista_vacia(lista))
        return NULL;

    return lista->nodo_fin->elemento;
}

bool lista_vacia(lista_t* lista){
    if(!lista || lista->cantidad == 0)
        return true;

    return false;
}

size_t lista_elementos(lista_t* lista){
    if (!lista)
        return 0;

    return lista->cantidad;
}

int lista_apilar(lista_t* lista, void* elemento){
    return lista_insertar_en_posicion(lista, elemento, 0);
}

int lista_desapilar(lista_t* lista){
    return lista_borrar_de_posicion(lista, 0);;
}

void* lista_tope(lista_t* lista){
    if (!lista || lista_vacia(lista))
        return NULL;

    return lista->nodo_inicio->elemento;
}

int lista_encolar(lista_t* lista, void* elemento){
    return lista_insertar(lista, elemento);
}

int lista_desencolar(lista_t* lista){
    return lista_borrar_de_posicion(lista, 0);
}

void* lista_primero(lista_t* lista){
    if(!lista || lista_vacia(lista))
        return NULL;

    return lista->nodo_inicio->elemento;
}

void lista_destruir(lista_t* lista){
    if (!lista)
        return;

    while(!lista_vacia(lista))
        lista_borrar_de_posicion(lista, 0);

    free(lista);

    return;
}

lista_iterador_t* lista_iterador_crear(lista_t* lista){
    if(!lista)
        return NULL;
    
    lista_iterador_t* lista_iterador = calloc(1, sizeof(lista_iterador_t));
    if(!lista_iterador)
        return NULL;
    
    lista_iterador->lista = lista;
    lista_iterador->corriente = lista->nodo_inicio;

    return lista_iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){
    if(!iterador)
        return false;

    if(iterador->corriente == NULL || iterador->corriente->elemento == NULL)
        return false;

    return true;
}

bool lista_iterador_avanzar(lista_iterador_t* iterador){
    if(!iterador)
        return false;

    if (iterador->corriente == NULL)
    {            
        return false;
    }

    iterador->corriente = iterador->corriente->siguiente;
    if (iterador->corriente == NULL)
        return false;

    return true;
}

void* lista_iterador_elemento_actual(lista_iterador_t* iterador){
    if(!iterador || iterador->corriente == NULL)
        return NULL;

    if(iterador->corriente == NULL)
        return NULL;
    
    return iterador->corriente->elemento;
}

void lista_iterador_destruir(lista_iterador_t* iterador){
    if(!iterador) 
        return;
    
    free(iterador);
    return;
}

size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void*, void*), void *contexto){
    if(!lista || lista_vacia(lista) || !funcion)
        return 0;

    size_t cantidad_iterados = 1;
    lista_iterador_t* iterador = lista_iterador_crear(lista);
    if (!iterador)
        return 0;

    while(funcion(lista_iterador_elemento_actual(iterador), contexto))
    {
        cantidad_iterados++;
        lista_iterador_avanzar(iterador);
        if (iterador->corriente == NULL)
        {
            lista_iterador_destruir(iterador);
            return lista->cantidad; //recorrio toda la lista
        }
    }
    lista_iterador_destruir(iterador);
    return cantidad_iterados;
}

