#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 13

void copy(int fdo, int fdd)
{
}

void copy_regular(char *orig, char *dest)
{
	int o, d;
	o = open(orig, O_RDONLY); /* abre el archivo de origrada */

	if (o == -1)
	{
		perror("Fallo open src:");
		exit(-1);
	}

	d = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644); /* crea el archivo de destida */
	if (d == -1)
	{
		close(o);
		perror("Fallo open dst:");
		exit(-1);
	}
	int n_read;
	char buffer[BUFSIZE];
	/* bucle de lectura del archivo de origrada */
	while ((n_read = read(o, buffer, BUFSIZE)) == BUFSIZE)
	{
		/* escribir el buffer al archivo de destida */
		if (write(d, buffer, BUFSIZE) < BUFSIZE)
		{
			perror("write");
			close(o);
			close(d);
			exit(-1);
		}
	}
	if (n_read > 0)
		write(d, buffer, n_read);
	close(o);
	close(d);
}

void copy_link(char *orig, char *dest)
{
	ssize_t size;
	struct stat s;
	if (lstat(orig, &s) == -1)
	{
		perror("Error on lstat");
		exit(EXIT_FAILURE);
	}
	size = s.st_size + 1;

	char *buff = malloc(size);
	if (buff == NULL)
	{
		perror("Malloc");
		exit(EXIT_FAILURE);
	}
	ssize_t nbytes = readlink(orig, buff, size);
	if (nbytes == -1)
	{
		perror("readlink");
		free(buff);
		exit(EXIT_FAILURE);
	}
	buff[size - 1] = '\0';

	if (symlink(buff, dest) == -1)
	{
		perror("symlink");
		free(buff);
		exit(EXIT_FAILURE);
	}

	free(buff);
	exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{

	if (argc != 3)
	{
		fprintf(stderr, "Error. Uso: ./copia <src> <dst>\n");
		exit(-1);
	}

	struct stat buffer;
	if (lstat(argv[1], &buffer) == -1)
	{
		perror("Error on lstat");
		exit(EXIT_FAILURE);
	}

	if ((buffer.st_mode & __S_IFMT) == __S_IFREG)
	{

		copy_regular(argv[1], argv[2]);
	}
	else if ((buffer.st_mode & __S_IFMT) == __S_IFLNK)
	{
		copy_link(argv[1], argv[2]);
	}
	else
	{
		perror("not supported");
		exit(EXIT_FAILURE);
	}

	exit(0);
}
