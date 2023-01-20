#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

pid_t child;

void killChild()
{
	kill(child, SIGKILL);
}

void procrear(const char *program, char **arg_list)
{
	child = fork();

	// printf(program);
	if (child == 0)
	{
		execvp(program, arg_list);
	}
	else if (child > 0)
	{
		struct sigaction act = {0};

		act.sa_sigaction = killChild;
		sigaction(SIGALRM, &act, NULL);

		struct sigaction ign;

		ign.sa_handler = SIG_IGN;
		sigaction(SIGINT, &ign, NULL);

		alarm(5); // schedule alarm for 5 seconds

		int n, wstatus;

		do
		{
			n = wait(&wstatus);
		} while ((n == -1) && (errno = EINTR));

		if (WIFEXITED(wstatus))
		{
			printf("Exited normally.\n");
		}
		else if (WIFSIGNALED(wstatus))
		{
			printf("Exited by signal.\n");
		}
	}
}

/*programa que temporiza la ejecución de un proceso hijo */

int main(int argc, char **argv)
{

	char *program = argv[1];

	procrear(program, argv + 1);

	return 0;
}
