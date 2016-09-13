#include <stdio.h>    
#include <string.h>    
#include <stdlib.h>    
#include <unistd.h>    
#include<sys/types.h>    
#include<sys/stat.h>    
#include<fcntl.h>    
#include "plat-drv.h"    
    
int main(int argc, char *argv[])    
{    
    int fd=0;    
    printf("\n%d\n",*argv[1]);    
    unsigned int arg=(unsigned int)(*argv[1]-'0');    
    char buf[40]="WRITE_STR_KCMD is in kernel";    
    if(-1==(fd=open("/dev/misc_led",O_RDWR)))  //设备节点名称为memdev0    
    {    
        printf("Open Dev Mem0 Error!\n");    
        _exit(EXIT_FAILURE);    
    }    
    printf("begin WRITE_KCMD!!!\n");  //写入一个int型arg    
    ioctl(fd,LEDW_KCMD,&arg);    
    close(fd);    
    return 0;    
}   


