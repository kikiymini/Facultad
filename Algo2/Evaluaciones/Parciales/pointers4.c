#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* desplazar_derecha(char* string)
{
    char* string_tmp = malloc(sizeof(string));

    if(*(string+1) == '\0')// si estoy en el ultimo
    {
        *string_tmp = string[0];
        return string_tmp;
    }   
    
    char* string_siguiente = desplazar_derecha(string+1);
    *string_tmp = string_siguiente[1];

    return string_tmp;
}

int main()
{
    char* string = "ABCDE";

    char* desplazado = desplazar_derecha(string);
    printf("%s\n", desplazado);

    return 0;
}

