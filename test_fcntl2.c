#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int fd;
    int ret;
    int flag;

    fd = open("./test_file", O_RDWR);
    if(fd == -1){
        perror("open fail");
        exit(-1);
    }

    flag = fcntl(fd, F_GETFL);
    if(flag == -1){
        perror("fcntl F_GETFL err");
        ret = -1;
        goto err;
    }

    printf("flag = %#x\n",flag);
    ret = fcntl(fd, F_SETFL, flag|O_APPEND);
    if(ret == -1){
        perror("fcntl F_SETFL err");
        goto err;
    }

    ret = 0;

err:
    close(fd);
    exit(ret);
}