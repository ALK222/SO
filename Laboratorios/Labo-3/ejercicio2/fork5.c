#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* programa que crea N hijos siguiendo un grado de dependencias. Usa las
 * versiones de execl y execlp */

#define N 8

int main(int argc, char **argv)
{

	// pid_t pros[N];
	char **nombres[N] = {"P1", "P2", "P5", "P7", "P3", "P4", "P6", "P8"};

	int *contador = 0;
	malloc(sizeof(int));

	pid_t p1 = fork();

	if (p1 == 0)
	{
		printf("%d", 1);
		// execlp("echo", "p1");
		exit(EXIT_SUCCESS);
	}

	wait(p1);

	pid_t p2 = fork();
	if (p2 == 0)
	{
		printf("%d", 2);
		// execl("echo", "p2");
		exit(EXIT_SUCCESS);
	}
	pid_t p5 = fork();
	if (p5 == 0)
	{
		printf("%d", 5);
		// execlp("echo", "p5");
		exit(EXIT_SUCCESS);
	}
	pid_t p7 = fork();
	if (p7 == 0)
	{
		printf("%d", 7);
		// execlp("echo", "p7");
		exit(EXIT_SUCCESS);
	}
	int wstatus;
	if (waitpid(p2, &wstatus, 0) == -1)
	{
		perror("waitpid p2");
		exit(EXIT_FAILURE);
	}
	else
	{
		pid_t p3 = fork();
		if (p3 == 0)
		{
			printf("%d", 3);
			// execlp("echo", "p3");
			exit(EXIT_SUCCESS);
		}
		pid_t p4 = fork();
		if (p4 == 0)
		{
			printf("%d", 4);
			// execl("echo", "p4");
			exit(EXIT_SUCCESS);
		}

		if (waitpid(p4, &wstatus, 0) == -1)
		{
			perror("waitpid p4");
			exit(EXIT_FAILURE);
		}
		else
		{
			if (waitpid(p5, &wstatus, 0) == -1)
			{
				perror("waitpid p5");
				exit(EXIT_FAILURE);
			}
			else
			{
				pid_t p6 = fork();
				if (p6 == 0)
				{
					printf("%d", 6);
					// execl("echo", "p6");
					exit(EXIT_SUCCESS);
				}

				if (waitpid(p3, &wstatus, 0) == -1)
				{
					perror("waitpid p3");
					exit(EXIT_FAILURE);
				}
				else
				{
					if (waitpid(p6, &wstatus, 0) == -1)
					{
						perror("waitpid p6");
						exit(EXIT_FAILURE);
					}
					else
					{
						if (waitpid(p7, &wstatus, 0) == -1)
						{
							perror("waitpid p7");
							exit(EXIT_FAILURE);
						}
						else
						{
							pid_t p8 = fork();
							if (p8 == 0)
							{
								printf("%d", 8);
								// execl("echo", "p8");
								exit(EXIT_SUCCESS);
							}
						}
					}
				}
			}
		}
	}

	return 0;
}
