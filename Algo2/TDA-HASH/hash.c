#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hash.h"

#define FACTOR_CARGA_LIMITE 0.75

typedef struct par{
  char* clave;
  void* elemento;
  bool flag_borrado; // indica si previamente almaceno un elemento
}par_t;

struct hash{
  size_t tam_tabla;
  size_t asignados;
  par_t** tabla;
  hash_destruir_dato_t destructor;
};

/*
 * Recibe un string y devuelve un puntero a 
 * una copia suya reservada en memoria dinamica
 */
char* string_cpy(const char* string)
{
    size_t tam_string = strlen(string);
    char* string_copiado = malloc(sizeof(char)*(tam_string+1));
    if(!string_copiado)
        return NULL;

    for(size_t i = 0; i < tam_string; i++)
    {
        string_copiado[i] = string[i];
    }
    string_copiado[tam_string] = '\0';

    return string_copiado;
}

/*
 *
 */
size_t clave_hash(const char* clave)
{
    size_t valor = 518;

    size_t pos = 0;
    while(clave[pos])
    {
        valor += (clave[pos]*(pos+1) + clave[pos]);
        pos++;
    }

    return valor;
}

/*
 *
 */
bool misma_clave(const char* clave1, const char* clave2)
{
  if(!clave1 || !clave2)
    return false;

  if (strcmp(clave1, clave2) == 0)
    return true;
  
  return false;
}

hash_t* hash_crear(hash_destruir_dato_t destruir_elemento, size_t capacidad_inicial){
  hash_t* nuevo_hash = calloc(1, sizeof(hash_t));
  if(!nuevo_hash)
    return NULL; 
  
  if (capacidad_inicial < 3)
    capacidad_inicial = 3;
  
  nuevo_hash->tam_tabla = capacidad_inicial;
  nuevo_hash->destructor = destruir_elemento;

  nuevo_hash->tabla = calloc(capacidad_inicial, sizeof(par_t*));
  if (!nuevo_hash->tabla)
  {
    free(nuevo_hash);
    return NULL;
  }

  return nuevo_hash;
}

/*
 *
 */
bool posicion_ocupada(par_t* par)
{
  if(!par)
    return false;

  if(!par->clave)
    return false;

  return true;
}

/*
 *
 */
int hash_expandir(hash_t* hash, size_t nuevo_tam)
{
  if(!hash)
    return -1;

  par_t** tabla_vieja = hash->tabla;
  size_t tam_viejo = hash->tam_tabla;

  hash->tabla = calloc(nuevo_tam, sizeof(par_t*));
  if(!hash->tabla)
    return -1;
  hash->tam_tabla = nuevo_tam;
  hash->asignados = 0;

  for(size_t i = 0; i < tam_viejo; i++)
  {
    if(posicion_ocupada(tabla_vieja[i]))
      hash_insertar(hash, tabla_vieja[i]->clave, tabla_vieja[i]->elemento);

    free(tabla_vieja[i]->clave);
    free(tabla_vieja[i]);
  }
  free(tabla_vieja);

  return 0;
}

/*
 *
 */
par_t* crear_par(const char* clave, void* elemento)
{
  par_t* nuevo_par = malloc(sizeof(par_t));
  if(!nuevo_par)
    return NULL;

  nuevo_par->clave = string_cpy(clave);
  if(!nuevo_par->clave)
  {
    free(nuevo_par);
    return NULL;
  }

  nuevo_par->elemento = elemento;
  nuevo_par->flag_borrado = false;

  return nuevo_par;
}

/*
 * 
 */
void destruir_contenido_par(par_t* par, hash_destruir_dato_t destructor_elemento)
{
  if(!par)
    return;

  if(destructor_elemento != NULL)
    destructor_elemento(par->elemento);
  free(par->clave);
}

