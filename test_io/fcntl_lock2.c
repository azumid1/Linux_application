/**
 * 对文件的100-200字节和400-500字节分别加读锁和写锁
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    struct flock wr_lock = {0};
    struct flock rd_lock = {0};
    int fd = -1;

    if(argc != 2){
        fprintf(stderr, "usage:%s<file>\n", argv[0]);
        exit(-1);
    }

    fd = open(argv[1], O_RDWR|O_TRUNC);
    if(fd == -1){
        perror("open err");
        exit(-1);
    }

    /* 将文件大小截断为1024字节 */
    ftruncate(fd, 1024);
    /* 对100-200字节区间加写锁 */
    wr_lock.l_type = F_WRLCK;
    wr_lock.l_whence = SEEK_SET;
    wr_lock.l_start = 100;
    wr_lock.l_len = 100;
    if(fcntl(fd, F_SETLK, &wr_lock) == -1){
        perror("加读锁失败");
        exit(-1);
    }
    /* 对400-500字节区间加写锁 */
    rd_lock.l_type = F_RDLCK;
    rd_lock.l_whence = SEEK_SET;
    rd_lock.l_start = 400;
    rd_lock.l_len = 100;
    if(fcntl(fd, F_SETLK, &rd_lock) == -1){
        perror("加写锁失败");
        exit(-1);
    }

    printf("加读写锁成功!\n");
    /* 对文件进行其他操作 */
    //...
    wr_lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &wr_lock);
    rd_lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &rd_lock);
    close(fd);
    exit(0);
}