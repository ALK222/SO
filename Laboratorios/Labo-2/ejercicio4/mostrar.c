#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int main(int argc, char *argv[])
{
	long n = 0;
	int N_FLAG = 0;
	int readLast = 0;
	int c = getopt(argc, argv, "en:");
	if (c == -1)
	{
		perror("getopt");
		exit(EXIT_FAILURE);
	}
	switch (c)
	{
	case 'n':
		n = strtol(optarg, NULL, 10);
		N_FLAG = 1;
		break;
	case 'e':
		readLast = 1;

	default:
		break;
	}

	return 0;
}
