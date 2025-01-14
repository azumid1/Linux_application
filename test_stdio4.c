/**
 * 这是测试ftell
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    FILE *fp = NULL;
    int ret;
    if(NULL==(fp = fopen("./test_file", "r"))){
        perror("fopen fail");
        exit(-1);
    }

    fseek(fp, 0, SEEK_END);
    ret = ftell(fp);
    printf("文件共%d个字节\n", ret);
    fclose(fp);
    exit(0);
}