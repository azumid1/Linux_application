#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    time_t t;
    char t_buf[100] = {0};
    t = time(NULL);
    if(t == -1){
        perror("time err");
        exit(-1);
    }
    ctime_r(&t, t_buf);
    printf("当前时间是:%s", t_buf);
    exit(0);
}