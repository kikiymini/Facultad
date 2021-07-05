#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "detector_personajes.h"

// Constante de Sabores
const char DULCE = 'D';
const char SALADO = 'S';
const char AMARGO = 'A';

// Constante de Colores
const char AZUL = 'A';
const char AMARILLO = 'Y';
const char VERDE = 'V';
const char NEGRO = 'N';
const char BLANCO = 'B';
const char ROSA = 'R';

// Constante de Personajes
/*const char JOHNNY = 'J';
const char BELLOTA = 'S';
const char POLLITO = 'P'; 
const char BLUE = 'B'; 
const char PURO_HUESO = 'H';
const char CORAJE = 'C';*/

// Constantes de Alturas
const int ALTURA_JOHNNY = 180;
const int ALTURA_BELLOTA = 120;
const int ALTURA_POLLITO = 50;
const int ALTURA_BLUE = 140;
const int ALTURA_HUESO = 200;
const int ALTURA_CORAJE = 30;

/* Funcion de fecha de nacimiento
** Pre-condiciones: La existencia de una variable para que pueda cambiarse su valor.
** Post-condiciones: Le asigna a la variable puntaje_nacimiento
** un valor entre 1 y 20. */
void calculo_puntaje_nacimiento(int* fecha_nacimiento)
{
    printf("Año de nacimiento (entre 1988 y 2008): ");
    scanf(" %i", fecha_nacimiento);

    while (*fecha_nacimiento < 1988 || *fecha_nacimiento > 2008)
    {
        printf("\nAño incorrecto amigo, entre 1988 y 2008 tiene que ser: ");
        scanf(" %i", fecha_nacimiento);
    } 

    *fecha_nacimiento = (*fecha_nacimiento % 20) + 1;
}

/* Funcion de sabor
** Pre-condiciones: La existencia de una variable para que pueda cambiarse su valor.
** Post-condiciones: Le asigna a la variable puntaje_sabor un valor
** de 5, 15 o 20 dependiendo de la eleccion de sabor del usuario */
void calculo_puntaje_sabor(int* puntaje_sabor)
{
    char preferencia_sabor;
    printf("Preferencia de sabor:\nD para dulce.\nS para salado.\nA para amargo.\n");
    scanf(" %c", &preferencia_sabor);

    while (preferencia_sabor != DULCE && preferencia_sabor != SALADO && preferencia_sabor != AMARGO)
    {
        printf("\nEse sabor no existe o no le gusta a nadie, elegi uno de abajo:\nD para dulce.\nS para salado.\nA para amargo.\n");
        scanf(" %c", &preferencia_sabor);
    } 

    if (preferencia_sabor == SALADO) *puntaje_sabor = 5;
    else if (preferencia_sabor == DULCE) *puntaje_sabor = 15;
    else *puntaje_sabor = 20; // AMARGO
}

/* Funcion de talla de zapatos
** Pre-condiciones: La existencia de una variable para que pueda cambiarse su valor.
** Post-condiciones: Devuelve un entero entre 1 y 4 dependiendo 
** de la talla de zapatos introducida por el usuario. */
void valor_multiplicador_zapatos(int* multiplicador)
{
    int talla_zapatos = 0;
    printf("Talle de zapatos (0 si no usa o sino un numero entre 33 y 47): ");
    scanf(" %i", &talla_zapatos);

    while ((talla_zapatos != 0) && (talla_zapatos < 33 || talla_zapatos > 47))
    {
        printf("\nSi mis avanzados conocimientos matematicos no me fallan ese numero no cumple con lo que pido,\n");
        printf("Pone un numero entre 33 y 47 o 0 si no usa zapatos: ");
        scanf(" %i", &talla_zapatos);
    } 

    if (talla_zapatos == 1) *multiplicador = 1;
    else if (talla_zapatos >= 33 && talla_zapatos <= 37) *multiplicador = 2;
    else if (talla_zapatos >= 38 && talla_zapatos <= 42) *multiplicador = 3;
    else *multiplicador = 4; // 43 a 47

}

/* Funcion color valido
** Pre-condiciones: Un caracter asignado a la variable color_preferido 
** para ser evaluado como valido o invalido
** Post-condiciones: Devuelve FALSE si no es valido o
** TRUE si es valido. */
bool color_no_valido(char color)
{
    if (color == AZUL
    || color == AMARILLO
    || color == VERDE
    || color == NEGRO
    || color == BLANCO
    || color == ROSA) return false;

    else return true;
}

/* Funcion color preferido
** Pre-condiciones: La existencia de una variable para que pueda cambiarse su valor.
** Post-condiciones: Le asigna a la variable puntaje_color un valor de 5, 15 o 20
** dependiendo del color introducido por el usuario. */
void calculo_puntaje_color(int* color)
{
    char color_preferido;

    printf("Color favorito:\nA para azul.\nY para amarillo.\nV para verde.\nN para negro.\nB para blanco.\nR para rosa.\n");
    scanf(" %c", &color_preferido);

    while (color_no_valido(color_preferido))
    {
        printf("\nERROR 404: color no encontrado, ingrese nuevamente:\nA para azul.\nY para amarillo.\nV para verde.\nN para negro.\nB para blanco.\nR para rosa.\n");
        scanf(" %c", &color_preferido);
    } 

    if (color_preferido == ROSA || color_preferido == AMARILLO) *color =  5;
    else if (color_preferido == NEGRO || color_preferido == BLANCO) *color =  15;
    else *color =  20; // AZUL o VERDE  
}

