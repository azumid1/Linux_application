/**
 * 这是用来测试uname函数的
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>

int main(int argc, char *argv[]){
    struct utsname os_info;
    int ret;
    ret = uname(&os_info);
    if(ret == -1){
        perror("uname err");
        exit(-1);
    }

    printf("操作系统的名称:%s\n", os_info.sysname);
    printf("主机名:%s\n", os_info.nodename);
    printf("内核版本:%s\n", os_info.release);
    printf("发行版本:%s\n", os_info.version);
    printf("硬件架构:%s\n", os_info.machine);
    exit(0);    
}