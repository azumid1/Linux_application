#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    unsigned char buf[100];
    int fd;
    int ret;

    fd = open("./test_file", O_RDWR);
    if(fd == -1){
        perror("open fail!");
        exit(-1);
    }

    ret = pread(fd, buf, sizeof(buf), 1024);
    if(ret == -1){
        perror("pread err");
        goto err;
    }

    ret = lseek(fd, 0, SEEK_CUR);
    if(ret == -1){
        perror("lseek err");
        goto err;
    }

    printf("current offset:%d\n", ret);
    ret = 0;

err:    
    close(fd);
    exit(ret);
}