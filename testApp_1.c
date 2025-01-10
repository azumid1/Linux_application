#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    int fd1, fd2;
    char buf[1024];
    int ret = 0;

    fd1 = open("./a.txt", O_RDONLY);
    if(fd1 == -1){
        printf("open a.txt failed\r\n");
        return -1;
    }
    fd2 = open("./dest_file", O_WRONLY|O_CREAT|O_EXCL, S_IRWXU|S_IRGRP|S_IROTH);
    if(fd2 == -1){
        printf("open dest_file failed!\r\n");
        ret = -1;
        goto err1;
    }
    ret = lseek(fd1, 500, SEEK_SET);
    if(ret == -1) goto err2;

    ret = read(fd1, buf, sizeof(buf));
    if(ret == -1){
        printf("read fd1 failed!\r\n");
        goto err2;
    }
    ret = lseek(fd2, 0, SEEK_SET);
    if(ret == -1)
    goto err2;

    ret = write(fd2, buf, sizeof(buf));
    if(ret == -1){
        printf("write fd2 failed!\r\n");
        goto err2;
    }

    printf("successful!\r\n");
    ret = 0;

err2:
    close(fd2);
err1:
    close(fd1);
    return ret;
}