#include "interfaz.h"
#include "pa2mm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// PRUEBA CAMBIAR PAGINAS
void prueba_cambiar_pagina()
{
    pa2m_nuevo_grupo("Prueba cambiar pagina:");
    interfaz_t* interfaz = crear_interfaz();

    // PAGINA 1
    elemento_t* elemento1 = crear_elemento("Elemento1", NULL, NULL, NULL);
    elemento_t* elemento2 = crear_elemento("Cambiar a Pagina2", cambiar_pagina, NULL, "Pagina2");
    pagina_t* pagina1 = crear_pagina("Pagina1");
    agregar_elemento(pagina1, elemento1);
    agregar_elemento(pagina1, elemento2);
    agregar_pagina(interfaz, pagina1);

    // PAGINA 2
    elemento_t* elemento3 = crear_elemento("Volver a inicio", cambiar_pagina, NULL, interfaz->pagina_inicio->nombre);
    elemento_t* elemento4 = crear_elemento("Elemento2", NULL, NULL, NULL);
    pagina_t* pagina2 = crear_pagina("Pagina2");
    agregar_elemento(pagina2, elemento3);
    agregar_elemento(pagina2, elemento4);
    agregar_pagina(interfaz, pagina2);

    mostrar_pagina_actual(interfaz);
    char buffer[32];
    buffer[0] = 0;
    while(buffer[0] != 'e')
    {
        printf("- ");
        char* input = fgets(buffer, 32, stdin);
        evaluar_input(interfaz, input);
        mostrar_pagina_actual(interfaz);
    }
}
// ---------------------


int main()
{
    prueba_cambiar_pagina();

    return pa2m_mostrar_reporte();
}