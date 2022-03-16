#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
    int fd;
    int n;
    char buff[512];
    int i;

    if ((fd = open("/dev/input/mice", O_RDONLY)) == -1)
    {
        perror("cannot open");
        exit(1);
    }

    while ((n = read(fd, buff, sizeof(buff))) > 0)
    {
        for (i = 0; i < n; i++)
        {
            printf("%d", buff[i]);
        }
        printf("\n");
    }
    close(fd);
}