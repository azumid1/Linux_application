#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(void){
    char buf[100];
    int fd,ret;

    fd = open("/dev/input/event3",O_RDONLY|O_NONBLOCK);
    if(fd == -1){
        perror("open err");
        exit(-1);
    }

    memset(buf, 0, sizeof(buf));
    for(;;){
        ret = read(fd, buf, sizeof(buf));
        if(ret < 0){
            printf("成功读取到<%d>个字节\n", ret);
            close(fd);
            exit(0);
        }
    }
}