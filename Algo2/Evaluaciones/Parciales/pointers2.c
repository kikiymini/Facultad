#include <stdio.h>
#include <stdlib.h>

typedef struct rojo_t{
    void* campo1;
    struct rojo_t* campo2;
}rojo_t;

typedef struct azul{
    void* campo1;
    rojo_t** campo2;
}azul_t;

int main()
{
    azul_t* v1 = malloc(sizeof(azul_t));
    if (!v1)
        return -1;
    
    v1->campo2 = malloc(sizeof(rojo_t*)*4);
    if(!v1->campo2)
    {
        free(v1);
        return -1;
    }

    for (size_t i = 0; i < 4; i++)
    {
        v1->campo2[i] = malloc(sizeof(rojo_t));
        if (!v1->campo2[i])
        {
            free(v1->campo2);
            free(v1);
            return -1;
        }
    }

    for (size_t j = 0; j < 3; j++)
        v1->campo2[j]->campo2 = v1->campo2[j+1];

    for (size_t k = 0; k < 4; k++)
        free(v1->campo2[k]);
    free(v1->campo2);
    free(v1);

    return 0;
}