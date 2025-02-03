#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
    struct flock lock;
    int fd = -1;
    char buf[] = "Hello World!";
    if(argc != 2){
        fprintf(stderr, "usage:%s<file>\n", argv[0]);
        exit(-1);
    }

    fd = open(argv[1], O_WRONLY|O_TRUNC);
    if(fd == -1){
        perror("open err");
        exit(-1);
    }
    lock.l_type = F_WRLCK;  //独占性写锁
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0; /* 整个文件都是处于锁的范围内，并且锁的范围是动态可变的 */
    if(fcntl(fd, F_SETLK, &lock) == -1){
        perror("加锁失败");
        exit(-1);
    }

    printf("对文件加锁成功!\n");
    if(write(fd, buf, sizeof(buf))<0){
        perror("write err");
        exit(-1);
    }
    /* 解锁 */
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    close(fd);
    exit(0);
}
