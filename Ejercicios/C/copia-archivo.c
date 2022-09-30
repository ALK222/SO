#include <stdio.h>
#include <fcntl.h>

int copia(char *src, char *dest)
{
    int fd1;
    int fd2;
    int n;

    unsigned char c;

    if ((fd1 = open(src, O_RDONLY)) == -1)
    {
        perror("Error al abrir src");
        return -1;
    }

    if ((fd2 = open(dest, O_WRONLY | O_CREAT, 0660)) == -1)
    {
        perror("Error al abrir dest");
        close(fd1);
        return -1;
    }
    // if ((fd2 = open(dest, O_WRONLY)) == -1)
    // {
    //     perror("Error al abrir dest");
    //     close(fd1);
    //     return -1;
    // }
    do
    {
        n = read(fd1, &c, 1);

        if (n > 0)
        {
            // printf("%c", c);
            n = write(fd2, &c, 1);
        }
    } while (n > 0);

    close(fd1);
    close(fd2);

    if (n < 0)
    {
        perror("Error en la copia");
        return -1;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    return copia("a1.txt", "a2.txt");
}
