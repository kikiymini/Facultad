#include <stdio.h>

/* para los numeros al azar */ 
#include <stdlib.h> 
#include <time.h>

/* constantes para siete y medio */
const int SIETE = 1;
const int PPOT = 2;
const int PyQ = 3;

/* constantes para piedra, papel o tijera */
const int PIEDRA = 1;
const int PAPEL = 2;
const int TIJERA = 3;

/* constantes para pan y queso */
const float PIE = 30.48; /* https://bit.ly/2GBBbtL */

/* constantes generales */
const char SI = 's';
const char NO = 'n';

int main()
{
    /* para los numeros al azar */ 
    srand(time(0)); 

    int juego = 0;
    /* preguntar juego deseado al usuario */
    do
    {
        printf("A que queres jugar?\nIntroducir numero del juego deseado:\n");
        printf("1. 7 y medio\n2. Piedra, Papel o Tijeras\n3. Pan y Queso\n");
        scanf(" %i", &juego);
    } while (juego < 1 || juego > 3);

    /* siete y medio */
    if (juego == SIETE)
    {
        /* cantidad de jugadores */
        int numero_jugadores;
        float score1 = 0;
        float score2 = 0;       
        do
        {
            printf("Cantidad de jugadores? [1/2] ");
            scanf(" %i", &numero_jugadores);
        } while (numero_jugadores < 1 || numero_jugadores > 2);

        /* Ronda */
        int ronda = 1;
        /* por defecto el jugador va a jugar una ronda si o si */
        char jugar_otra_ronda = 's';
        while (jugar_otra_ronda == SI)
        {
            printf("Ronda %i\n", ronda);
            for (int jugador = 1; jugador <= numero_jugadores; jugador++)
            {

                printf("jugador %i, pedir carta? [s/n]", jugador);
                char entregar;
                scanf(" %c", &entregar);

                float suma = 0;
                while (entregar == 's')
                {
                    /* Aca no sabia si habia que generar siempre los mismos numeros
                    o generar azar asi que opte por la segunda y busque en google
                    como hacer un numero al azar y llegue a esto:
                    https://www.geeksforgeeks.org/generating-random-number-range-c/
                    perdon si entendi mal.
                    */

                    int carta = (rand() % (10 - 1 + 1)) + 1;

                    /* Corregir valores */
                    if (carta == 8) carta = 10;
                    if (carta == 9) carta = 11;
                    if (carta == 10) carta = 12;

                    /* Calcular sumatoria */
                    if (carta <= 7) suma = suma + carta;
                    else suma = suma + 0.5;

                    printf("carta %i, suma %.1f\n", carta, suma);

                    /* fijarse si se paso */
                    if (suma > 7.5)
                    {
                        printf("perdiste!\n\n");
                        entregar = 'n';
                    }
                    /* ofrecer otra carta si no perdio*/
                    else
                    {
                        printf("jugador %i, pedir carta? [s/n]", jugador);
                        scanf(" %c", &entregar);              
                    }

                    /* asignar puntaje al jugador */
                    if (jugador == 1) score1 = suma;
                    else score2 = suma;
                } 
            }      

            /* calcular ganador de ronda si es que hay dos jugadores*/
            if (numero_jugadores == 2)
            {
                if (score1 == score2 && score1 <= 7.5) printf("Empate en la ronda %i\n", ronda);
                else if (score1 > 7.5 && score2 > 7.5) printf("Nadie gana la ronda %i\n", ronda);
                else if (score2 > 7.5 || score2 < score1 && score1 <=7.5) printf("El ganador de la ronda %i es el jugador 1\n", ronda);
                else if (score1 > 7.5 || score1 < score2 && score2 <= 7.5) printf("El ganador de la ronda %i es el jugador 2\n", ronda);
            }
            /* si el jugador saca 7.5 gana */
            if (score1 == 7.5) printf("Ganaste!\n");

            /* preguntar si quiere jugar otra ronda */
            printf("Jugar otra ronda? [s/n] ");
            scanf(" %c", &jugar_otra_ronda);
            printf("\n");
            ronda++;
        }


    }

    /* piedra, papel o tijera */    
    else if (juego == PPOT)
    {
        /* almacena eleccion del jugador */
        int jugador1;
        int jugador2;

        /* Ronda */
        int ronda = 1;
        /* por defecto el jugador va a jugar una ronda si o si */
        char jugar_otra_ronda = 's';

        do
        {
            
            printf("\nElegir:\n1. piedra \n2. papel \n3. tijeras\n");
            printf("Jugador 1: ");
            scanf(" %i", &jugador1);
            printf("Jugador 2: ");
            scanf(" %i", &jugador2);

            /* calcular ganador */
            if (jugador1 == PIEDRA)
            {
                if(jugador2 == PAPEL) printf("El jugador 2 es el ganador de la ronda %i", ronda);
                else if (jugador2 == TIJERA) printf("El jugador 1 es el ganador de la ronda %i", ronda);
            }
            else if (jugador1 == PAPEL)
            {
                if(jugador2 == TIJERA) printf("El jugador 2 es el ganador de la ronda %i", ronda);
                else if (jugador2 == PIEDRA) printf("El jugador 1 es el ganador de la ronda %i", ronda);
            }
            else if (jugador1 == TIJERA)
            {
                if(jugador2 == PIEDRA) printf("El jugador 2 es el ganador de la ronda %i", ronda);
                else if (jugador2 == PAPEL) printf("El jugador 1 es el ganador de la ronda %i", ronda);
            }
            else printf("Empate");

            /* preguntar si quiere jugar otra ronda */
            printf("\nJugar otra ronda? [s/n] ");
            scanf(" %c", &jugar_otra_ronda);
            printf("\n");
            ronda++;

        } while (jugar_otra_ronda == SI);
        


    }
    
    /* pan y queso */
    else 
    {
        float distancia;
        printf("Distancia entre jugadores en metros: ");
        scanf("%f", &distancia);

        /*calculo distancia en centimetros para igualar unidades con medida del pie */
        distancia = distancia * 100;

        int turno = 1;
        do
        {
            if (turno % 2 != 0)
            {
                printf("Jugador 1: Pan!\n");
            }
            else printf("Jugador 2: Queso!\n");

            distancia = distancia - PIE;
            turno++;
        } while (distancia > 0); /* si se vuelve negativo significa que se pisaron */
        
        if ((turno) % 2 == 0) printf("Gano Pan! (jugador 1)\n"); 
        else printf("Gano queso! (jugador 2)\n");
    }

    return 0;
}