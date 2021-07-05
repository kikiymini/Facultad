#include "abb.h"
#include <stdio.h>
#include "pa2mm.h"
#include "string.h"

// COMPARADORES, DESTRUCTORES y BOOLEANOS
int comparador_char(void* chr1,void* chr2)
{
  if (!chr1 || !chr2)
  {
    return -1;
  }

  return (*(char*)chr1 - *(char*)chr2);
}

int comparador_int(void* int1, void* int2)
{  
  if (!int1 || !int2)
  {
    return -1;
  }

  return(*(int*)int1 - *(int*)int2);
}

void destructor_int(void* elemento_int)
{
  if (elemento_int != NULL)
    free(elemento_int);
}

bool iterador_simple(void* elemento, void* extra)
{
  return false;
}

bool iterador_buscar_numero(void* numero_iterado, void* buscado)
{
  if (numero_iterado == buscado)
    return true;
  
  return false;
}

//-------------------

// PRUEBAS INSERCION
void pruebas_insercion()
{
  pa2m_nuevo_grupo("Pruebas insercion");
  abb_t* arbol = arbol_crear(comparador_char, NULL);
  char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e';

  pa2m_afirmar(arbol_insertar(arbol, &b) == 0, "Puedo insertar un elemento en una lista vacia");
  pa2m_afirmar(*(char*)arbol_raiz(arbol) == 'b', "El elemento 'b' se inserto en la raiz");

  pa2m_afirmar(arbol_insertar(arbol, &a) == 0, "Puedo insertar un elemento en una lista con un elemento previo");
  pa2m_afirmar(*(char*)arbol->nodo_raiz->izquierda->elemento == 'a', "El elemento 'a' se inserto debajo a la izquierda de 'b'");
  
  pa2m_afirmar(arbol_insertar(arbol, &c) == 0, "Puedo insertar un elemento en una lista con un dos elementos previos");
  pa2m_afirmar(*(char*)arbol->nodo_raiz->derecha->elemento == 'c', "El elemento 'c' se inserto debajo a la derecha de 'b'");

  pa2m_afirmar(arbol_insertar(arbol, &d) == 0, "Puedo insertar un elemento en una lista con un tres elementos previos");
  pa2m_afirmar(*(char*)arbol->nodo_raiz->derecha->derecha->elemento == 'd', "El elemento 'd' se inserto debajo a la derecha de 'c'");

  pa2m_afirmar(arbol_borrar(arbol, &e) == -1, "No puedo borrar un elemento que no existe en el arbol");

  arbol_insertar(arbol, &e);
  pa2m_afirmar(*(char*)arbol->nodo_raiz->derecha->derecha->derecha->elemento == 'e', "El elemento 'e' se inserto debajo a la derecha de 'd'");

  pa2m_afirmar(arbol_borrar(arbol, &e) == 0, "Puedo borrar un elemento sin hijos");
  pa2m_afirmar(arbol->nodo_raiz->derecha->derecha->derecha == NULL, "El elemento 'd' ya no tiene hijos");

  pa2m_afirmar(arbol_borrar(arbol, &c) == 0, "Puedo borrar un elemento con un hijo");
  
  pa2m_afirmar(*(char*)arbol->nodo_raiz->derecha->elemento == 'd', "El 'd' reemplazo a 'c'");

  arbol_destruir(arbol);
}
//-------------------

// PRUEBAS BUSQUEDA
void dado_un_arbol_inexistente_cuando_busco_un_elemento_en_el_no_puedo()
{
  pa2m_afirmar(arbol_buscar(NULL, NULL) == NULL, "No puedo buscar elementos en un arbol null");
}

void dado_un_arbol_vacio_cuando_busco_un_elemento_en_el_no_puedo()
{
  abb_t* arbol = arbol_crear(comparador_int, destructor_int);
  int* uno = malloc(sizeof(int));
  *uno = 1;

  pa2m_afirmar(arbol_buscar(arbol, uno) == NULL, "No puedo buscar elementos en un arbol vacio");

  free(uno);
  arbol_destruir(arbol);
}

void dado_un_arbol_con_elementos_cuando_busco_un_elemento_perteneciente_a_el_lo_encuentro()
{
  abb_t* arbol = arbol_crear(comparador_int, destructor_int);
  int* uno = malloc(sizeof(int));
  *uno = 1;
  int* dos = malloc(sizeof(int));
  *dos = 2;
  int* tres = malloc(sizeof(int));
  *tres = 3;
  int* cuatro = malloc(sizeof(int));
  *cuatro = 4;
  int* cinco = malloc(sizeof(int));
  *cinco = 5;
  int* seis = malloc(sizeof(int));
  *seis = 6;
  int* siete = malloc(sizeof(int));
  *siete = 7;

  arbol_insertar(arbol, uno);
  arbol_insertar(arbol, dos);
  arbol_insertar(arbol, tres);
  arbol_insertar(arbol, cuatro);
  arbol_insertar(arbol, cinco);
  arbol_insertar(arbol, seis);
  arbol_insertar(arbol, siete);

  pa2m_afirmar(arbol->comparador(arbol_buscar(arbol, cinco), cinco) == 0, "Busco y encuentro un elemento perteneciente al arbol");

  arbol_destruir(arbol);
}

