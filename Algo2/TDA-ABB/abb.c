#include "abb.h"
#include <stdio.h>

/*
 * Recibe un nodo y verifica si tiene hijos, devuelve true
 * si tiene por lo menos uno, false caso contrario.
 */
bool nodo_sin_hijos(nodo_abb_t* nodo)
{
    if (!nodo)
        return false;

    if (nodo->derecha == NULL && nodo->izquierda == NULL)
        return true;
    
    return false;
}

/*
 * Recibe un arbol y un nodo, devuelve true si el 
 * elemento perteneciente al nodo es el mismo 
 * que se encuentra en la raiz del arbol
 */
bool es_nodo_raiz(abb_t* arbol, nodo_abb_t* nodo)
{
    if (!arbol || arbol_vacio(arbol))
        return false;

    if (arbol->comparador(arbol->nodo_raiz->elemento, nodo->elemento) == 0)
        return true;

    return false;
}

/*
 * Busca el nodo que tenga en uno de sus hijos al elemento buscado
 * y devuelve el puntero a dicho nodo, si no lo encuentra devuelve
 * NULL
 */
nodo_abb_t* nodo_padre(abb_t* arbol, void* elemento)
{
    if (arbol_vacio(arbol) || arbol->comparador(arbol->nodo_raiz->elemento, elemento) == 0)
        return NULL;

    nodo_abb_t* nodo_actual = arbol->nodo_raiz;
    bool nodo_encontrado = false;
    while(!nodo_encontrado)
    {
        if (nodo_actual->derecha != NULL && arbol->comparador(nodo_actual->derecha->elemento, elemento) == 0)
            return nodo_actual;
        else if (nodo_actual->izquierda != NULL && arbol->comparador(nodo_actual->izquierda->elemento, elemento) == 0)
            return nodo_actual;
        else
        {
            int comparador = arbol->comparador(nodo_actual->elemento, elemento);
            if (comparador > 0)
                nodo_actual = nodo_actual->izquierda;
            else
                nodo_actual = nodo_actual->derecha;
        }

        if (nodo_actual == NULL)
            return NULL;
    }   

    return NULL;
}

/*
 * Recibe un nodo con solo un hijo y devuelve 
 * el puntero a el.
*/
nodo_abb_t* nodo_hijo_unico(nodo_abb_t* nodo)
{
    if (!nodo)
        return NULL;

    if (nodo->derecha != NULL)
        return nodo->derecha;
    
    return nodo->izquierda;
}

/*
 * Recibe un nodo y busca a partir de el cual es el
 * subnodo con mayor elemento y lo devuelve.
 */
nodo_abb_t* nodo_mayor_hijo(nodo_abb_t* hijo_izquierda)
{
    if(!hijo_izquierda)
        return NULL;

    nodo_abb_t* nodo_mayor = hijo_izquierda;
    while(nodo_mayor->derecha != NULL)
        nodo_mayor = nodo_mayor->derecha;

    return nodo_mayor;
}

/*
 * Recibe un nodo y devuelve true si solo tiene un hijo
 * caso contrario devuelve false
 */
bool tiene_solo_un_hijo(nodo_abb_t* nodo)
{
    if(!nodo)
        return false;

    if (nodo->derecha == NULL || nodo->izquierda == NULL)
        return true;
    
    return false;
}

/*
 * Recibe el comparador para evaluar elementos, el nodo padre y un elemento
 * perteneciente al nodo hijo evaluado. Si el comparador dice que el hijo
 * derecho de nodo_anterior posee el mismo elemento que el recibido como
 * argumento devuelve true. Caso contrario devolvera false
 */
bool es_hijo_derecho(int (*comparador)(void*, void*), nodo_abb_t* nodo_anterior, void* elemento)
{
    if (!comparador || !nodo_anterior || !nodo_anterior->derecha)
        return false;

    if (comparador(nodo_anterior->derecha->elemento, elemento) == 0)
        return true;

    return false;
}

