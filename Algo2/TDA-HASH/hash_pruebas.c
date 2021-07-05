#include "hash.h"
#include <stdio.h>
#include "pa2mm.h"
#include <string.h>

// DESTRUCTORES
void destructor_int(void* numero)
{
  if(!numero)
    return;

  free(numero);
}
//-------------------

// PRUEBAS CREAR HASH
void pruebas_tabla_hash_vacia()
{
  pa2m_nuevo_grupo("Pruebas tabla hash vacia");

  hash_t* tabla_hash = hash_crear(NULL, 25);
  pa2m_afirmar(tabla_hash != NULL, "Puedo crear una tabla hash");
  pa2m_afirmar(hash_cantidad(tabla_hash) == 0, "La cantidad de asignados iniciales es 0");

  char* string = "AlgoritmosMendez";
  int numero = 2;
  void* elemento = &numero;
  pa2m_afirmar(hash_insertar(tabla_hash, string, elemento) == 0,"Puedo insertar un elemento");
  pa2m_afirmar(hash_cantidad(tabla_hash) == 1, "La tabla ahora tiene 1 elemento");
  
  char* otro_string = "TablaHash";
  int otro_numero = 4;
  void* otro_elemento = &otro_numero;
  pa2m_afirmar(hash_insertar(tabla_hash, otro_string, otro_elemento) == 0,"Puedo insertar otro elemento");
  pa2m_afirmar(hash_cantidad(tabla_hash) == 2, "La tabla ahora tiene 2 elementos");

  hash_destruir(tabla_hash);
}
//-------------------

// PRUEBAS BUSQUEDA Y CONTIENE
void buscar_arbol_nulo()
{
  pa2m_afirmar(hash_obtener(NULL, NULL) == NULL, "No puedo buscar elementos en un hash nulo");
}

void buscar_arbol_vacio()
{
  hash_t* tabla_hash = hash_crear(NULL, 3);
  pa2m_afirmar(!hash_contiene(tabla_hash, "AlgoritmosMendez"), "El arbol no contiene la clave buscada en un hash vacio");
  pa2m_afirmar(hash_obtener(tabla_hash,"AlgoritmosMendez") == NULL, "No puedo buscar elementos en un hash vacio");
  hash_destruir(tabla_hash);
}

void buscar_arbol_existente()
{
  hash_t* tabla_hash = hash_crear(NULL, 3);
  char* string = "AlgoritmosMendez";
  int numero = 2;
  hash_insertar(tabla_hash, string, &numero);
  pa2m_afirmar(hash_contiene(tabla_hash, string), "La tabla hash contiene un elemento con la clave almacenada");
  pa2m_afirmar(*(int*)hash_obtener(tabla_hash, string) == numero, "Puedo encontrar un elemento perteneciente a la tabla hash");

  hash_destruir(tabla_hash);
}

void buscar_arbol_inexistente()
{
  hash_t* tabla_hash = hash_crear(NULL, 3);
  char* string = "AlgoritmosMendez";
  int numero = 2;
  hash_insertar(tabla_hash, string, &numero);
  pa2m_afirmar(!hash_contiene(tabla_hash, "Messirve"), "La tabla hash no contiene un elemento con una clave no almacenada");
  pa2m_afirmar(hash_obtener(tabla_hash, "Messirve") == NULL, "No puedo encontrar un elemento ajeno a la tabla hash");

  hash_destruir(tabla_hash);

}

void buscar_arbol_inexistente_post_borrado()
{
  hash_t* tabla_hash = hash_crear(NULL, 3);
  char* string = "AlgoritmosMendez";
  int numero = 2;
  hash_insertar(tabla_hash, string, &numero);
  hash_quitar(tabla_hash, string);
  pa2m_afirmar(!hash_contiene(tabla_hash, string), "Luego de borrar un elemento, la clave con la que se almaceno ya no contiene nada");
  pa2m_afirmar(hash_obtener(tabla_hash, string) == NULL, "Luego de borrar un elemento ya no lo puedo encontrar en la tabla hash");
  hash_insertar(tabla_hash, string, &numero);
  pa2m_afirmar(*(int*)hash_obtener(tabla_hash, string) == numero, "Luego de insertar el elemento previamente borrado lo puedo encontrar en la tabla hash");

  hash_destruir(tabla_hash);
}

void pruebas_buscar()
{
  pa2m_nuevo_grupo("Pruebas busqueda");
  buscar_arbol_nulo();
  buscar_arbol_vacio();
  buscar_arbol_existente();
  buscar_arbol_inexistente();
  buscar_arbol_inexistente_post_borrado();
}
//-------------------

// PRUEBAS EXPANDIR
void prueba_expandir_consistencia()
{
  hash_t* tabla_hash = hash_crear(destructor_int, 3);

  char* string1 = "String1";
  int* uno = malloc(sizeof(int)); 
  *uno = 1;
  char* string2 = "String2";
  int* dos = malloc(sizeof(int));
  *dos = 2;
  char* string3 = "String3";
  int* tres = malloc(sizeof(int)); 
  *tres = 3;

  hash_insertar(tabla_hash, string1, uno);
  hash_insertar(tabla_hash, string2, dos);
  hash_insertar(tabla_hash, string3, tres);

  pa2m_afirmar(hash_cantidad(tabla_hash) == 3, "Expando la tabla hash y la cantidad de asignados es la correcta");
  pa2m_afirmar(*(int*)hash_obtener(tabla_hash, string1) == *uno &&
  *(int*)hash_obtener(tabla_hash, string2) == *dos &&
  *(int*)hash_obtener(tabla_hash, string3) == *tres,
  "Se mantuvieron los elementos previos");

  char* string4 = "String4";
  int* cuatro = malloc(sizeof(int));
  *cuatro = 4;

  pa2m_afirmar(hash_insertar(tabla_hash, string4, cuatro) == 0, "Puedo insertar nuevos elementos en la tabla expandida");
  pa2m_afirmar(*(int*)hash_obtener(tabla_hash, string4) == *cuatro, "Puedo encontrar el elemento agregado");

  hash_destruir(tabla_hash);
}

void prueba_borro_agrego_expando_no_encuentro_borrado()
{
  hash_t* tabla_hash = hash_crear(destructor_int, 3);

  char* string1 = "String1";
  int* uno = malloc(sizeof(int)); 
  *uno = 1;
  char* string2 = "String2";
  int* dos = malloc(sizeof(int));
  *dos = 2;
  char* string3 = "String3";
  int* tres = malloc(sizeof(int)); 
  *tres = 3;
  char* string4 = "String4";
  int* cuatro = malloc(sizeof(int));
  *cuatro = 4;

  hash_insertar(tabla_hash, string1, uno);
  hash_insertar(tabla_hash, string2, dos);
  hash_quitar(tabla_hash, string1);
  hash_insertar(tabla_hash, string3, tres);
  hash_insertar(tabla_hash, string4, cuatro);

  pa2m_afirmar(hash_obtener(tabla_hash, string1) == NULL, "No puedo encontrar el elemento eliminado previa expansion");


  hash_destruir(tabla_hash);
}

void pruebas_expandir()
{
  pa2m_nuevo_grupo("Pruebas expandir");
  prueba_expandir_consistencia();
  prueba_borro_agrego_expando_no_encuentro_borrado();
}
//-------------------


int main(){
  pruebas_tabla_hash_vacia();
  pruebas_buscar();
  //prueba_quitar();
  pruebas_expandir();
  

  //prueba_iterador();


  return pa2m_mostrar_reporte();
}
