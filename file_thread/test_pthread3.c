#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

static void *new_thread_start(void *arg){
    printf("新线程start\n");
    sleep(2);
    printf("新线程end\n");
    pthread_exit((void*)10);
}

int main(int argc, char *argv[]){
    pthread_t tid;
    int  ret;
    void *tret;

    ret = pthread_create(&tid, NULL, new_thread_start, NULL);
    if(ret){
        fprintf(stderr, "error:%s\n", strerror(ret));
        exit(-1);
    }

    ret = pthread_join(tid, &tret);
    if(ret){
        fprintf(stderr, "pthread_join err:%s\n",strerror(ret));
        exit(-1);
    }

    printf("新线程终止,code=%ld\n",(long)tret);

    exit(0);
}