/*
 * Recibe un arbol y un nodo perteneciente a el creando un
 * nuevo arbol con el comparador y destructor del original
 * pero la raiz sera el nodo_hijo recibido. Devuelve el puntero
 * al arbol creado.
 */
abb_t* sub_arbol_crear(abb_t* arbol, nodo_abb_t* nodo_hijo)
{
    if(!arbol || !nodo_hijo)
        return NULL;

    abb_t* sub_arbol = arbol_crear(arbol->comparador, arbol->destructor);
    sub_arbol->nodo_raiz = nodo_hijo;
    return sub_arbol;
}

abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){
    if (!comparador)
        return NULL;
    
    abb_t* nuevo_arbol = calloc(1, sizeof(abb_t));
    if (!nuevo_arbol)
        return NULL;
    
    nuevo_arbol->comparador = comparador;
    nuevo_arbol->destructor = destructor;

    return nuevo_arbol;
}

int arbol_insertar(abb_t* arbol, void* elemento){
    if(!arbol)
        return -1;
    
    nodo_abb_t* nuevo_nodo = calloc(1, sizeof(nodo_abb_t));
    if(!nuevo_nodo)
        return -1;
    nuevo_nodo->elemento = elemento;
    nuevo_nodo->derecha = NULL;
    nuevo_nodo->izquierda = NULL;

    if (arbol_vacio(arbol))
        arbol->nodo_raiz = nuevo_nodo;
    else
    {
        nodo_abb_t* nodo_actual = arbol->nodo_raiz;
        
        bool posicion_encontrada = false;
        while(!posicion_encontrada)
        {
            int evaluacion_elemento = arbol->comparador(nodo_actual->elemento, nuevo_nodo->elemento);
            if (evaluacion_elemento >= 0)
            {
                if (!nodo_actual->izquierda)
                {
                    nodo_actual->izquierda = nuevo_nodo;
                    posicion_encontrada = true;
                }
                else
                    nodo_actual = nodo_actual->izquierda;
            }
            else
            {
                if (!nodo_actual->derecha)
                {
                    nodo_actual->derecha = nuevo_nodo;
                    posicion_encontrada = true;
                }
                else
                    nodo_actual = nodo_actual->derecha;
            }
        }
    }

    return 0;   
}

