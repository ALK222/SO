#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/mman.h>

#define MAX_BUFFER 1024 // tamanno del buff
#define RACIONES 1000

sem_t *elements; //Elementos del buffer
sem_t *holes; //Huecos en el buff;

void eat(int dato){
    printf("se ha comido %d \n", dato);

}
void getServingFromPot(int *buffer){
    int pos = 0;
    int i, dato;
    for(i = 0; i < RACIONES; i++){
        sem_wait(elements);
        dato=buffer[pos];
        pos = (pos+1) %MAX_BUFFER;
        sem_post(holes);
        eat(dato);
    }
}

int main(int argc, char *argv[])
{
    //CREAR Y ABRIR LOS SEMAFOROS 
    int shd, *buffer;
    shd= open("BUFFER", O_RDONLY);
    buffer= (int*) mmap(NULL,MAX_BUFFER * sizeof(int), PROT_READ, MAP_SHARED, shd,0);
    elements= sem_open("/ELEMENTS",0),
    holes = sem_open("/HOLES",0);
    //LOs salvajes comen
    getServingFromPot(buffer);

    // SE CIERRAN LOS SEMAFOROS y memoria compartida
    munmap(buffer, MAX_BUFFER * sizeof(int));
    close(shd);
    sem_close(elements);
    sem_close(holes);
    exit(EXIT_SUCCESS);
}
