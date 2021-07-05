#include "util.h"
#include <string.h>

#define BUFFER 512

size_t vtrlen(void* ptr){
    if (ptr == NULL)
        return 0;

    size_t tamanio_vtr = 0;
    
    void** ptr_aux = ptr;
    while( *ptr_aux != NULL )
    {        
        tamanio_vtr++;
        ptr_aux++;
    }

    return tamanio_vtr;
}

void* vtradd(void* ptr, void* item){
    size_t tamanio_vtr = 0;
    if (ptr != NULL)
        tamanio_vtr = vtrlen(ptr);

    void** nuevo_vtr = realloc(ptr, (tamanio_vtr + 2)*sizeof(void*));
    if (nuevo_vtr == NULL)
        return NULL;
    void** ptr_aux = nuevo_vtr;
    ptr_aux = ptr_aux + tamanio_vtr;
    *ptr_aux = item;
    ptr_aux++;
    *ptr_aux = NULL;

    return nuevo_vtr;
}

/**
 * Recibe un string y le agrega el caracter al final 
 * ademas de insertar el caracter nulo
 */
char* stradd(char* str, char caracter){
    size_t tamanio_str = 0;
    if (str != NULL)
        tamanio_str = strlen(str);

    char* nuevo_string = realloc(str, (tamanio_str +2) * sizeof(char));
    char* ptr_aux = nuevo_string;
    ptr_aux = ptr_aux + tamanio_str;
    *ptr_aux = caracter;
    ptr_aux++;
    *ptr_aux = '\0';

    return nuevo_string;
}

void vtrfree(void* ptr){
    if (ptr == NULL)
        return;

    void** ptr_aux = ptr;

    size_t cantidad_elementos_vtr = vtrlen(ptr);
    for (size_t i = 0; i < cantidad_elementos_vtr; i++)
    {    
        if (strcmp(*ptr_aux, "") != 0)
            free(*ptr_aux);
        ptr_aux++;
    }  

    free(ptr);
    return;
}

char** split(const char* str, char separador){
    if (str == NULL || strlen(str) == 0)
        return NULL;

    size_t tamanio_str = strlen(str);

    char** vtr_din = NULL;

    char* str_aux = NULL;
    for (size_t i = 0; i < tamanio_str +1; i++)
    {
        if(str[i] != separador && str[i] != '\0')
        {
            str_aux = stradd(str_aux, str[i]);
        }
        else 
        {
            if(str_aux == NULL)
                str_aux = ""; 

            vtr_din = vtradd(vtr_din, str_aux);
            str_aux = NULL;
        }
    }
    
    return vtr_din;
}

char* fgets_alloc(FILE* archivo){
    if (archivo == NULL)
        return NULL;
    
    char* linea = malloc(BUFFER);
    if (!linea)
        return NULL;

    size_t char_leidos = 0;
    size_t cant_allocs = 1;
    while(fgets(linea+char_leidos, (int)((BUFFER*cant_allocs)-char_leidos), archivo))
    {
        size_t leido = 0;
        if ((linea+char_leidos) != NULL)
            leido = strlen(linea+char_leidos);
        
        if (leido > 0 && *(linea+char_leidos+leido-1) == '\n')
        {
            *(linea+char_leidos+leido) = '\0';
            return linea;
        }
        else
        {
            cant_allocs++;
            linea = realloc(linea, BUFFER*cant_allocs);
            if(!linea)
                return NULL;
        }
        char_leidos += leido;
    }

    if(char_leidos == 0)
    {
        free(linea);
        return NULL;
    }

    return linea;
}

void fclosen(FILE* archivo){
    if (archivo != NULL)
        fclose(archivo);
}