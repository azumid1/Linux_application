#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>

int main(int argc, char argv[]){
    struct sysinfo sys_info;
    int ret;
    ret = sysinfo(&sys_info);
    if(ret == -1){
        perror("sysinfo err");
        exit(-1);
    }

    printf("uptime:%ld\n", sys_info.uptime);
    printf("totalram:%lu\n", sys_info.totalram);
    printf("freeram:%lu\n", sys_info.freeram);
    printf("procs:%u\n", sys_info.procs);
    exit(0);

}