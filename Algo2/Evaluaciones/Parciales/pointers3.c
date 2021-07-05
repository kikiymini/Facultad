#include <stdio.h>
#include <stdlib.h>

#define CANT_ARRAY_NUM 9
#define CANT_AZULES 3

typedef struct cosa_azul_t{
 struct cosa_azul_t* siguiente;
 int* ptr_numero;
}cosa_azul_t;

typedef struct cosa_naranja{
  cosa_azul_t** punteros;
  int numero;
}cosa_naranja_t;

void borrar_azules(cosa_azul_t* azul)
{
 if(!azul)
  return;
  
  if(azul->siguiente != NULL)
    borrar_azules(azul->siguiente);
  
  free(azul);
}

int main()
{
  int* array_numeros = calloc(CANT_ARRAY_NUM, sizeof(int));
  
  cosa_naranja_t naranja;
  naranja.numero = 3;
  naranja.punteros = calloc(CANT_AZULES, sizeof(void*));
  // chequeo
  
  size_t cant0 = 3, cant1 = 1, cant2= 2;
  int cantidades[CANT_AZULES] = {cant0, cant1, cant2};
  
  for(size_t i = 0; i < CANT_AZULES; i++)
  {
    naranja.punteros[i] = calloc(1, sizeof(cosa_azul_t));
    // chequeo
    cosa_azul_t* ptr_aux = naranja.punteros[i];
    
    for(size_t j = 0; j < cantidades[i]; j++)
    {
      ptr_aux->ptr_numero = &array_numeros[(j*3)+i];
      if(j+1 < cantidades[i])
      {
        ptr_aux->siguiente = malloc(sizeof(cosa_azul_t));
        // chequeo
      }
      else
        ptr_aux->siguiente = NULL;
      ptr_aux = ptr_aux->siguiente;
    } 
  }
  
  for(int i = 0; i < CANT_AZULES; i++)
    borrar_azules(naranja.punteros[i]);
  free(naranja.punteros);
  free(array_numeros);
  
  return 0;
}