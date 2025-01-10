#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(int arrc, char *argv[]){
    int fd;
    int ret;
    char buffer[1024];
    int i;

    /* 打开文件 */
    fd = open("./hole_file", O_WRONLY|O_CREAT|O_EXCL,
                S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    
    if(fd == -1){
        perror("open err");
        exit(-1);
    }

    ret = lseek(fd, 4096, SEEK_SET);
    if(ret == -1){
        perror("lseek error");
        goto err;
    }
    printf("ret = %d", ret);

    memset(buffer, 0xFF, sizeof(buffer));

    for(i=0; i<4; i++){
        ret = write(fd, buffer, sizeof(buffer));
        if(ret == -1){
            perror("write error");
            goto err;
        }
    }

    ret = 0;

err:
    close(fd);
    exit(ret);
}