void dado_un_arbol_con_elementos_cuando_busco_un_elemento_ajeno_a_el_no_lo_encuentro()
{
  abb_t* arbol = arbol_crear(comparador_int, destructor_int);
  int* uno = malloc(sizeof(int));
  *uno = 1;
  int* dos = malloc(sizeof(int));
  *dos = 2;
  int* tres = malloc(sizeof(int));
  *tres = 3;
  int* cuatro = malloc(sizeof(int));
  *cuatro = 4;
  int* cinco = malloc(sizeof(int));
  *cinco = 5;
  int* seis = malloc(sizeof(int));
  *seis = 6;
  int* siete = malloc(sizeof(int));
  *siete = 7;
  int* ocho = malloc(sizeof(int));
  *ocho = 8;
  
  arbol_insertar(arbol, uno);
  arbol_insertar(arbol, dos);
  arbol_insertar(arbol, tres);
  arbol_insertar(arbol, cuatro);
  arbol_insertar(arbol, cinco);
  arbol_insertar(arbol, seis);
  arbol_insertar(arbol, siete);

  pa2m_afirmar(arbol_buscar(arbol, ocho) == NULL, "No puedo encontrar un elemento ajeno al arbol");

  free(ocho);
  arbol_destruir(arbol);
}

void pruebas_busqueda()
{
  pa2m_nuevo_grupo("Pruebas busqueda");
  dado_un_arbol_inexistente_cuando_busco_un_elemento_en_el_no_puedo();
  dado_un_arbol_vacio_cuando_busco_un_elemento_en_el_no_puedo();
  dado_un_arbol_con_elementos_cuando_busco_un_elemento_perteneciente_a_el_lo_encuentro();
  dado_un_arbol_con_elementos_cuando_busco_un_elemento_ajeno_a_el_no_lo_encuentro();
}
//-------------------

// PRUEBAS BORRADO
void dado_un_arbol_inexistente_cuando_quiero_borrar_un_elemento_no_puedo()
{
  pa2m_afirmar(arbol_borrar(NULL, NULL) == -1, "No puedo borrar en un arbol inexistente");
}

void dado_un_arbol_vacio_cuando_quiero_borrar_un_elemento_no_puedo()
{
  abb_t* arbol = arbol_crear(comparador_char, NULL);
  pa2m_afirmar(arbol_borrar(arbol, NULL) == -1, "No puedo borrar en un arbol vacio");

  arbol_destruir(arbol);
}

void dado_un_arbol_con_un_nodo_sin_hijos_cuando_intento_borrarlo_puedo_hacerlo()
{
  abb_t* arbol = arbol_crear(comparador_char, NULL);
  char a = 'a', b = 'b', c = 'c';

  arbol_insertar(arbol, &b);
  arbol_insertar(arbol, &a);
  arbol_insertar(arbol, &c);

  pa2m_afirmar(arbol_borrar(arbol, &c) == 0, "Puedo borrar un elemento sin hijos");
  pa2m_afirmar(arbol->nodo_raiz->derecha == NULL, "La raiz ya no tiene hijo derecho");

  arbol_destruir(arbol);
}

void dado_un_arbol_con_un_nodo_con_solo_un_hijo_izquierdo_cuando_lo_borro_este_toma_su_lugar()
{
  abb_t* arbol = arbol_crear(comparador_char, NULL);
  char a = 'a', b = 'b', c = 'c', d = 'd';

  arbol_insertar(arbol, &b);
  arbol_insertar(arbol, &a);
  arbol_insertar(arbol, &c);
  arbol_insertar(arbol, &d);

  pa2m_afirmar(arbol_borrar(arbol, &c) == 0, "Puedo borrar un elemento con solo un hijo derecho");
  pa2m_afirmar(*(char*)arbol->nodo_raiz->derecha->elemento == 'd', "El hijo derecho de la raiz paso a ser el hijo derecho del nodo borrado");

  arbol_destruir(arbol);
}

void dado_un_arbol_con_un_nodo_con_solo_un_hijo_derecho_cuando_lo_borro_este_toma_su_lugar()
{
  abb_t* arbol = arbol_crear(comparador_char, NULL);
  char a = 'a', b = 'b', c = 'c', d = 'd';

  arbol_insertar(arbol, &b);
  arbol_insertar(arbol, &a);
  arbol_insertar(arbol, &d);
  arbol_insertar(arbol, &c);

  pa2m_afirmar(arbol_borrar(arbol, &d) == 0, "Puedo borrar un elemento con un hijo izquierdo");
  pa2m_afirmar(*(char*)arbol->nodo_raiz->derecha->elemento == 'c', "El hijo derecho de la raiz paso a ser el hijo izquierdo del nodo borrado");

  arbol_destruir(arbol);
}

