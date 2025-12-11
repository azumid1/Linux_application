#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

static void sig_handler(int sig){
    printf("received sig:%d\n",sig);
}

int main(int argc, char *argv[]){
    struct sigaction sig = {0};
    sigset_t wait_mask;

    sigemptyset(&wait_mask);
    sig.sa_handler = sig_handler;
    sig.sa_flags = 0;
    if(sigaction(SIGUSR1, &sig, NULL) == -1){
        perror("sigaction err");
        exit(-1);
    }

    switch(fork()){
        case -1:
            perror("fork err");
            exit(-1);
        case 0:
            printf("子进程开始执行\n");
            printf("子进程打印信息\n");
            printf("*************\n");
            sleep(2);
            kill(getppid(), SIGUSR1);
            _exit(0);
        default:
            if(sigsuspend(&wait_mask) != -1){
                exit(-1);
            }
            printf("父进程开始执行\n");
            printf("父进程打印信息\n");
            exit(0);
    }
}
