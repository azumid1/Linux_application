#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

static pthread_mutex_t mutex;
static int g_count = 0;

static void *new_thread_start(void *arg){
    int loops = *((int *)arg);
    int l_count,j;
    for(j=0;j<loops;j++){
        pthread_mutex_lock(&mutex);
        // l_count = g_count;
        // l_count++;
        // g_count = l_count;
        g_count++;
        pthread_mutex_unlock(&mutex);
    }
    return (void*)0;
}

static int loops;
int main(int argc, char *argv[]){
    pthread_t tid1,tid2;
    int ret;
    if(argc < 2)
        loops = 1000000;
    else loops = atoi(argv[1]);
    pthread_mutex_init(&mutex, NULL);

    ret = pthread_create(&tid1, NULL, new_thread_start, &loops);
    if(ret){
        fprintf(stderr, "pthread_create err:%s", strerror(ret));
        exit(-1);
    }
    ret = pthread_create(&tid2, NULL, new_thread_start, &loops);
    if(ret){
        fprintf(stderr, "pthread_create err:%s", strerror(ret));
        exit(-1);
    }
    ret = pthread_join(tid1, NULL);
    if(ret){
        fprintf(stderr, "pthread_join err:%s", strerror(ret));
        exit(-1);
    }

    ret = pthread_join(tid2, NULL);
    if(ret){
        fprintf(stderr, "pthread_join err:%s", strerror(ret));
        exit(-1);
    }

    printf("g_count=%d\n", g_count);
    exit(0);

}