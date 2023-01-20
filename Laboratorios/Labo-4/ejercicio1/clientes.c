#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

typedef struct
{
    int num_cliente;
    int isVip;
} cliente_t;

char *progname;

int gente = 0;
int aforo = 3;
int nTicketVip = 0;
int turnoVip = 1;
int nTicketNormal = 0;
int turnoNormal = 1;
pthread_mutex_t m;
pthread_cond_t club_lleno_vip;
pthread_cond_t club_lleno_normal;

int vips_restantes = 0;

void *dance(int id, int isVip)
{
    gente++;
    printf("Aforo: %d, gente: %d \n", aforo, gente);
    if (isVip == 1)
    {
        printf("Cliente VIP %d bailando\n", id);
    }
    else
    {
        printf("Cliente %d bailando\n", id);
    }
    sleep(rand() % 5);
}

void *enter_vip_client(int id)
{
    int ticket = nTicketVip; // Asignamos el ticket actual a un cliente
    nTicketVip++;            // ""Creamos"" el siguiente ticket
    turnoVip++;
    vips_restantes++;
    pthread_mutex_lock(&m);
    while (aforo == gente || ticket == turnoVip)
    {
        pthread_cond_wait(&club_lleno_vip, &m);
    }
    pthread_cond_broadcast(&club_lleno_vip);
    pthread_cond_broadcast(&club_lleno_normal);
    vips_restantes--;
    pthread_mutex_unlock(&m);
}

void *enter_normal_client(int id)
{
    int ticket = nTicketNormal; // Asignamos el ticket actual a un cliente
    nTicketNormal++;            // ""Creamos"" el siguiente ticket
    turnoNormal++;
    pthread_mutex_lock(&m);
    while (aforo == gente || ticket == turnoNormal || vips_restantes > 0)
    {
        pthread_cond_wait(&club_lleno_normal, &m);
    }
    pthread_mutex_unlock(&m);
}

void *exit_client(int id)
{
    printf("Sacando cliente %d\n", id);

    gente--;
    if (vips_restantes != 0)
    {
        pthread_cond_broadcast(&club_lleno_vip);
    }
    else
    {
        pthread_cond_broadcast(&club_lleno_normal);
    }
}

void *client(void *arg)
{
    cliente_t *aux = arg;

    printf("Registrando cliente %d\n", aux->num_cliente);
    if (aux->isVip == 1)
    {
        enter_vip_client(aux->num_cliente);
    }

    else
    {
        enter_normal_client(aux->num_cliente);
    }

    dance(aux->num_cliente, aux->isVip);
    exit_client(aux->num_cliente);
}

int main(int argc, char *argv[])
{

    progname = argv[0];

    pthread_t *tid;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    FILE *file = fopen(argv[1], "r");
    int num_clientes;

    if (file == NULL)
    {
        perror("Open file");
        exit(EXIT_FAILURE);
    }

    // Num gente
    fscanf(file, "%d\n", &num_clientes);

    tid = malloc(num_clientes * sizeof(pthread_t));
    if (tid == NULL)
    {
        perror("malloc tid");
        exit(EXIT_FAILURE);
    }

    pthread_mutex_init(&m, NULL);
    pthread_cond_init(&club_lleno_normal, NULL);
    pthread_cond_init(&club_lleno_vip, NULL);

    for (int i = 0; i < num_clientes; i++)
    {
        cliente_t *aux;
        aux = malloc(sizeof(cliente_t));
        aux->num_cliente = i;
        fscanf(file, "%d\n", &(aux->isVip));
        pthread_create(&tid[i], NULL, client, aux);
    }

    for (int i = 0; i < num_clientes; i++)
        pthread_join(tid[i], NULL);

    pthread_mutex_destroy(&m);
    pthread_cond_destroy(&club_lleno_normal);
    pthread_cond_destroy(&club_lleno_vip);

    free(tid);

    exit(EXIT_SUCCESS);
}
