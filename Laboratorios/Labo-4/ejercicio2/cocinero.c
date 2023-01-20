#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <signal.h>

#define MAX_BUFFER 1024 /*tamaño del buffer*/
#define RACIONES 10     /*Datos a producir*/

int finish = 0;
int *buffer;
sem_t *raciones; // Elementos en el buffer
sem_t *vacio;    // huecos en el buffer

void putServingsInPot(int servings)
{
    for (int i = 0; i < servings; ++i)
    {
        *buffer += 1;
        sem_post(raciones);
    }
    printf("%d rations served by %d\n", *buffer, getpid());
}

void Cocinero()
{
    while (!finish)
    {
        putServingsInPot(RACIONES);
        sem_wait(vacio);
    }
}

void handler(int s)
{
    finish = 1;
    sem_post(vacio);
    printf("\n");
}

int main(int argc, char *argv[])
{
    // Aqui preparamos el buffer y los semaforos para producir
    int shd;

    signal(SIGINT, handler);
    signal(SIGTERM, handler);

    shd = shm_open("/BUFFER", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    ftruncate(shd, MAX_BUFFER * sizeof(int));

    buffer = (int *)mmap(NULL, MAX_BUFFER * sizeof(int), PROT_WRITE, MAP_SHARED, shd, 0);
    *buffer = 0;

    raciones = sem_open("/RACIONES", O_CREAT, 0700, 0);
    vacio = sem_open("/VACIO", O_CREAT, 0700, 0);
    // llamamos a cocinero para que cree todas las raciones necesarias hasta llenar
    Cocinero();
    // una vez relleno se procede a desmapear y cerrar los semaforos

    munmap(buffer, MAX_BUFFER * sizeof(int));
    close(shd);
    unlink("/BUFFER");
    sem_close(vacio);
    sem_close(raciones);
    sem_unlink("/RACIONES");
    sem_unlink("/VACIO");

    exit(EXIT_SUCCESS);
}