int arbol_borrar(abb_t* arbol, void* elemento){
    if (!arbol || arbol_vacio(arbol))
        return -1;

    // recorro el arbol buscando el elemento
    nodo_abb_t* nodo_actual = arbol->nodo_raiz;

    bool nodo_encontrado = false;
    while(!nodo_encontrado)
    {
        int evaluacion_elemento = arbol->comparador(nodo_actual->elemento, elemento);
        if(evaluacion_elemento == 0)
        {
            if (nodo_sin_hijos(nodo_actual))
            {
                nodo_abb_t* nodo_borrar = nodo_actual;
                nodo_abb_t* nodo_anterior = nodo_padre(arbol, nodo_actual->elemento);
                if (nodo_anterior == NULL) // borrar raiz
                {
                    if (arbol->destructor != NULL)
                        arbol->destructor(arbol->nodo_raiz->elemento);
                    arbol->nodo_raiz = NULL;
                    free(nodo_borrar);
                    return 0;
                }

                if (es_hijo_derecho(arbol->comparador, nodo_anterior, nodo_actual->elemento))
                    nodo_anterior->derecha = NULL;
                else
                    nodo_anterior->izquierda = NULL;

                if (arbol->destructor != NULL)
                    arbol->destructor(nodo_borrar->elemento);
                free(nodo_borrar);
            }

            else if (tiene_solo_un_hijo(nodo_actual))
            {
                nodo_abb_t* nodo_borrar = nodo_actual;
                nodo_abb_t* nodo_siguiente = nodo_hijo_unico(nodo_actual);
                nodo_abb_t* nodo_anterior = nodo_padre(arbol, nodo_actual->elemento);

                if (nodo_anterior == NULL) // borrar raiz
                {
                    if (arbol->destructor != NULL)
                        arbol->destructor(arbol->nodo_raiz->elemento);

                    if (arbol->nodo_raiz->izquierda != NULL)
                    {
                        arbol->nodo_raiz = arbol->nodo_raiz->izquierda;
                    }
                    else
                    {
                        arbol->nodo_raiz = arbol->nodo_raiz->derecha;
                    }
                    free(nodo_borrar);
                    return 0;
                }


                if (es_hijo_derecho(arbol->comparador, nodo_anterior, nodo_actual->elemento))
                    nodo_anterior->derecha = nodo_siguiente;
                else
                    nodo_anterior->izquierda = nodo_siguiente;
                
                if (arbol->destructor != NULL)
                    arbol->destructor(nodo_borrar->elemento);
                free(nodo_borrar);
            }  

            else // Caso dos hijos
            {
                nodo_abb_t* nodo_heredero = nodo_mayor_hijo(nodo_actual->izquierda);
                nodo_abb_t* nodo_borrar = nodo_heredero;
                nodo_abb_t* nodo_heredero_anterior = nodo_padre(arbol, nodo_heredero->elemento);

                if (arbol->comparador(nodo_heredero_anterior->elemento, nodo_actual->elemento) == 0) 
                {
                    nodo_heredero_anterior->izquierda = nodo_heredero->izquierda;
                }
                else
                {
                    if (nodo_heredero->izquierda != NULL)
                        nodo_heredero_anterior->derecha = nodo_heredero->izquierda;
                    else 
                        nodo_heredero_anterior->derecha = NULL;
                }

                if (arbol->destructor != NULL)
                    arbol->destructor(nodo_actual->elemento);

                nodo_actual->elemento = nodo_heredero->elemento;

                free(nodo_borrar);
            }
            
            nodo_encontrado = true;
        }

        else if (evaluacion_elemento > 0)
            nodo_actual = nodo_actual->izquierda;
        else
            nodo_actual = nodo_actual->derecha;

        if (nodo_actual == NULL)
            return -1;
    }

    return 0;
}

void* arbol_buscar(abb_t* arbol, void* elemento){
    if (!arbol || arbol_vacio(arbol))
        return NULL;

    void* elemento_encontrado = NULL;

    int evaluacion_elemento = arbol->comparador(arbol->nodo_raiz->elemento, elemento);
    if (evaluacion_elemento == 0)
        elemento_encontrado = arbol->nodo_raiz->elemento;

    else if (evaluacion_elemento > 0)
    {
        if (arbol->nodo_raiz->izquierda != NULL)
        {
            abb_t* sub_arbol_izquierdo = sub_arbol_crear(arbol, arbol->nodo_raiz->izquierda);
            elemento_encontrado = arbol_buscar(sub_arbol_izquierdo, elemento);
            free(sub_arbol_izquierdo);
        }
        else
            return NULL;
    }

    else //evaluacion_elemento < 0
    {
        if (arbol->nodo_raiz->derecha != NULL)
        {
            abb_t* sub_arbol_derecho = sub_arbol_crear(arbol, arbol->nodo_raiz->derecha);
            elemento_encontrado = arbol_buscar(sub_arbol_derecho, elemento);
            free(sub_arbol_derecho);
        }
        else
            return NULL;
    }
    
    return elemento_encontrado;
}

void* arbol_raiz(abb_t* arbol){
    if(arbol_vacio(arbol))
        return NULL;

    return arbol->nodo_raiz->elemento;
}

bool arbol_vacio(abb_t* arbol){
    if(!arbol || !arbol->nodo_raiz)
        return true;
    
    return false;
}

/*
 * Recibe la cantidad de asignados acutal de un array
 * y el tamaño maximo que puede almacenar. Devuelve
 * true si estos son iguales, caso contrario devolvera
 * false
 */
bool array_lleno(size_t cantidad_asignados, size_t tamanio_array)
{
    return (cantidad_asignados == tamanio_array);
}

