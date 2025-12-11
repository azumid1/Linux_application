#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

static void sig_handler(int sig){
    printf("received signal:%d\n", sig);
}

int main(int argc, char *argv[]){
    struct sigaction sig = {0};
    int ret,pid;

    sig.sa_handler = sig_handler;
    sig.sa_flags = 0;
    pid = getpid();
    printf("pid=%d\n", pid);
    ret = sigaction(SIGINT, &sig, NULL);
    if(ret == -1){
        perror("sigaction err");
        exit(-1);
    }

    while(1){
        if(0!=raise(SIGINT)){
            printf("raise error\n");
            exit(-1);
        }
        sleep(3);
    }

    exit(0);

}