int hash_insertar(hash_t* hash, const char* clave, void* elemento){
  if(!hash || !clave)
    return -1;

  size_t posicion = clave_hash(clave) % hash->tam_tabla;
  while(posicion_ocupada(hash->tabla[posicion]))
  {
    if (misma_clave(clave, hash->tabla[posicion]->clave))
    {
      if(hash->destructor != NULL)
        hash->destructor(hash->tabla[posicion]->elemento);
      hash->tabla[posicion]->elemento = elemento;
      return 0;
    }

    posicion++;

    if (posicion == hash->tam_tabla)
      posicion = 0;
  }

  par_t* nuevo_par = crear_par(clave, elemento);
  if(!nuevo_par)
    return -1;

  if(hash->tabla[posicion] && hash->tabla[posicion]->flag_borrado)                   
    free(hash->tabla[posicion]);            

  hash->tabla[posicion] = nuevo_par;
  hash->asignados++;

  float factor_carga = hash->asignados/hash->tam_tabla;
  if (factor_carga >= FACTOR_CARGA_LIMITE)
  {
    size_t nuevo_tamanio = hash->tam_tabla * 2; 
    return hash_expandir(hash, nuevo_tamanio);
  }

  return 0;
}

/*
 * para iterar sobre los pares con elementos y los que fueron borrados
 */
bool espacio_vacio(par_t* par)
{
  if(!par)
    return true;

  if(par->flag_borrado)
    return false;

  return false;
}

int hash_quitar(hash_t* hash, const char* clave){
  if(!hash || !clave)
    return -1;

  size_t posicion = clave_hash(clave) % hash->tam_tabla;
  while(!espacio_vacio(hash->tabla[posicion]))  
  {
    if (misma_clave(clave, hash->tabla[posicion]->clave))
    {
      char* clave_borrar = hash->tabla[posicion]->clave;
      void* elemento_borrar = hash->tabla[posicion]->elemento;

      hash->tabla[posicion]->elemento = NULL;
      hash->tabla[posicion]->clave = NULL;
      hash->tabla[posicion]->flag_borrado = true;

      hash->asignados--;

      free(clave_borrar);
      if(hash->destructor != NULL)
        hash->destructor(elemento_borrar);

      return 0;
    }

    posicion++;

    if(posicion == hash->tam_tabla)
      posicion = 0;
  }

  return -1; // Si llego a aca no encontro el elemento
}

void* hash_obtener(hash_t* hash, const char* clave){
  if(!hash || !clave)
    return NULL;

  size_t posicion = clave_hash(clave) % hash->tam_tabla;
  while(!espacio_vacio(hash->tabla[posicion]))  
  {
    if(misma_clave(clave, hash->tabla[posicion]->clave))
      return hash->tabla[posicion]->elemento;

    posicion++;
    
    if (posicion == hash->tam_tabla)
      posicion = 0;
  }

  return NULL; 
}

size_t hash_cantidad(hash_t* hash){
  if(!hash)
    return 0;

  return hash->asignados;
}

bool hash_contiene(hash_t* hash, const char* clave){
  if(!hash || hash->asignados == 0 ||!clave)
    return false;

  for(size_t i = 0; i < hash->tam_tabla; i++)
    if(hash->tabla[i] != NULL &&
      hash->tabla[i]->clave != NULL &&
      strcmp(hash->tabla[i]->clave, clave) == 0)
      return true;

  return false;
}

void hash_destruir(hash_t* hash){
  if(!hash)
    return;

  for(size_t i = 0; i < hash->tam_tabla; i++)
  {
    if(posicion_ocupada(hash->tabla[i]))
      destruir_contenido_par(hash->tabla[i], hash->destructor);
      
    free(hash->tabla[i]);
  }
  free(hash->tabla);
  free(hash);
}

size_t hash_con_cada_clave(hash_t* hash, bool (*funcion)(hash_t* hash, const char* clave, void* aux), void* aux){
  if(!hash || !funcion)
    return 0;

  size_t cantidad_iterados = 0;
  size_t claves_por_recorrer = hash->asignados;

  size_t i = 0;
  while(i < hash->tam_tabla && cantidad_iterados < claves_por_recorrer)
  {
    if(hash->tabla[i] != NULL && hash->tabla[i]->clave != NULL)
    {
      cantidad_iterados++;
      claves_por_recorrer--;
      if(funcion(hash, hash->tabla[i]->clave, aux))
        return cantidad_iterados;
    }

    i++;
  }

  return cantidad_iterados;
}