/*
 * Recibe un array con la posicion en la que se le debe asignar
 * el elemento y lo ubica en ese lugar
 */
void array_add(void** array, void* elemento, size_t* posicion_ultimo)
{
    if(!array)
        return;

    array[*posicion_ultimo] = elemento;
    (*posicion_ultimo)++;  
}

/*
 * Funcion recursiva, recorre el arbol inorden y va agregando los elementos
 * iterados al array recibido, tambien incrementa la cantidad de iterados
 * cada vez que se agrega al array.
 */
void recorrido_inorden(abb_t* arbol, void** array, size_t tamanio_array, size_t* cantidad_iterados)
{
    if(!arbol || arbol_vacio(arbol) || !array || tamanio_array == 0 || *cantidad_iterados == tamanio_array)
        return;

    if (arbol->nodo_raiz->izquierda != NULL)
    {
        abb_t* sub_arbol_izquierdo = sub_arbol_crear(arbol, arbol->nodo_raiz->izquierda);
        recorrido_inorden(sub_arbol_izquierdo, array, tamanio_array, cantidad_iterados);
        free(sub_arbol_izquierdo);
    }

    if (array_lleno(*cantidad_iterados, tamanio_array))
        return;

    array_add(array, arbol->nodo_raiz->elemento, cantidad_iterados);

    if (array_lleno(*cantidad_iterados, tamanio_array))
        return;

    if (arbol->nodo_raiz->derecha != NULL)
    {
        abb_t* sub_arbol_derecho = sub_arbol_crear(arbol, arbol->nodo_raiz->derecha);
        recorrido_inorden(sub_arbol_derecho, array, tamanio_array, cantidad_iterados);
        free(sub_arbol_derecho);
    }

    return;
}

size_t arbol_recorrido_inorden(abb_t* arbol, void** array, size_t tamanio_array){
    size_t cantidad_iterados = 0;
    recorrido_inorden(arbol, array, tamanio_array, &cantidad_iterados);
    return cantidad_iterados;
}

/*
 * Funcion recursiva, recorre el arbol preorden y va agregando los elementos
 * iterados al array recibido, tambien incrementa la cantidad de iterados
 * cada vez que se agrega al array.
 */
void recorrido_preorden(abb_t* arbol, void** array, size_t tamanio_array, size_t* cantidad_iterados)
{
    if(!arbol || arbol_vacio(arbol) || !array || tamanio_array == 0 || *cantidad_iterados == tamanio_array)
        return;

    array_add(array, arbol->nodo_raiz->elemento, cantidad_iterados);

    if (array_lleno(*cantidad_iterados, tamanio_array))
        return;

    if (arbol->nodo_raiz->izquierda != NULL)
    {
        abb_t* sub_arbol_izquierdo = sub_arbol_crear(arbol, arbol->nodo_raiz->izquierda);
        recorrido_preorden(sub_arbol_izquierdo, array, tamanio_array, cantidad_iterados);
        free(sub_arbol_izquierdo);
    }

    if (array_lleno(*cantidad_iterados, tamanio_array))
        return;

    if (arbol->nodo_raiz->derecha != NULL)
    {
        abb_t* sub_arbol_derecho = sub_arbol_crear(arbol, arbol->nodo_raiz->derecha);
        recorrido_preorden(sub_arbol_derecho, array, tamanio_array, cantidad_iterados);
        free(sub_arbol_derecho);
    }

    return;
}

size_t arbol_recorrido_preorden(abb_t* arbol, void** array, size_t tamanio_array){
    size_t cantidad_iterados = 0;
    recorrido_preorden(arbol, array, tamanio_array, &cantidad_iterados);
    return cantidad_iterados;
}

/*
 * Funcion recursiva, recorre el arbol postorden y va agregando los elementos
 * iterados al array recibido, tambien incrementa la cantidad de iterados
 * cada vez que se agrega al array.
 */
