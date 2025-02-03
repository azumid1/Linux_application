#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

int main(int argc, char *argv[]){
    int srcfd,dstfd;
    void *srcaddr;
    void *dstaddr;
    int ret;
    struct stat sbuf;
    if(argc != 3){
        fprintf(stderr, "usage:%s<srcfile> <dstfile>\n", argv[0]);
        exit(-1);
    }
    /* 打开原文件 */
    srcfd = open(argv[1], O_RDONLY);
    if(srcfd == -1){
        perror("open srcfile err");
        exit(-1);
    }

    /* 打开目标文件 */
    dstfd = open(argv[2], O_RDWR|O_CREAT|O_TRUNC, 0664);
    if(dstfd == -1){
        perror("open dstfile err");
        ret = -1;
        goto out1;
    }

    /* 获取源文件的大小 */
    fstat(srcfd, &sbuf);
    /* 设置目标文件的大小 */
    ftruncate(dstfd, sbuf.st_size);
    /* 将源文件映射到内存区域中 */
    srcaddr = mmap(NULL, sbuf.st_size, PROT_READ, MAP_SHARED, srcfd, 0);
    if(MAP_FAILED == srcaddr){
        perror("mmap err1");
        ret = -1;
        goto out2;
    }

    /* 将目标文件映射到内存区域中 */
    dstaddr = mmap(NULL, sbuf.st_size, PROT_WRITE, MAP_SHARED, dstfd, 0);
    if(MAP_FAILED == dstaddr){
        perror("mmap err2");
        ret = -1;
        goto out3;
    }

    /* 将源文件中的内容复制到目标文件中 */
    memcpy(dstaddr, srcaddr, sbuf.st_size);

    msync(dstaddr, sbuf.st_size, MS_ASYNC);

/* 解除文件映射 */
out4:
    munmap(dstaddr, sbuf.st_size);
out3:
    munmap(srcaddr, sbuf.st_size);
out2:
    close(dstfd);
out1:
    close(srcfd);
    exit(ret);
}