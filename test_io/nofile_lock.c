/**
 * 未获取锁的情况下读写文件
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
#include <string.h>

int main(int argc, char *argv[]){
    char buf[100] = "Hello World!";
    int fd;
    int len;
    if(argc != 2){
        fprintf(stderr, "usage:%s<file>\n", argv[0]);
        exit(-1);
    }

    fd = open(argv[1], O_RDWR);
    if(fd == -1){
        perror("open err");
        exit(-1);
    }

    if(flock(fd, LOCK_EX|LOCK_NB) == -1)
        perror("进程2：文件加锁失败");
    else printf("进程2：文件加锁成功");
    len = strlen(buf);
    if(0>write(fd, buf, len)){
        perror("write err");
        exit(-1);
    }
    printf("进程2：写入到文件的字符串<%s>\n", buf);
    if(0>lseek(fd, 0x00, SEEK_SET)){
        perror("lseek err");
        exit(-1);
    }
    /* 读文件 */
    memset(buf, 0x00, sizeof(buf));
    if(0>read(fd, buf, len)){
        perror("read err");
        exit(-1);
    }

    /* 解锁，退出 */
    flock(fd, LOCK_UN);
    close(fd);
    exit(0);
}
