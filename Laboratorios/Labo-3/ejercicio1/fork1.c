#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/*programa que crea dos hijos: uno no cambia de ejecutable y otro si */

__pid_t procrear(const char *program, char **arg_list)
{
	__pid_t pid = fork();
	if (pid == 0)
	{
		printf("Proceso hijo, pid %d, pid padre %d\n", pid, getppid());
		execvp("ls", arg_list);
		perror("execvp");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		printf("Proceso padre, pid %d, pid padre %d\n", pid, getppid());
		return pid;
	}
}

int main(int argc, char **argv)
{
	__pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		printf("Proceso hijo, pid %d, pid padre: %d\n", pid, getppid());
	}
	else if (pid > 0)
	{
		printf("Proceso padre, pid %d, pid padre %d\n", pid, getppid());
	}
	else
	{
		printf("yatusabe");
	}

	__pid_t child = procrear(argv[1], argv);

	int wstatus;

	if (waitpid(child, &wstatus, 0) == -1)
	{
		perror("waitpid");
		exit(EXIT_FAILURE);
	}

	return 0;
}
