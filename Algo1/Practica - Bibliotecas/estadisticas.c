#include "estadisticas.h"
#include <stdio.h>

void imprimir_saludo() {
  printf("Buen día!\n");
}

void cargar_estadisticas(estadisticas_t* estadisticas) {
  imprimir_saludo();
  printf("Ingrese día del mes\n");
  scanf("%i", &(estadisticas->dia_mes));
  printf("Ingrese segundos que duró en vertical\n");
  scanf("%i", &(estadisticas->segundos_vertical));
  printf("Ingrese cantidad de agua en litros que tomó\n");
  scanf("%i", &(estadisticas->cantidad_agua));
  printf("Ingrese cantidad de chistes\n");
  scanf("%i", &(estadisticas->cantidad_chistes));
}

int humor(estadisticas_t estadisticas) {
  return (estadisticas.cantidad_agua + estadisticas.cantidad_chistes) * estadisticas.segundos_vertical;
}
