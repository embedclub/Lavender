/*************************************************************************
	> File Name: mmap.c
	> Author: 
	> Mail: 
	> Created Time: 2016年09月10日 星期六 16时53分30秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/mman.h>
#include<string.h>
int main()
{
    int fd;
    char *start;
    char buf[100];

    fd = open("testfile", O_RDWR);

    start = mmap(NULL, 100, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    strcpy(buf,start);
    printf("buf = %s\n", buf);

    strcpy(start,"Buf Is Not Null!");

    munmap(start, 100);
    close(fd);

    return 0;
}
