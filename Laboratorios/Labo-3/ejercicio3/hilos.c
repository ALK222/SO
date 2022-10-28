#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
typedef struct {
pthread_t hilo;
int num_Hilo;
char prio;
}dates;


void *thread_usuario(void *arg)
{
//borrar memoria
	dates *argumentos =arg;

	//pthread_attr_t attr=arg[1];
	//dates datos= arg[3];

int err= pthread_join(argumentos->hilo,NULL);
// getpid
pthread_t id_hilo = pthread_self();
//printf con pid, num hilo y prio
printf("El  pid es %lu, en num hilo es %d, y la prioridad es %c \n",argumentos->hilo, argumentos->num_Hilo, argumentos->prio);
}

int main(int argc, char *argv[])
{

	//pthread_t hilo;
	pthread_attr_t attr;

	dates* datos;
	int err;
	// err= pthread_attr_init(&attr);
	// if(err!=0) {
	// 	perror("N")
	// 	exit(EXIT_FAILURE);}
	datos=malloc(10*sizeof(*datos));
	if(datos == NULL ) {
		perror("malloc error");
		exit(EXIT_FAILURE);}
	int num_hilos=1;
	
	for(int i =0; i < 10; i++){
		datos[i].num_Hilo=num_hilos;
		if(num_hilos%2 ==0) datos[i].prio="P";
		else datos[i].prio="N";
		num_hilos++;

		err =pthread_create(&datos[i].hilo, NULL, thread_usuario,&datos[i]);
		if(err!=0){
		perror("pthread_create error");
		exit(EXIT_FAILURE);
		}
	
	}

	



exit(EXIT_SUCCESS);
}
