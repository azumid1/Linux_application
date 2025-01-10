#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main(int argc, char *argv[]){
    // printf("%d\n", errno);
    // printf("no err\r\n");

    int fd;
    fd = open("./b.txt", O_RDONLY);
    if(fd == -1){
        //printf("Error: %s\r\n", strerror(errno));
        perror("Error");
        return -1;
    }

    close(fd);

    return 0;
}