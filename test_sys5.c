#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    struct tms t_buf_start;
    struct tms t_buf_end;
    clock_t t_start;
    clock_t t_end;
    long tck;
    int i,j;

    tck = sysconf(_SC_CLK_TCK);
    t_start = times(&t_buf_start);
    if(-1==t_start){
        perror("times err");
        exit(-1);
    }
    for(i=0; i<20000; i++)
        for(j=0;j<20000;j++)
            ;
    
    sleep(1);
    t_end = times(&t_buf_end);
    if(t_end==-1){
        perror("times err");
        exit(-1);
    }

    printf("时间的总和:%f秒\n", (t_end-t_start)/(double)tck);
    printf("用户cpu时间:%f秒\n", (t_buf_end.tms_utime-t_buf_start.tms_utime)/(double)tck);
    printf("系统cpu时间:%f秒\n", (t_buf_end.tms_stime-t_buf_start.tms_stime)/(double)tck);
    exit(0);
}