void dado_un_arbol_con_un_nodo_con_dos_hijos_cuando_lo_borro_su_hijo_izquierdo_toma_el_lugar()
{
  abb_t* arbol = arbol_crear(comparador_char, NULL);
  char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e';

  arbol_insertar(arbol, &b);
  arbol_insertar(arbol, &a);
  arbol_insertar(arbol, &d);
  arbol_insertar(arbol, &c);
  arbol_insertar(arbol, &e);

  pa2m_afirmar(arbol_borrar(arbol, &d) == 0, "Puedo borrar un elemento con dos hijos");
  pa2m_afirmar(*(char*)arbol->nodo_raiz->derecha->elemento == 'c', "El hijo derecho del nodo borrado tomo su lugar");
  pa2m_afirmar(*(char*)arbol->nodo_raiz->derecha->derecha->elemento == 'e', "Luego del cambio, el hijo derecho del borrado sigue siendo el mismo");

  arbol_destruir(arbol);
}

void dado_un_arbol_con_un_nodo_con_dos_hijos_que_tienen_sus_propios_hijos_al_borrar_el_nodo_su_mayor_sub_nodo_izquierdo_toma_su_lugar()
{
  abb_t* arbol = arbol_crear(comparador_char, NULL);
  char a = 'a', b = 'b', c = 'c', d = 'd', f = 'f', g = 'g';

  arbol_insertar(arbol, &b);
  arbol_insertar(arbol, &a);
  arbol_insertar(arbol, &f);
  arbol_insertar(arbol, &g);
  arbol_insertar(arbol, &c);
  arbol_insertar(arbol, &d);

  pa2m_afirmar(arbol_borrar(arbol, &f) == 0, "Puedo borrar un elemento con dos hijos con hijos propios");
  pa2m_afirmar(*(char*)arbol->nodo_raiz->derecha->elemento == 'd', "El mayor elemento a su derecha tomo su posicion");
  pa2m_afirmar(*(char*)arbol->nodo_raiz->derecha->derecha->elemento == 'g', "Luego del cambio, el hijo derecho del borrado sigue siendo el mismo");
  pa2m_afirmar(*(char*)arbol->nodo_raiz->derecha->izquierda->elemento == 'c', "Luego del cambio, el hijo izquierdo del borrado sigue siendo el mismo");
  pa2m_afirmar(arbol->nodo_raiz->derecha->izquierda->derecha == NULL, "Luego del cambio, el elemento que tomo su lugar ya no existe en su posicion original");

  arbol_destruir(arbol);
}

void dado_un_arbol_solo_con_raiz_cuando_la_borro_al_insertar_un_elemento_este_pasa_a_ser_la_nueva_raiz()
{
  abb_t* arbol = arbol_crear(comparador_char, NULL);
  char a = 'a', b = 'b';

  arbol_insertar(arbol, &a);
  pa2m_afirmar(arbol_borrar(arbol, &a) == 0, "Puedo borrar de un arbol con un solo elemento");
  pa2m_afirmar(arbol->nodo_raiz == NULL, "La raiz del arbol se volvio NULL");

  pa2m_afirmar(arbol_insertar(arbol, &b) == 0, "Puedo volver a insertar elementos");
  pa2m_afirmar(*(char*)arbol->nodo_raiz->elemento == 'b', "La nueva raiz del arbol es el elemento insertado");

  arbol_destruir(arbol);
}

void dado_un_arbol_con_dos_elementos_al_borrar_la_raiz_el_nodo_restante_pasa_a_ser_la_nueva_raiz()
{
  abb_t* arbol = arbol_crear(comparador_char, NULL);
  char a = 'a', b = 'b';

  arbol_insertar(arbol, &a);
  arbol_insertar(arbol, &b);

  pa2m_afirmar(arbol_borrar(arbol, &a) == 0, "Puedo borrar de un arbol con solo dos elementos");
  pa2m_afirmar(*(char*)arbol->nodo_raiz->elemento == 'b', "La raiz del arbol se volvio su unico hijo");

  arbol_destruir(arbol);
}

void dado_un_arbol_con_tres_elementos_al_borrar_la_raiz_el_hijo_izquierdo_de_la_raiz_para_a_ser_la_nueva_raiz()
{
  abb_t* arbol = arbol_crear(comparador_char, NULL);
  char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e', f = 'f', g = 'g';

  arbol_insertar(arbol, &f);
  arbol_insertar(arbol, &g);
  arbol_insertar(arbol, &c);
  arbol_insertar(arbol, &e);
  arbol_insertar(arbol, &d);
  arbol_insertar(arbol, &b);
  arbol_insertar(arbol, &a);

  pa2m_afirmar(arbol_borrar(arbol, &f) == 0, "Puedo borrar la raiz de un arbol con varios elementos");
  pa2m_afirmar(*(char*)arbol->nodo_raiz->elemento == 'e', "La raiz del arbol se volvio su mayor heredero izquierdo");
  pa2m_afirmar(*(char*)arbol->nodo_raiz->izquierda->elemento == 'c' &&
              *(char*)arbol->nodo_raiz->izquierda->derecha->elemento == 'd' &&
              *(char*)arbol->nodo_raiz->izquierda->izquierda->elemento == 'b' &&
              *(char*)arbol->nodo_raiz->derecha->elemento == 'g',
              "Los demas elementos mantuvieron su orden");

  arbol_destruir(arbol);
}

