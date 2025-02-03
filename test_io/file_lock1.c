#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
#include <signal.h>

static int fd = -1;

static void sigint_handler(int sig){
    if(SIGINT != sig)
        return;
    flock(fd, LOCK_UN);
    close(fd);
    printf("进程1：文件已解锁!\n");
}

int  main(int argc, char *argv[]){
    if(argc != 2){
        fprintf(stderr, "usage:%s<file>\n", argv[0]);
        exit(-1);
    }
    fd = open(argv[1], O_WRONLY);
    if(fd == -1){
        perror("open err");
        exit(-1);
    }

    if(flock(fd, LOCK_EX|LOCK_NB) == -1){
        perror("进程1：文件加锁失败!");
        exit(-1);
    }
    printf("进程1：加锁成功!\n");
    signal(SIGINT, sigint_handler);
    for(;;)
        sleep(1);
    
}