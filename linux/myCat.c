#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char *av[])
{
    int fd;
    char buff[32];
    int n;

    if(ac<2){
        printf("Usage: CMD filename\n");
        exit(1);
    }
    if((fd=open(av[1],O_RDONLY))==-1){
        perror("cannot open");
        exit(1);
    }
    while((n=read(fd,buff,sizeof(buff)))>0){
        printf("%.*s",n,buff);
    }

}