/* Funcion altura
** Pre-condiciones: La existencia de una variable para que pueda cambiarse su valor.
** Post-condiciones: Le asigna a la variable altura un valor
** entero entre 10 y 250 inclusive */
void pedir_altura(int* altura)
{
    printf("Altura (en cm): ");
    scanf(" %i", altura);

    while (*altura < 10 || *altura > 250)
    {
        if (*altura < 10) printf("\nMuy petiso tiene que ser un poco mas (altura en cm): ");
        else printf("\nNada puede medir mas que mi ego! (altura en cm): ");
        scanf(" %i", altura);
    } 
}

/* Funcion diferencia absoluta
** Pre-condiciones: altura_pesronaje debe ser: 180, 120, 50, 140, 200,30 dependiendo del personaje
** altura_ingresada debe ser un valor entero entre 10 y 250 inclusive.
** Post-condiciones: Devuelve la diferencia entre dichas alturas como
** un valor entero y positivo. */
int diferencia_personaje(int altura_personaje, int altura_ingresada)
{
    int diferencia_absoluta = abs(altura_personaje - altura_ingresada);

    return diferencia_absoluta;
}

/* Funcion personaje detectado
** Pre-condiciones: puntaje debe tener un valor entero entre 1 y 240 inclusive.
** altura_ingresada debe ser un valor entero entre 10 y 250 inclusive.
** personbaje_detectado debe ser el caracter J, B, P, F, H o C.
** Post-condiciones: se le asignara a la variable personaje_detectado el caracter asociado
** a su nombre. */
void definir_personaje(int puntaje, int altura_ingresada, char* personaje_detectado)
{
    int puntaje_final = puntaje; 

    int diferencia_personaje1;
    int diferencia_personaje2;

    // RANGO 1
    if (puntaje_final >= 1 && puntaje_final <= 80)
    {
        diferencia_personaje1 = diferencia_personaje(ALTURA_JOHNNY, altura_ingresada);
        diferencia_personaje2 = diferencia_personaje(ALTURA_CORAJE, altura_ingresada);
        if (diferencia_personaje1 <= diferencia_personaje2) *personaje_detectado = JOHNNY;
        else *personaje_detectado = CORAJE;
    }
    // RANGO 2
    else if (puntaje_final >= 81 && puntaje_final <= 160)
    {
        diferencia_personaje1 = diferencia_personaje(ALTURA_HUESO, altura_ingresada);
        diferencia_personaje2 = diferencia_personaje(ALTURA_POLLITO, altura_ingresada);
        if (diferencia_personaje1 <= diferencia_personaje2) *personaje_detectado = PURO_HUESO;
        else *personaje_detectado = POLLITO;
    } 
    // RANGO 3
    else
    {
        diferencia_personaje1 = diferencia_personaje(ALTURA_BLUE, altura_ingresada);
        diferencia_personaje2 = diferencia_personaje(ALTURA_BELLOTA, altura_ingresada);
        if (diferencia_personaje1 <= diferencia_personaje2) *personaje_detectado = BLUE;
        else *personaje_detectado = BELLOTA;
    }
}

/* Funcion imprimir personaje detectado
** Pre-condiciones: El caracter asociado al personaje que fue detectado por el algoritmo que 
** varia entre J, B, P, F, H o C.
** Post-condiciones: Imprime en pantalla el personaje detectado. */
void imprimir_personaje_detectado(char* personaje_detectado)
{
    printf("Luego de extensos y avanzados calculos, el Detectron3000 a detectado a ");
    if (*personaje_detectado == JOHNNY) printf("- Johnny Bravo -");
    else if (*personaje_detectado == BELLOTA) printf("- Bellota -");
    else if (*personaje_detectado == POLLITO) printf("- Pollito -"); 
    else if (*personaje_detectado == BLUE) printf("- Blue -");
    else if (*personaje_detectado == PURO_HUESO) printf("- Puro Hueso -");
    else printf("- Coraje -"); // Si no es ninguno de los otros casos, es coraje por descarte.
    printf("\n"); // para dejar un renglon al finalizar el print
}

void detectar_personaje(char* personaje_detectado)
{
    // Preguntar fecha de nacimiento
    int puntaje_nacimiento = 0;
    calculo_puntaje_nacimiento(&puntaje_nacimiento);

    // Preguntar preferencia de sabor
    int puntaje_sabor = 0;
    calculo_puntaje_sabor(&puntaje_sabor);

    // Preguntar talla de zapatos
    int multiplicador_zapatos;
    valor_multiplicador_zapatos(&multiplicador_zapatos);

    // Preguntar color preferido
    int puntaje_color = 0;
    calculo_puntaje_color(&puntaje_color);

    // Preguntar altura
    int altura = 0;
    pedir_altura(&altura);

    // Calcular puntaje total
    int puntaje_total = 0;
    puntaje_total = (puntaje_sabor + puntaje_color + puntaje_nacimiento) * multiplicador_zapatos;

    // Detectar personaje
    definir_personaje(puntaje_total, altura, personaje_detectado);
    imprimir_personaje_detectado(personaje_detectado);    

    while(getchar() != '\n');    
}



