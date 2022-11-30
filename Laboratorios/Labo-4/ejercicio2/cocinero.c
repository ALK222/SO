#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

#define MAX_BUFFER 1024 /*tamaño del buffer*/
#define RACIONES 1000   /*Datos a producir*/

sem_t *elements;
sem_t *holes;

int putServingsInPot()
{
    int r = random() % 100;
    return r;
}

void Cocinero()
{
    int pos = 0;
    int dato;
    int i;
}

int main(int argc, char *argv[])
{
    while (!finish)
    {
        putServingInPot();
    }
    exit(EXIT_SUCCESS);
}
