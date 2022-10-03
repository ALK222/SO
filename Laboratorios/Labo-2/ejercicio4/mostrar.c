#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int main(int argc, char *argv[])
{
	long n = 0;
	int N_FLAG = 0;
	int readLast = 0;
	int c;
	char *filename = argv[1];

	while (1)
	{
		c = getopt(argc, argv, "en:");

		if (c == -1)
		{
			break;
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
	}

	if (readLast == 1 && N_FLAG == 0)
	{
		perror("-e tiene que tener un valor -n");
		exit(EXIT_FAILURE);
	}

	char ch;
	char *chs;
	FILE *ptr = fopen(filename, "r");
	if (NULL == ptr)
	{
		perror("file can't be opened");
		exit(EXIT_FAILURE);
	}

	if (readLast == 1)
	{
		fseek(ptr, 0, SEEK_END);
		int length = ftell(ptr);
		fseek(ptr, (length - n - 1), SEEK_SET);
	}

	int i = 0;
	if (N_FLAG == 0 || N_FLAG == 1 && readLast == 1)
	{
		while (ch != EOF)
		{
			ch = fgetc(ptr);
			printf("%c", ch);
		}
	}
	else
	{
		while (ch != EOF && i < n)
		{
			ch = fgetc(ptr);
			printf("%c", ch);
			++i;
		}
		printf("\n");
	}

	return 0;
}
