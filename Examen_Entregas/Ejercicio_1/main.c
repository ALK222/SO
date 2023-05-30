#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFSIZE 13


int get_char(char *fname, int outputFlag, int bites, int d)
{
	struct stat s;
	if (lstat(fname, &s) == -1)
	{
		return 1;
	}
	if (S_ISDIR(s.st_mode))
	{
		get_char_dir(fname, outputFlag, bites, d);
	}
	else
	{
        if(S_ISREG(s.st_mode))
        {
            FILE *ptr = fopen(fname, "r");
            if (NULL == ptr)
            {
                perror("file can't be opened");
                exit(EXIT_FAILURE);
            }
            int i = 0;
            int d;
            char ch = 'a';
            // char buffer[1];
            int pos;
            while (ch != EOF && i < bites)
            {
                ++i;
                ch = fgetc(ptr);
                if(outputFlag == 0)
                { // SALIDA ESTANDAR
                    printf("%c", ch);
                }
                else
                { //FICHERO
                    
                    if (d == -1)
                    {
                        close(ptr);
                        perror("Fallo open dst:");
                        exit(-1);
                    }
                    lseek(d, pos, SEEK_SET);
                    write(d, ch, 1);
                    close(d);
                }
                
                
            }
            if(outputFlag == 1)
            {
                pos = lseek(d, 0, SEEK_CUR);
                write(d, "\n", 1);
                lseek(d, 0, SEEK_CUR);
            }
            else
            {
                printf("\n");
            }
            close(ptr);
        }
       
	}
	return 0;
}

/* Gets the total number of blocks occupied by all the files in a directory. If
 * a contained file is a directory a recursive call to get_char_dir is
 * performed. Entries . and .. are conveniently ignored.
 */
int get_char_dir(char *dname, int outputFlag, int bites, int d1)
{
	DIR *directory = opendir(dname);
	struct dirent *d;
	while ((d = readdir(directory)))
	{
		if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0)
		{
			continue;
		}
		get_char(d->d_name, outputFlag, bites, d1);
	}
	closedir(directory);
	return 0;
}

int main(int argc, char *argv[])
{
	long n = 0;
	int N_FLAG = 0;
	int outputFlag = 0;
	char outfile[1000];
    int c;
	// char *filename = argv[1];
int d = 0;
	while ((c = getopt(argc, argv, "n:o:")) != -1)
	{
        
		switch (c)
		{
		case 'n':
			n = strtol(optarg, NULL, 10);
			N_FLAG = 1;
			break;
		case 'o':
			strcpy(outfile, optarg);
            d = open(outfile, O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR); /* crea el archivo de destida */
            outputFlag = 1;
            break;
		default:
            printf("Usage: %s -n <number of bytes> -o <outfile>\n", argv[0]);
            exit(EXIT_FAILURE);
			break;
		}

        
	}

	if (N_FLAG == 0)
	{
		perror("Necesario un campo -n\n");
		exit(EXIT_FAILURE);
	}

	get_char(".", outputFlag, n, d);

    if(outputFlag == 1)
        {
            close(d);
        }

	return 0;
}