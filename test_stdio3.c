/**
 * 这是用来测试fseek函数的
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]){
    FILE *fp = NULL;
    int ret;
    char rd_buf[100] = {0};
    char wr_buf[] = "正点原子 http://www.openedv.com/forum.php\n";
    if(NULL==(fp=fopen("./test_file","w+"))){
        perror("fopen fail");
        exit(-1);
    }

    printf("文件打开成功!\n");
    if(sizeof(wr_buf) > fwrite(wr_buf, 1, sizeof(wr_buf), fp)){
        printf("fwrite error\n");
        fclose(fp);
        exit(-1);
    }
    printf("数据写入成功\n");
    if(0 > fseek(fp, 0, SEEK_SET)){
        perror("fseek error");
        fclose(fp);
        exit(-1);
    }

    if(sizeof(wr_buf) > 
        (ret = fread(rd_buf, 1, sizeof(wr_buf), fp))){
        printf("fread error\n");
        fclose(fp);
        exit(-1);
        }
    printf("成功读取到%d个字节数据:%s\n", ret, rd_buf);
    fclose(fp);
    exit(0);

}