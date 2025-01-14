#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    char buf[50];
    int size;
    memset(buf, 0x00, sizeof(buf));

    FILE *fp = NULL;

    fp = fopen("./test_file","r");
    if(fp == NULL){
        perror("fopen fail");
        exit(-1);
    }

    printf("文件打开成功\n");

    if(12 >
        (size=fread(buf, 1, 12, fp))){
        if(ferror(fp)){
            printf("fread error\n");
            fclose(fp);
            exit(-1);
        }
        }
    
    printf("成功读取到%d个字节数据:%s\n", size, buf);
    fclose(fp);
    exit(0);

}