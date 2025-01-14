#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    char buf[] = "Hello World!\r\n";
    FILE *fp = NULL;
    if(NULL == (fp = fopen("./test_file","w"))){
        perror("fopen err");
        exit(-1);
    }

    printf("文件打开成功!\r\n");
    
    if(sizeof(buf) > 
        fwrite(buf, 1, sizeof(buf), fp)){
        printf("fwrite err");
        fclose(fp);
        exit(-1);
        }
    
    fclose(fp);
    exit(0);
}