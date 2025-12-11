#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    time_t sec;
    struct tm t;
    sec = time(NULL);
    if(sec == -1){
        perror("time err");
        exit(-1);
    }

    localtime_r(&sec, &t);
    printf("当前的时间是：%d年%d月%d日 %d:%d:%d\n",
        t.tm_year+1900, t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);

    exit(0);
}