#include <stdio.h>
#include "estadisticas.h"

int main() {
  estadisticas_t estadisticas;

  cargar_estadisticas(&estadisticas);
  int humor_char = humor(estadisticas);
  printf("El humor de Char es %i", humor_char);

  return 0;
}
