#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

#define MAX_BUFFER 1024 /*tamaño del buffer*/
#define RACIONES 1000   /*Datos a producir*/

sem_t *elements; // Elementos en el buffer
sem_t *holes; //huecos en el buffer

int putServingsInPot()
{
    int r = random() % 100;
    return r;
}

void Cocinero(int *buffer)
{
    int pos = 0;
    int dato;
    int i;
    for(i = 0; i < RACIONES; i++){
        dato = putServingsInPot();
        buffer[pos] = dato;
        pos = (pos+1) %MAX_BUFFER;
        sem_post(elements);

    }
}

int main(int argc, char *argv[])
{
    //Aqui preparamos el buffer y los semaforos para producir
    int shd, *bff;

    shd = open("BUFFER", O_CREAT|O_RDWR, 0700);
    ftruncate(shd, MAX_BUFFER *sizeof(int));
    
    bff = (int*)mmap(NULL,MAX_BUFFER *sizeof(int), PROT_WRITE, MAP_SHARED, shd,0);
    elements = sem_open("/ELEMENTS", O_CREAT, 0700,0);
    holes = sem_open("/HOLES", O_CREAT, 0700,MAX_BUFFER);
    //llamamos a cocinero para que cree todas las raciones necesarias hasta llenar
    Cocinero(bff);
    //una vez relleno se procede a desmapear y cerrar los semaforos

    munmap(bff, MAX_BUFFER *sizeof(int));
    close(shd);
    unlink("BUFFER");
    sem_close(elements);
    sem_close(holes);
    sem_unlink("/ELEMENTS");
    sem_unlink("/HOLES");


    exit(EXIT_SUCCESS);
}
