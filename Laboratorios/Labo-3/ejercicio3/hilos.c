#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

void *thread_usuario(void *arg)
{
}

int main(int argc, char *argv[])
{

	if (pthread_create() != 0)
	{
		perror("create");
		exit(EXIT_FAILURE);
	}

	return 0;
}
