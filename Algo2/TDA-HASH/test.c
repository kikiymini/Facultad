#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CLAVE 512
#define TOPE 5000

int hashear(char* clave, size_t tam_hash)
{
    int valor = 518;

    int pos = 0;
    while(clave[pos])
    {
        valor += (clave[pos]*(pos+1) + clave[pos]);
        pos++;
    }

    return (valor % tam_hash);
}

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

int main()
{
    char* string = "AlgoritmosMendez";

    char* copia = string_cpy(string);
    printf("%s\n", copia);
    printf("\n-%c\n", copia[strlen(string)]);
    free(copia);

    return 0;
}