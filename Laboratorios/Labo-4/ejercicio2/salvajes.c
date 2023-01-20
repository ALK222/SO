#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/mman.h>

#define MAX_BUFFER 1024 // tamanno del buff
#define RACIONES 100

int *buffer;
sem_t *raciones; // Elementos del buffer
sem_t *vacio;    // Huecos en el buff;

void eat()
{
    printf("%lu comiendo.\n", getpid());
    sleep(rand() % 2);
}
void getServingFromPot()
{
    if (*buffer <= 1)
    {
        sem_post(vacio);
    }
    sem_wait(raciones);
    *buffer -= 1;
    printf("%lu eats. %d servings in pot.\n", getpid(), *buffer);
}

void Savages()
{
    for (int i = 0; i < RACIONES; i++)
    {
        getServingFromPot();
        eat();
    }
}

int main(int argc, char *argv[])
{
    // CREAR Y ABRIR LOS SEMAFOROS
    int shd;
    if ((shd = shm_open("/BUFFER", O_RDWR, S_IRUSR | S_IWUSR)) == -1)
    {
        perror("Open cooker first");
        return -1;
    }
    buffer = (int *)mmap(NULL, MAX_BUFFER * sizeof(int), PROT_WRITE, MAP_SHARED, shd, 0);
    raciones = sem_open("/RACIONES", 0),
    vacio = sem_open("/VACIO", 0);

    // LOs salvajes comen
    Savages();

    // SE CIERRAN LOS SEMAFOROS y memoria compartida
    munmap(buffer, MAX_BUFFER * sizeof(int));
    close(shd);
    sem_close(raciones);
    sem_close(vacio);
    exit(EXIT_SUCCESS);
}