void pruebas_borrado()
{
  pa2m_nuevo_grupo("Pruebas borrado");

  dado_un_arbol_inexistente_cuando_quiero_borrar_un_elemento_no_puedo();
  dado_un_arbol_vacio_cuando_quiero_borrar_un_elemento_no_puedo();
  dado_un_arbol_con_un_nodo_sin_hijos_cuando_intento_borrarlo_puedo_hacerlo();
  dado_un_arbol_con_un_nodo_con_solo_un_hijo_izquierdo_cuando_lo_borro_este_toma_su_lugar();
  dado_un_arbol_con_un_nodo_con_solo_un_hijo_derecho_cuando_lo_borro_este_toma_su_lugar();
  dado_un_arbol_con_un_nodo_con_dos_hijos_cuando_lo_borro_su_hijo_izquierdo_toma_el_lugar();
  dado_un_arbol_con_un_nodo_con_dos_hijos_que_tienen_sus_propios_hijos_al_borrar_el_nodo_su_mayor_sub_nodo_izquierdo_toma_su_lugar();
  dado_un_arbol_solo_con_raiz_cuando_la_borro_al_insertar_un_elemento_este_pasa_a_ser_la_nueva_raiz();
  dado_un_arbol_con_dos_elementos_al_borrar_la_raiz_el_nodo_restante_pasa_a_ser_la_nueva_raiz();
  dado_un_arbol_con_tres_elementos_al_borrar_la_raiz_el_hijo_izquierdo_de_la_raiz_para_a_ser_la_nueva_raiz();
}
//-------------------

// PRUEBAS RECORRIDOS
void dado_un_arbol_vacio_cuando_lo_quiero_recorrer_inorden_no_puedo()
{
  abb_t* arbol = arbol_crear(comparador_int, NULL);
  size_t tamanio_array = 7;
  void* array_numeros[tamanio_array]; 

  pa2m_afirmar(arbol_recorrido_inorden(arbol, array_numeros, tamanio_array) == 0, "No puedo recorrer un arbol vacio");

  arbol_destruir(arbol);
}

void dado_un_arbol_cuando_lo_quiero_recorrer_inorden_con_un_array_sin_espacio_no_puedo()
{
  abb_t* arbol = arbol_crear(comparador_int, NULL);
  size_t tamanio_array = 0;
  void* array_numeros[tamanio_array]; 

  pa2m_afirmar(arbol_recorrido_inorden(arbol, array_numeros, tamanio_array) == 0, "Recorrer un array vacio devuelve 0 iteraciones");

  arbol_destruir(arbol);
}

void dado_un_arbol_cuando_lo_recorro_inorden_con_un_array_con_el_espacio_justo_almaceno_todos_los_elementos()
{
  abb_t* arbol = arbol_crear(comparador_int, NULL);
  int uno = 1, dos = 2, tres = 3, cuatro = 4, cinco = 5, seis = 6, siete = 7;

  size_t tamanio_array = 7;
  void* array_numeros[tamanio_array];

  arbol_insertar(arbol, &cuatro);
  arbol_insertar(arbol, &dos);
  arbol_insertar(arbol, &seis);
  arbol_insertar(arbol, &uno);
  arbol_insertar(arbol, &tres);
  arbol_insertar(arbol, &cinco);
  arbol_insertar(arbol, &siete); 
  
  pa2m_afirmar(arbol_recorrido_inorden(arbol, array_numeros, tamanio_array) == tamanio_array, "Puedo recorrer un arbol inorden enteramente"); 
  pa2m_afirmar(*(int*)array_numeros[0] == 1 &&
              *(int*)array_numeros[1] == 2 &&
              *(int*)array_numeros[2] == 3 &&
              *(int*)array_numeros[3] == 4 &&
              *(int*)array_numeros[4] == 5 &&
              *(int*)array_numeros[5] == 6 &&
              *(int*)array_numeros[6] == 7
              ,"Los elementos se almacenaron correctamente en el array");

  arbol_destruir(arbol);
}

