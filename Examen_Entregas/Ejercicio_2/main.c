#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define NJUGADORES 4

struct jugador {
   int dorsal; // dorsal (único) del jugador
   int eficTiro; // entero entre 1 y 100 que determina su efectividad en el tiro 
   int eficRebote; // entero entre 1 y 100 que determina su efectividad en el rebote 
   int puntos; // puntos conseguidos durante el entrenamiento
};

char *progname;
// POSESION -> un jugador tiene el balon.  ENAIRE -> el balón se ha lanzado a canasta
enum estadoBalon_t {POSESION, ENAIRE}; 



#define MAXREBOTE 70
enum estadoBalon_t balon; // Modela el estado actual del balón
int dificultadRebote =0; // var. Global para indicar la dificultad del rebote actual
#define TOPEANOTACION 2
struct jugador jugadores[NJUGADORES] = {
    {0,30,MAXREBOTE,0}, // jugador con dorsal 0, eficTiro 30, eficRebote MAXREBOTE
    {1,80,20,0} ,
    {2,40,MAXREBOTE,0} ,    
    {3,50,50,0}};

pthread_mutex_t m;
pthread_cond_t balon_aire;

int finished = 0;

void rebotear(struct jugador *j )
{  
    printf("jugador %d reboteando\n", j->dorsal);
   while (balon == POSESION && j->eficRebote < dificultadRebote)
    {
        pthread_cond_wait(&balon_aire, &m);
    }
   balon = POSESION;
}

void correr() {
    printf("jugador corriendo\n");
       usleep(100);
}
void tirar(struct jugador *j ) {
    int difTiro;
    
    pthread_mutex_lock(&m);
    printf("jugador %d tirando\n", j->dorsal);
    difTiro = rand() % 100;

    if(difTiro < j->eficTiro)//    <si difTiro es menor que nuestra eficacia en tiro: canasta>  
    {
        printf("jugador %d encesta\n", j->dorsal);
        j->puntos +=2;
    }
    balon = ENAIRE ;
    dificultadRebote = rand() % MAXREBOTE; 
    
    if(j->puntos >= TOPEANOTACION)
    {
        finished = 1;
    }
    pthread_cond_broadcast(&balon_aire);
    pthread_mutex_unlock(&m);
    
}




void* jugadorInit(void* arg) {
   struct jugador *j = arg;
//    printf("%d %d %d %d\n", j->dorsal, j->eficTiro, j->eficRebote, j->puntos);
    while (!finished) {
        rebotear(j);
        correr();
        tirar(j);
        correr();
    }
    printf("Jugador %d: puntuacion -> %d \n", j->dorsal, j->puntos);
   return NULL;
}

int main(int argc, char** argv)
{
    progname = argv[0];

    pthread_t *tid;
    
    tid = malloc(NJUGADORES * sizeof(pthread_t));
    if (tid == NULL)
    {
        perror("malloc tid");
        exit(EXIT_FAILURE);
    }

    pthread_mutex_init(&m, NULL);
    pthread_cond_init(&balon_aire, NULL);

    for (int i = 0; i < NJUGADORES; i++)
    {
        struct jugador *aux;
        aux = malloc(sizeof(struct jugador));
        aux->dorsal = jugadores[i].dorsal;
        aux->eficTiro = jugadores[i].eficTiro;
        aux->eficRebote = jugadores[i].eficRebote;
        aux->puntos = jugadores[i].puntos;
            
        pthread_create(&tid[i], NULL, jugadorInit, aux);
    }

    for (int i = 0; i < NJUGADORES; i++)
        pthread_join(tid[i], NULL);

    return 0;
}