void recorrido_postorden(abb_t* arbol, void** array, size_t tamanio_array, size_t* cantidad_iterados)
{
    if(!arbol || arbol_vacio(arbol) || !array || tamanio_array == 0 || *cantidad_iterados == tamanio_array)
        return;

    if (arbol->nodo_raiz->izquierda != NULL)
    {
        abb_t* sub_arbol_izquierdo = sub_arbol_crear(arbol, arbol->nodo_raiz->izquierda);
        recorrido_postorden(sub_arbol_izquierdo, array, tamanio_array, cantidad_iterados);
        free(sub_arbol_izquierdo);
    }

    if (array_lleno(*cantidad_iterados, tamanio_array))
        return;

    if (arbol->nodo_raiz->derecha != NULL)
    {
        abb_t* sub_arbol_derecho = sub_arbol_crear(arbol, arbol->nodo_raiz->derecha);
        recorrido_postorden(sub_arbol_derecho, array, tamanio_array, cantidad_iterados);
        free(sub_arbol_derecho);
    }

    if (array_lleno(*cantidad_iterados, tamanio_array))
        return;

    array_add(array, arbol->nodo_raiz->elemento, cantidad_iterados);
    
    return;
}

size_t arbol_recorrido_postorden(abb_t* arbol, void** array, size_t tamanio_array){
    size_t cantidad_iterados = 0;
    recorrido_postorden(arbol, array, tamanio_array, &cantidad_iterados);
    return cantidad_iterados;
}

void arbol_destruir(abb_t* arbol){
    if (!arbol)
        return;

    if (arbol_vacio(arbol))
    {
        free(arbol);
        return;
    }

    if (arbol->nodo_raiz->izquierda != NULL)
    {
        abb_t* sub_arbol_izquierdo = arbol_crear(arbol->comparador, arbol->destructor);
        sub_arbol_izquierdo->nodo_raiz = arbol->nodo_raiz->izquierda;
        arbol_destruir(sub_arbol_izquierdo);
    }
    
    if (arbol->nodo_raiz->derecha != NULL)
    {
        abb_t* sub_arbol_derecho = arbol_crear(arbol->comparador, arbol->destructor);
        sub_arbol_derecho->nodo_raiz = arbol->nodo_raiz->derecha;
        arbol_destruir(sub_arbol_derecho);
    }

    if (arbol->destructor != NULL)
        arbol->destructor(arbol->nodo_raiz->elemento);
    free(arbol->nodo_raiz);

    free(arbol);
    return;
}

bool recorrido_valido(int recorrido)
{
    if (recorrido == ABB_RECORRER_INORDEN ||
    recorrido == ABB_RECORRER_PREORDEN ||
    recorrido == ABB_RECORRER_POSTORDEN)
        return true;
    
    return false;
}

/*
 * Funcion recursiva, recorre el arbol inorden hasta que la funcion pasada 
 * como argumento devuelva true o se itere completamente el arbol. Devuelve
 * la cantidad de elementos por los que se itera. 
 */
size_t recorrido_inorden_funcion(abb_t* arbol, bool (*funcion)(void*, void*), void* extra, bool* condicion_elemento)
{
    if (!arbol || arbol_vacio(arbol) || !funcion || (*condicion_elemento))
        return 0;
    
    size_t cantidad_iterados = 0;

    if (arbol->nodo_raiz->izquierda != NULL)
    {
        abb_t* sub_arbol_izquierdo = sub_arbol_crear(arbol, arbol->nodo_raiz->izquierda);
        cantidad_iterados += recorrido_inorden_funcion(sub_arbol_izquierdo, funcion, extra, condicion_elemento);
        free(sub_arbol_izquierdo);
        if(*condicion_elemento)
            return cantidad_iterados;
    }

    cantidad_iterados++;
    bool evaluacion_elemento = funcion(arbol->nodo_raiz->elemento, extra);
    if (evaluacion_elemento)
    {
        *condicion_elemento = true;
        return cantidad_iterados;
    }


    if (arbol->nodo_raiz->derecha != NULL)
    {
        abb_t* sub_arbol_derecho = sub_arbol_crear(arbol, arbol->nodo_raiz->derecha);
        cantidad_iterados += recorrido_inorden_funcion(sub_arbol_derecho, funcion, extra, condicion_elemento);
        free(sub_arbol_derecho);
    }

    return cantidad_iterados;
}

