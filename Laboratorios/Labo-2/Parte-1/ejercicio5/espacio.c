#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

/* Forward declaration */
int get_size_dir(char *fname, size_t *blocks);

/* Gets in the blocks buffer the size of file fname using lstat. If fname is a
 * directory get_size_dir is called to add the size of its contents.
 */
int get_size(char *fname, size_t *blocks)
{
	struct stat s;
	if (lstat(fname, &s) == -1)
	{
		return 1;
	}
	if (S_ISDIR(s.st_mode))
	{
		get_size_dir(fname, blocks);
	}
	else
	{
		*blocks += s.st_blocks;
	}
	return 0;
}

/* Gets the total number of blocks occupied by all the files in a directory. If
 * a contained file is a directory a recursive call to get_size_dir is
 * performed. Entries . and .. are conveniently ignored.
 */
int get_size_dir(char *dname, size_t *blocks)
{
	DIR *directory = opendir(dname);
	struct dirent *d;
	while ((d = readdir(directory)))
	{
		if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0)
		{
			continue;
		}
		get_size(d->d_name, blocks);
	}
	closedir(directory);
	return 0;
}

/* Processes all the files in the command line calling get_size on them to
 * obtain the number of 512 B blocks they occupy and prints the total size in
 * kilobytes on the standard output
 */
int main(int argc, char *argv[])
{

	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s [<file_name>]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	int i;
	for (i = 1; i < argc; ++i)
	{
		size_t blocks = 0;
		get_size(argv[i], &blocks);
		printf("%luk %s\n", (blocks * 512) / 1000, argv[i]);
	}

	return 0;
}