void dado_un_arbol_cuando_lo_recorro_inorden_con_un_array_con_espacio_insuficiente_almaceno_elementos_hasta_llenar_el_array()
{
  abb_t* arbol = arbol_crear(comparador_int, NULL);
  int uno = 1, dos = 2, tres = 3, cuatro = 4, cinco = 5, seis = 6, siete = 7;

  size_t tamanio_array = 5;
  void* array_numeros[tamanio_array];

  arbol_insertar(arbol, &cuatro);
  arbol_insertar(arbol, &dos);
  arbol_insertar(arbol, &seis);
  arbol_insertar(arbol, &uno);
  arbol_insertar(arbol, &tres);
  arbol_insertar(arbol, &cinco);
  arbol_insertar(arbol, &siete); 
  
  pa2m_afirmar(arbol_recorrido_inorden(arbol, array_numeros, tamanio_array) == tamanio_array, "Puedo recorrer un arbol inorden hasta llenar el array"); 
  pa2m_afirmar(*(int*)array_numeros[0] == 1 &&
              *(int*)array_numeros[1] == 2 &&
              *(int*)array_numeros[2] == 3 &&
              *(int*)array_numeros[3] == 4 &&
              *(int*)array_numeros[4] == 5
              ,"Los elementos se almacenaron correctamente en el array");

  arbol_destruir(arbol);
}

void dado_un_arbol_cuando_lo_recorro_inorden_con_un_array_con_espacio_excedente_almaceno_todos_los_elementos_sin_llenar_por_completo_el_array()
{
  abb_t* arbol = arbol_crear(comparador_int, NULL);
  int uno = 1, dos = 2, tres = 3, cuatro = 4, cinco = 5, seis = 6, siete = 7;

  size_t tamanio_array = 12;
  void* array_numeros[tamanio_array];

  arbol_insertar(arbol, &cuatro);
  arbol_insertar(arbol, &dos);
  arbol_insertar(arbol, &seis);
  arbol_insertar(arbol, &uno);
  arbol_insertar(arbol, &tres);
  arbol_insertar(arbol, &cinco);
  arbol_insertar(arbol, &siete); 
  
  pa2m_afirmar(arbol_recorrido_inorden(arbol, array_numeros, tamanio_array) == 7, "Puedo recorrer un arbol inorden con un array con espacio de sobra"); 
  pa2m_afirmar(*(int*)array_numeros[0] == 1 &&
              *(int*)array_numeros[1] == 2 &&
              *(int*)array_numeros[2] == 3 &&
              *(int*)array_numeros[3] == 4 &&
              *(int*)array_numeros[4] == 5 &&
              *(int*)array_numeros[5] == 6 &&
              *(int*)array_numeros[6] == 7
              ,"Los elementos se almacenaron correctamente en el array");

  arbol_destruir(arbol);
}

void dado_un_arbol_vacio_cuando_lo_quiero_recorrer_preorden_no_puedo()
{
  abb_t* arbol = arbol_crear(comparador_int, NULL);
  size_t tamanio_array = 7;
  void* array_numeros[tamanio_array]; 

  pa2m_afirmar(arbol_recorrido_preorden(arbol, array_numeros, tamanio_array) == 0, "No puedo recorrer un arbol vacio");

  arbol_destruir(arbol);
}

void dado_un_arbol_cuando_lo_quiero_recorrer_preorden_con_un_array_sin_espacio_no_puedo()
{
  abb_t* arbol = arbol_crear(comparador_int, NULL);
  size_t tamanio_array = 0;
  void* array_numeros[tamanio_array]; 

  pa2m_afirmar(arbol_recorrido_preorden(arbol, array_numeros, tamanio_array) == 0, "Recorrer un array vacio devuelve 0 iteraciones");

  arbol_destruir(arbol);
}

void dado_un_arbol_cuando_lo_recorro_preorden_con_un_array_con_el_espacio_justo_almaceno_todos_los_elementos()
{
  abb_t* arbol = arbol_crear(comparador_int, NULL);
  int uno = 1, dos = 2, tres = 3, cuatro = 4, cinco = 5, seis = 6, siete = 7;

  size_t tamanio_array = 7;
  void* array_numeros[tamanio_array];

  arbol_insertar(arbol, &cuatro);
  arbol_insertar(arbol, &dos);
  arbol_insertar(arbol, &seis);
  arbol_insertar(arbol, &uno);
  arbol_insertar(arbol, &tres);
  arbol_insertar(arbol, &cinco);
  arbol_insertar(arbol, &siete); 
  
  pa2m_afirmar(arbol_recorrido_preorden(arbol, array_numeros, tamanio_array) == tamanio_array, "Puedo recorrer un arbol preorden enteramente"); 
  pa2m_afirmar(*(int*)array_numeros[0] == 4 &&
              *(int*)array_numeros[1] == 2 &&
              *(int*)array_numeros[2] == 1 &&
              *(int*)array_numeros[3] == 3 &&
              *(int*)array_numeros[4] == 6 &&
              *(int*)array_numeros[5] == 5 &&
              *(int*)array_numeros[6] == 7
              ,"Los elementos se almacenaron correctamente en el array");

  arbol_destruir(arbol);
}

