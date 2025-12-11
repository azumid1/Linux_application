/**
 * 这是测试 kill函数
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

int main(int argc, char *argv[]){
    int pid;
    if(argc<2)
        exit(-1);
    pid = atoi(argv[1]);
    printf("pid=%d\n", pid);
    if(kill(pid, SIGINT) == -1){
        perror("kill err");
        exit(-1);
    }
    exit(0);
}