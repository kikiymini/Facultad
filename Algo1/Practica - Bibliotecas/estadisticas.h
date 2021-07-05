// estadisticas.h
// - Firmas, definiciones de structs, constantes, etc...

#ifndef __ESTADISTICAS_H__
#define __ESTADISTICAS_H__

typedef struct estadisticas {
  int dia_mes;
  int segundos_vertical;
  int cantidad_agua;
  int cantidad_chistes;
} estadisticas_t;

/*
 * PRE: -
 * POST: el struct estadisticas va a estar inicializado validamente.
 */
void cargar_estadisticas(estadisticas_t* estadisticas);

int humor(estadisticas_t estadisticas);

#endif
