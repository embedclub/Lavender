#ifndef _LED_H_  
#define _LED_H_  
  
#include <linux/ioctl.h>  
  
#define CMD_KTYPE 'k' //定义命令幻数   也叫命令类型  
  
#define LEDR_KCMD   _IOR(CMD_KTYPE,1,int)   //定义读方向的命令  
#define LEDW_KCMD  _IOW(CMD_KTYPE,2,int)  //定义写方向的命令  
  
#define LED_KCMD 2  //命令个数  后面判断命令是否有效 用的  
  
  
#endif /* _MEMDEV_H_ */  