void dado_un_arbol_cuando_lo_recorro_preorden_con_un_array_con_espacio_insuficiente_almaceno_elementos_hasta_llenar_el_array()
{
  abb_t* arbol = arbol_crear(comparador_int, NULL);
  int uno = 1, dos = 2, tres = 3, cuatro = 4, cinco = 5, seis = 6, siete = 7;

  size_t tamanio_array = 5;
  void* array_numeros[tamanio_array];

  arbol_insertar(arbol, &cuatro);
  arbol_insertar(arbol, &dos);
  arbol_insertar(arbol, &seis);
  arbol_insertar(arbol, &uno);
  arbol_insertar(arbol, &tres);
  arbol_insertar(arbol, &cinco);
  arbol_insertar(arbol, &siete); 
  
  pa2m_afirmar(arbol_recorrido_preorden(arbol, array_numeros, tamanio_array) == tamanio_array, "Puedo recorrer un arbol preorden hasta llenar el array"); 
  pa2m_afirmar(*(int*)array_numeros[0] == 4 &&
              *(int*)array_numeros[1] == 2 &&
              *(int*)array_numeros[2] == 1 &&
              *(int*)array_numeros[3] == 3 &&
              *(int*)array_numeros[4] == 6
              ,"Los elementos se almacenaron correctamente en el array");

  arbol_destruir(arbol);
}

void dado_un_arbol_cuando_lo_recorro_preorden_con_un_array_con_espacio_excedente_almaceno_todos_los_elementos_sin_llenar_por_completo_el_array()
{
  abb_t* arbol = arbol_crear(comparador_int, NULL);
  int uno = 1, dos = 2, tres = 3, cuatro = 4, cinco = 5, seis = 6, siete = 7;

  size_t tamanio_array = 12;
  void* array_numeros[tamanio_array];

  arbol_insertar(arbol, &cuatro);
  arbol_insertar(arbol, &dos);
  arbol_insertar(arbol, &seis);
  arbol_insertar(arbol, &uno);
  arbol_insertar(arbol, &tres);
  arbol_insertar(arbol, &cinco);
  arbol_insertar(arbol, &siete); 
  
  pa2m_afirmar(arbol_recorrido_preorden(arbol, array_numeros, tamanio_array) == 7, "Puedo recorrer un arbol preorden con un array con espacio de sobra"); 
  pa2m_afirmar(*(int*)array_numeros[0] == 4 &&
              *(int*)array_numeros[1] == 2 &&
              *(int*)array_numeros[2] == 1 &&
              *(int*)array_numeros[3] == 3 &&
              *(int*)array_numeros[4] == 6 &&
              *(int*)array_numeros[5] == 5 &&
              *(int*)array_numeros[6] == 7
              ,"Los elementos se almacenaron correctamente en el array");

  arbol_destruir(arbol);
}

void dado_un_arbol_vacio_cuando_lo_quiero_recorrer_postorden_no_puedo()
{
  abb_t* arbol = arbol_crear(comparador_int, NULL);
  size_t tamanio_array = 7;
  void* array_numeros[tamanio_array]; 

  pa2m_afirmar(arbol_recorrido_postorden(arbol, array_numeros, tamanio_array) == 0, "No puedo recorrer un arbol vacio");

  arbol_destruir(arbol);
}

void dado_un_arbol_cuando_lo_quiero_recorrer_postorden_con_un_array_sin_espacio_no_puedo()
{
  abb_t* arbol = arbol_crear(comparador_int, NULL);
  size_t tamanio_array = 0;
  void* array_numeros[tamanio_array]; 

  pa2m_afirmar(arbol_recorrido_postorden(arbol, array_numeros, tamanio_array) == 0, "Recorrer un array vacio devuelve 0 iteraciones");

  arbol_destruir(arbol);
}

void dado_un_arbol_cuando_lo_recorro_postorden_con_un_array_con_el_espacio_justo_almaceno_todos_los_elementos()
{
  abb_t* arbol = arbol_crear(comparador_int, NULL);
  int uno = 1, dos = 2, tres = 3, cuatro = 4, cinco = 5, seis = 6, siete = 7;

  size_t tamanio_array = 7;
  void* array_numeros[tamanio_array];

  arbol_insertar(arbol, &cuatro);
  arbol_insertar(arbol, &dos);
  arbol_insertar(arbol, &seis);
  arbol_insertar(arbol, &uno);
  arbol_insertar(arbol, &tres);
  arbol_insertar(arbol, &cinco);
  arbol_insertar(arbol, &siete); 
  
  pa2m_afirmar(arbol_recorrido_postorden(arbol, array_numeros, tamanio_array) == tamanio_array, "Puedo recorrer un arbol postorden enteramente"); 
  pa2m_afirmar(*(int*)array_numeros[0] == 1 &&
              *(int*)array_numeros[1] == 3 &&
              *(int*)array_numeros[2] == 2 &&
              *(int*)array_numeros[3] == 5 &&
              *(int*)array_numeros[4] == 7 &&
              *(int*)array_numeros[5] == 6 &&
              *(int*)array_numeros[6] == 4
              ,"Los elementos se almacenaron correctamente en el array");

  arbol_destruir(arbol);
}

