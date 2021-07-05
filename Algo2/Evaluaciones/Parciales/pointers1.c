#include <stdio.h>
#include <stdlib.h>

int main()
{
    char array_chr[16] = {'0','1','2','3','4','5','6','7','8',      
    '9','A','B','C','D','E','F',};

    size_t cant_ptr_array = 4;
    char*** array_madre = malloc(sizeof(char*)*cant_ptr_array);
    if (!array_madre)
        return -1;

    for (size_t i = 0; i < cant_ptr_array; i++)
    {
        array_madre[i] = malloc(sizeof(char*)*cant_ptr_array);
        if (!array_madre[i])
        {
            free(array_madre);
            return -1;
        }
        for (size_t j = 0; j < cant_ptr_array; j++)
        {
            char* chr = malloc(sizeof(char));
            if(!chr)
            {
                free(array_madre);
                return -1;
            }
            *chr = array_chr[(j*4)+i];
            array_madre[i][j] = chr;
        }
    }

    for(size_t i = 0; i < cant_ptr_array; i++)
    {
        for(size_t j = 0; j < cant_ptr_array; j++)
            free(array_madre[i][j]);
        free(array_madre[i]);
    }
    free(array_madre);
    return 0;
}