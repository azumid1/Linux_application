#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *arhv[]){
    struct stat file_stat;
    int ret;

    ret = stat("./test_file", &file_stat);
    if(ret == -1){
        perror("stat error");
        exit(-1);
    }

    printf("file size:%ld bytes\ninode number:%ld\n", file_stat.st_size, file_stat.st_ino);
    exit(0);
}