void dado_un_arbol_cuando_lo_recorro_postorden_con_un_array_con_espacio_insuficiente_almaceno_elementos_hasta_llenar_el_array()
{
  abb_t* arbol = arbol_crear(comparador_int, NULL);
  int uno = 1, dos = 2, tres = 3, cuatro = 4, cinco = 5, seis = 6, siete = 7;

  size_t tamanio_array = 5;
  void* array_numeros[tamanio_array];

  arbol_insertar(arbol, &cuatro);
  arbol_insertar(arbol, &dos);
  arbol_insertar(arbol, &seis);
  arbol_insertar(arbol, &uno);
  arbol_insertar(arbol, &tres);
  arbol_insertar(arbol, &cinco);
  arbol_insertar(arbol, &siete); 
  
  pa2m_afirmar(arbol_recorrido_postorden(arbol, array_numeros, tamanio_array) == tamanio_array, "Puedo recorrer un arbol postorden hasta llenar el array"); 
  pa2m_afirmar(*(int*)array_numeros[0] == 1 &&
              *(int*)array_numeros[1] == 3 &&
              *(int*)array_numeros[2] == 2 &&
              *(int*)array_numeros[3] == 5 &&
              *(int*)array_numeros[4] == 7
              ,"Los elementos se almacenaron correctamente en el array");

  arbol_destruir(arbol);
}

void dado_un_arbol_cuando_lo_recorro_postorden_con_un_array_con_espacio_excedente_almaceno_todos_los_elementos_sin_llenar_por_completo_el_array()
{
  abb_t* arbol = arbol_crear(comparador_int, NULL);
  int uno = 1, dos = 2, tres = 3, cuatro = 4, cinco = 5, seis = 6, siete = 7;

  size_t tamanio_array = 12;
  void* array_numeros[tamanio_array];

  arbol_insertar(arbol, &cuatro);
  arbol_insertar(arbol, &dos);
  arbol_insertar(arbol, &seis);
  arbol_insertar(arbol, &uno);
  arbol_insertar(arbol, &tres);
  arbol_insertar(arbol, &cinco);
  arbol_insertar(arbol, &siete); 
  
  pa2m_afirmar(arbol_recorrido_postorden(arbol, array_numeros, tamanio_array) == 7, "Puedo recorrer un arbol postorden con un array con espacio de sobra"); 
  pa2m_afirmar(*(int*)array_numeros[0] == 1 &&
              *(int*)array_numeros[1] == 3 &&
              *(int*)array_numeros[2] == 2 &&
              *(int*)array_numeros[3] == 5 &&
              *(int*)array_numeros[4] == 7 &&
              *(int*)array_numeros[5] == 6 &&
              *(int*)array_numeros[6] == 4
              ,"Los elementos se almacenaron correctamente en el array");

  arbol_destruir(arbol);
}

void pruebas_recorridos()
{
  pa2m_nuevo_grupo("Pruebas recorridos");

  dado_un_arbol_vacio_cuando_lo_quiero_recorrer_inorden_no_puedo();
  dado_un_arbol_cuando_lo_quiero_recorrer_inorden_con_un_array_sin_espacio_no_puedo();
  dado_un_arbol_cuando_lo_recorro_inorden_con_un_array_con_el_espacio_justo_almaceno_todos_los_elementos();
  dado_un_arbol_cuando_lo_recorro_inorden_con_un_array_con_espacio_insuficiente_almaceno_elementos_hasta_llenar_el_array();
  dado_un_arbol_cuando_lo_recorro_inorden_con_un_array_con_espacio_excedente_almaceno_todos_los_elementos_sin_llenar_por_completo_el_array();
  
  dado_un_arbol_vacio_cuando_lo_quiero_recorrer_preorden_no_puedo();
  dado_un_arbol_cuando_lo_quiero_recorrer_preorden_con_un_array_sin_espacio_no_puedo();
  dado_un_arbol_cuando_lo_recorro_preorden_con_un_array_con_el_espacio_justo_almaceno_todos_los_elementos();
  dado_un_arbol_cuando_lo_recorro_preorden_con_un_array_con_espacio_insuficiente_almaceno_elementos_hasta_llenar_el_array();
  dado_un_arbol_cuando_lo_recorro_preorden_con_un_array_con_espacio_excedente_almaceno_todos_los_elementos_sin_llenar_por_completo_el_array();

  dado_un_arbol_vacio_cuando_lo_quiero_recorrer_postorden_no_puedo();
  dado_un_arbol_cuando_lo_quiero_recorrer_postorden_con_un_array_sin_espacio_no_puedo();
  dado_un_arbol_cuando_lo_recorro_postorden_con_un_array_con_el_espacio_justo_almaceno_todos_los_elementos();
  dado_un_arbol_cuando_lo_recorro_postorden_con_un_array_con_espacio_insuficiente_almaceno_elementos_hasta_llenar_el_array();
  dado_un_arbol_cuando_lo_recorro_postorden_con_un_array_con_espacio_excedente_almaceno_todos_los_elementos_sin_llenar_por_completo_el_array();

}
//-------------------

