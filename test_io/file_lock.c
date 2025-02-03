#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define LOCK_FILE   "./testApp.pid"

int main(void){
    char str[20] = {0};
    int fd;

    fd = open(LOCK_FILE, O_WRONLY|O_CREAT, 0666);
    if(fd == -1){
        perror("open err");
        exit(-1);
    }

    if(-1 == flock(fd, LOCK_EX|LOCK_NB)){
        fputs("不能重复执行该程序!\n", stderr);
        close(fd);
        exit(-1);
    }

    puts("程序运行中...");
    ftruncate(fd, 0);   //将文件长度截断为0
    sprintf(str, "%d\n", getpid());
    write(fd, str, sizeof(str));
    for(;;)
        sleep(1);
    
    exit(0);
}