/*
 * Funcion recursiva, recorre el arbol preorden hasta que la funcion pasada 
 * como argumento devuelva true o se itere completamente el arbol. Devuelve
 * la cantidad de elementos por los que se itera. 
 */
size_t recorrido_preorden_funcion(abb_t* arbol, bool (*funcion)(void*, void*), void* extra, bool* condicion_elemento)
{
    if (!arbol || arbol_vacio(arbol) || !funcion || (*condicion_elemento))
        return 0;
    
    size_t cantidad_iterados = 0;

    bool evaluacion_elemento = funcion(arbol->nodo_raiz->elemento, extra);
    if (evaluacion_elemento)
        *condicion_elemento = true;

    cantidad_iterados++;

    if (arbol->nodo_raiz->izquierda != NULL && !(*condicion_elemento))
    {
        abb_t* sub_arbol_izquierdo = sub_arbol_crear(arbol, arbol->nodo_raiz->izquierda);
        cantidad_iterados += recorrido_preorden_funcion(sub_arbol_izquierdo, funcion, extra, condicion_elemento);
        free(sub_arbol_izquierdo);
    }

    if (arbol->nodo_raiz->derecha != NULL && !(*condicion_elemento))
    {
        abb_t* sub_arbol_derecho = sub_arbol_crear(arbol, arbol->nodo_raiz->derecha);
        cantidad_iterados += recorrido_preorden_funcion(sub_arbol_derecho, funcion, extra, condicion_elemento);
        free(sub_arbol_derecho);
    }

    return cantidad_iterados;
}

/*
 * Funcion recursiva, recorre el arbol postorden hasta que la funcion pasada 
 * como argumento devuelva true o se itere completamente el arbol. Devuelve
 * la cantidad de elementos por los que se itera. 
 */
size_t recorrido_postorden_funcion(abb_t* arbol, bool (*funcion)(void*, void*), void* extra, bool* condicion_elemento)
{
    if (!arbol || arbol_vacio(arbol) || !funcion || (*condicion_elemento))
        return 0;
    
    size_t cantidad_iterados = 0;

    if (arbol->nodo_raiz->izquierda != NULL && !(*condicion_elemento))
    {
        abb_t* sub_arbol_izquierdo = sub_arbol_crear(arbol, arbol->nodo_raiz->izquierda);
        cantidad_iterados += recorrido_postorden_funcion(sub_arbol_izquierdo, funcion, extra, condicion_elemento);
        free(sub_arbol_izquierdo);
    }

    if (arbol->nodo_raiz->derecha != NULL && !(*condicion_elemento))
    {
        abb_t* sub_arbol_derecho = sub_arbol_crear(arbol, arbol->nodo_raiz->derecha);
        cantidad_iterados += recorrido_postorden_funcion(sub_arbol_derecho, funcion, extra, condicion_elemento);
        free(sub_arbol_derecho);
    }

    if (*condicion_elemento)
        return cantidad_iterados;

    bool evaluacion_elemento = funcion(arbol->nodo_raiz->elemento, extra);
    if (evaluacion_elemento)
        *condicion_elemento = true;

    cantidad_iterados++;

    return cantidad_iterados;
}

size_t abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra){
    if (!arbol || arbol_vacio(arbol) || !recorrido_valido(recorrido) || !funcion)
        return 0;

    bool condicion_elemento = false;

    if (recorrido == ABB_RECORRER_INORDEN)
        return recorrido_inorden_funcion(arbol, funcion, extra, &condicion_elemento);

    else if (recorrido == ABB_RECORRER_PREORDEN)
        return recorrido_preorden_funcion(arbol, funcion, extra, &condicion_elemento);

    return recorrido_postorden_funcion(arbol, funcion, extra, &condicion_elemento);
}
