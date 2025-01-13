#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *arhv[]){
    int fd;
    char buf[16];
    int ret;
    /*
    fd = open("./a.txt", O_WRONLY|O_TRUNC);
    if(fd == -1){
        perror("open file!\r\n");
        exit(-1);
    }

    */

   fd = open("./a.txt", O_RDWR|O_APPEND);
   if(fd == -1){
    perror("open fail!\r\n");
    exit(-1);
   }

    memset(buf, 0x55,sizeof(buf));
    ret = write(fd, buf, 4);
    if(ret < 0){
        perror("write fail!\r\n");
        goto err;
    }

    memset(buf, 0x00, sizeof(buf));
    ret = lseek(fd, -4, SEEK_END);
    if(ret < 0){
        perror("lseek err!\r\n");
        goto err;
    }

    ret = read(fd, buf, 4);
    if(ret == -1){
        perror("read err!\r\n");
        goto err;
    }
    printf("0x%x 0x%x 0x%x 0x%x\n",buf[0], buf[1], buf[2], buf[3]);
    ret = 0;

err:
    close(fd);
    exit(ret);
}