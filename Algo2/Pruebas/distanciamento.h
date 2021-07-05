#ifndef __DISTANCIAMENTO_H_
#define __DISTANCIAMENTO_H_

#define MAX_FILAS 5
#define MAX_COLUMNAS 6
#define ENEMIGO 'E'
#define VACIO '-'

int distanciar_formacion(char formacion[MAX_FILAS][MAX_COLUMNAS], int* tope_filas, int* tope_columnas); 

#endif // __DISTANCIAMENTO_H_