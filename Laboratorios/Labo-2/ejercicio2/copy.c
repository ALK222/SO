#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	FILE *file = NULL;
	FILE *file2 = NULL;
	int c, ret;

	// if (argc != 2)
	// {
	// 	fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
	// 	exit(1);
	// }

	/* Open file */
	if ((file = fopen(argv[1], "r")) == NULL)
		err(2, "The input file %s could not be opened", argv[1]);

	/* Open file */
	if ((file2 = fopen(argv[2], "w")) == NULL)
		err(2, "The input file %s could not be opened", argv[2]);

	/* Read file byte by byte */
	while ((c = getc(file)) != EOF)
	{
		/* Print byte to stdout */
		ret = putc((unsigned char)c, file2);

		if (ret == EOF)
		{
			fclose(file);
			fclose(file2);
			err(3, "putc() failed!!");
		}
	}

	fclose(file);
	fclose(file2);
	return 0;
}
