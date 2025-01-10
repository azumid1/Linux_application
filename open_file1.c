 #include <sys/types.h>
 #include <sys/stat.h>
 #include <fcntl.h>
#include<stdio.h>
int main(){
	int fd = open("./hello", O_RDONLY);
	if(fd == -1) return -1;
	printf("文件打开！\r\n");
	return 0;
}
