#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

static void sig_handler(int sig){
    printf("received signal:%d\n", sig);
}

int main(int argc, char *argv[]){
    struct sigaction sig = {0};
    int ret;
    sig.sa_handler = sig_handler;
    sig.sa_flags = 0;
    ret = sigaction(SIGINT, &sig, NULL);
    if(ret == -1){
        perror("sigaction err");
        exit(-1);
    }

    for(;;){}
    exit(0);
}