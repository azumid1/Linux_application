#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    struct stat sbuf = {0};
    int fd = -1;
    pid_t pid;
    if(argc != 2){
        fprintf(stderr,"usage:%s<file>\n", argv[0]);
        exit(-1);
    }

    fd = open(argv[1], O_RDWR|O_CREAT|O_TRUNC, 0664);
    if(fd == -1){
        perror("open err");
        exit(-1);
    }
    /* 写入一行字符串 */
    if(12!=write(fd, "Hello World!", 12)){
        perror("write err");
        exit(-1);
    }
    
    if(fstat(fd, &sbuf) < 0){   //获取文件属性，成功返回0，失败返回-1
        perror("fstat err");
        exit(-1);
    }
    if(0>fchmod(fd, (sbuf.st_mode & ~S_IXGRP)|S_ISGID)){
        perror("fchmod err");
        exit(-1);
    }
    /* fork创建子进程 */
    if(0>(pid = fork())){
        perror("fork err");
    }
    else if(pid > 0){//父进程
        struct flock lock = {0};
        lock.l_type = F_WRLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = 0;
        lock.l_len = 0;
        if(0>fcntl(fd, F_SETLK, &lock)){
            perror("父进程加锁失败");
        }
        else printf("父进程加锁成功!\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~\n");
        if(0>wait(NULL)) perror("wait err");
    }
    else {//子进程
        struct flock lock = {0};
        int flag;
        char buf[20] = {0};
        sleep(1);//休眠1秒让父进程先运行

        flag = fcntl(fd, F_GETFL);
        flag |= O_NONBLOCK;
        fcntl(fd, F_SETFL, flag);
        /* 对整个文件加读锁 */
        lock.l_type = F_RDLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = 0;
        lock.l_len = 0;
        if(-1 == fcntl(fd, F_SETLK, &lock)){
            perror("子进程加锁失败");
        }
        else printf("子进程加锁成功!\n");

        /* 读文件 */
        if(0>lseek(fd, 0,SEEK_SET)) perror("lseek err");
        if(0>read(fd,buf,12)) perror("子进程:read err");
        else printf("子进程:read OK,buf = %s\n", buf);
    }
    exit(0);
}