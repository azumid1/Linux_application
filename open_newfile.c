#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdio.h>

int main(int argc, char *arg[]){
	int fd = open("./a.txt", O_RDWR|O_CREAT, S_IRWXU|S_IRGRP|S_IROTH);
	if(fd == -1){
		printf("open failed!\r\n");
		return -1;
	}
	printf("fd = %d\r\n", fd);
	return 0;	
}