// PRUEBAS ITERADOR
void dado_un_arbol_nulo_o_un_recorrido_invalido_no_puedo_recorrer()
{
  pa2m_afirmar(abb_con_cada_elemento(NULL, ABB_RECORRER_INORDEN, iterador_simple, NULL) == 0, "No puedo iterar un arbol NULL");
  
  abb_t* arbol = arbol_crear(comparador_int, NULL);
  int uno = 1;
  arbol_insertar(arbol, &uno);
  pa2m_afirmar(abb_con_cada_elemento(arbol, 9, iterador_simple, NULL) == 0, "No puedo iterar se el recorrido es invalido");
  pa2m_afirmar(abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, NULL, NULL) == 0, "No puedo iterar si la funcion es NULL");

  arbol_destruir(arbol);
}

void dado_un_arbol_cuando_recorro_inorden_recorre_hasta_que_la_funcion_devuelva_true_o_se_itere_el_arbol_completo()
{
  abb_t* arbol = arbol_crear(comparador_int, NULL);
  int uno = 1, dos = 2, tres = 3, cuatro = 4, cinco = 5, seis = 6, siete = 7;

  arbol_insertar(arbol, &cuatro);
  arbol_insertar(arbol, &dos);
  arbol_insertar(arbol, &seis);
  arbol_insertar(arbol, &uno);
  arbol_insertar(arbol, &tres);
  arbol_insertar(arbol, &cinco);
  arbol_insertar(arbol, &siete); 

  pa2m_afirmar(abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, iterador_simple, NULL) == 7, "El arbol se recorre inorden completamente");
  pa2m_afirmar(abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, iterador_buscar_numero, &cinco) == 5, "El arbol se recorre inorden hasta encontrar el elemento");

  arbol_destruir(arbol);
}

void dado_un_arbol_cuando_recorro_preorden_recorre_hasta_que_la_funcion_devuelva_true_o_se_itere_el_arbol_completo()
{
  abb_t* arbol = arbol_crear(comparador_int, NULL);
  int uno = 1, dos = 2, tres = 3, cuatro = 4, cinco = 5, seis = 6, siete = 7;

  arbol_insertar(arbol, &cuatro);
  arbol_insertar(arbol, &dos);
  arbol_insertar(arbol, &seis);
  arbol_insertar(arbol, &uno);
  arbol_insertar(arbol, &tres);
  arbol_insertar(arbol, &cinco);
  arbol_insertar(arbol, &siete); 

  pa2m_afirmar(abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, iterador_simple, NULL) == 7, "El arbol se recorre preorden completamente");
  pa2m_afirmar(abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, iterador_buscar_numero, &cinco) == 6, "El arbol se recorre preorden hasta encontrar el elemento");

  arbol_destruir(arbol);

}

void dado_un_arbol_cuando_recorro_postorden_recorre_hasta_que_la_funcion_devuelva_true_o_se_itere_el_arbol_completo()
{
  abb_t* arbol = arbol_crear(comparador_int, NULL);
  int uno = 1, dos = 2, tres = 3, cuatro = 4, cinco = 5, seis = 6, siete = 7;

  arbol_insertar(arbol, &cuatro);
  arbol_insertar(arbol, &dos);
  arbol_insertar(arbol, &seis);
  arbol_insertar(arbol, &uno);
  arbol_insertar(arbol, &tres);
  arbol_insertar(arbol, &cinco);
  arbol_insertar(arbol, &siete); 

  pa2m_afirmar(abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, iterador_simple, NULL) == 7, "El arbol se recorre postorden completamente");
  pa2m_afirmar(abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, iterador_buscar_numero, &cinco) == 4, "El arbol se recorre postorden hasta encontrar el elemento");

  arbol_destruir(arbol);

}

void pruebas_iterador()
{
  pa2m_nuevo_grupo("Pruebas iteradores");

  dado_un_arbol_nulo_o_un_recorrido_invalido_no_puedo_recorrer();
  dado_un_arbol_cuando_recorro_inorden_recorre_hasta_que_la_funcion_devuelva_true_o_se_itere_el_arbol_completo();
  dado_un_arbol_cuando_recorro_preorden_recorre_hasta_que_la_funcion_devuelva_true_o_se_itere_el_arbol_completo();
  dado_un_arbol_cuando_recorro_postorden_recorre_hasta_que_la_funcion_devuelva_true_o_se_itere_el_arbol_completo();
}
//-------------------

int main()
{
  pruebas_insercion();
  pruebas_busqueda();
  pruebas_borrado();
  pruebas_recorridos();  
  pruebas_iterador();

  return pa2m_mostrar_reporte();
}
