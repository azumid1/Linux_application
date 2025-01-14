#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int fd1,fd2;
    int ret;

    fd1 = open("./test_file", O_RDWR);
    if(fd1 == -1){
        perror("open fail!");
        exit(-1);
    }

    fd2 = fcntl(fd1, F_DUPFD, 0);
    if(fd2 == -1){
        perror("fcntl err");
        ret = -1;
        goto err;
    }

    printf("fd1 = %d, fd2 = %d\n", fd1, fd2);
    ret = 0;
    close(fd2);

err:
    close(fd1);
    exit(ret);
}