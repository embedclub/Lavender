#include <linux/device.h>  
#include <linux/module.h>  
#include <linux/kernel.h>  
#include <linux/init.h>  
#include <linux/string.h>  
#include <linux/init.h>  
#include <linux/platform_device.h>  
#include <linux/miscdevice.h>  
#include <linux/types.h>  
#include <linux/fs.h>  
#include <linux/errno.h>  
#include <linux/mm.h>  
#include <linux/sched.h>  
#include <linux/cdev.h>  
#include <linux/slab.h>  
#include <linux/poll.h>  
#include <linux/ioport.h>  
#include <asm/io.h>  
#include <asm/system.h>  
#include <asm/uaccess.h>  
#include <asm/atomic.h>  
#include <linux/ioctl.h>  
#include "plat-drv.h"   
  
MODULE_AUTHOR("Hao");  
MODULE_LICENSE("Dual BSD/GPL");  
  
  
volatile unsigned long  GPIOM_VA_BASE;//定义一个全局变量  保存ioremap映射的地址  
  
#define GPIOM_CON_VA    GPIOM_VA_BASE         
#define GPIOM_DAT_VA    (GPIOM_VA_BASE+0x4)       
#define GPIOM_PUD_VA    (GPIOM_VA_BASE+0x8)  
  
struct resource led_res;  
  
static void ok6410_led_setup(struct resource *led_resource)  
{  
        unsigned long temp;   
        led_res=*led_resource;  
        request_mem_region(led_resource->start,(led_resource->end-led_resource->start),led_resource->name);//申请i/o内存 设备资源的名字  
        //其实我觉得用上面那个资源的结构体意义不打  因为request_mem_region就是在跟系统申请这个资源  等价于了把上面的那个资源结构体拷贝到了内核中的设备资源链表  
        GPIOM_VA_BASE = (volatile unsigned long )ioremap(led_resource->start, led_resource->end-led_resource->start);//  
  
/****************************可以直接对地址进行操作***************************************/  
        /* 
        (*(volatile unsigned long *)GPIOM_VA_BASE)&=~0xffff;     
        (*(volatile unsigned long *)GPIOM_VA_BASE)|=0x1|(0x1<<4)|(0x1<<8)|(0x1<<12); 
        temp=0; 
        (*(volatile unsigned long*)GPIOM_DAT_VA)=temp;  //默认所有灯都亮 
        */  
          
          
/*******************也可以用函数api进行操作  貌似这个方式更加安全***************************/  
        temp&=~0xffff;  
        temp|=0x1|(0x1<<4)|(0x1<<8)|(0x1<<12);   
        writel(temp, GPIOM_CON_VA);  
          
        temp|=0xf;  
        temp=0;  
        writel(temp, GPIOM_DAT_VA);  
          
}  
  
static void ok6410_led_release(void)  
{  
    iounmap((void*)GPIOM_VA_BASE);  
    release_mem_region(led_res.start,led_res.end-led_res.start);  
}  
  
/************************************************************************** 
函数名：                     memdev_ioctl 
函数功能:                   ioctl实现函数  命令实习函数 
函数参数:                   无 
函数返回值:                 返回ret为正常执行   返回-EINVAL命令号不正确 
***************************************************************************/  
static long memdev_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)  
{  
    int ret=0;  
    int err=0;  
    int kernel_num=1991;  
    //char kernel_buf[20]="hello kernel!!!";  
      
    /*先判断命令号是否正确*/  
    if (_IOC_TYPE(cmd) != CMD_KTYPE) //获得命令的type类型是否正确  
            return -EINVAL;  
        if (_IOC_NR(cmd) > LED_KCMD)    //获得命令的num类型  是否小于命令个数  
            return -EINVAL;  
              
        /*获命令的数据传输方向   根据各自的方向判断*/    
        if (_IOC_DIR(cmd) & _IOC_READ)  
             err = !access_ok(VERIFY_WRITE, (void *)arg, _IOC_SIZE(cmd));/*此函数是根据 
             内核空间写的 是用来判断 arg应用程序传来的用户空间 是否有效的  所以对于用户空间来说是写*/  
        else if (_IOC_DIR(cmd) & _IOC_WRITE)  
             err = !access_ok(VERIFY_READ, (void *)arg, _IOC_SIZE(cmd));//对于用户空间来说是读   成功返回1  失败返回0  
        if (err)   
            return -EFAULT;  
              
          
        /*实现CMD的用法*/  
        switch(cmd)  
        {  
            case LEDR_KCMD:    
                ret=__put_user(kernel_num, (int *)arg);  //把内核中的int型数据读入用户空间   unsigned long arg就是一个地址值   kernel->arg  
                break;  
            case LEDW_KCMD:  
                ret=__get_user(kernel_num, (int *)arg);   //arg->kernel_num   把用户空间的数据传递给kernel_num  
                printk(KERN_EMERG "WRITE_KCMD is in kernel!!!  kernel_num:%d \n",kernel_num);  
                if(1==kernel_num)  
                    {  
                            writel(0x0, GPIOM_DAT_VA);//将4个led全部点亮  
                    }  
                if(0==kernel_num)  
                    {  
                            writel(0x1f, GPIOM_DAT_VA);//将4个led全部熄灭  
                    }  
                break;  
            default:  
                return -EINVAL;  
                break;  
        }     
          
}  
  
int mem_release(struct inode *inode, struct file *filp)  
{  
    return 0;  
}  
  
int mem_open(struct inode *inode,struct file *filp)  
{  
        return 0;   
}  
  
  
static const struct file_operations mem_fops =  //定义此字符设备的file_operations  
{                       //这里是对结构体整体赋值的方式  
    .owner = THIS_MODULE, //函数名都可以自己定义  都是函数指针  
    .open = mem_open,  
    .release = mem_release,  
    .unlocked_ioctl=memdev_ioctl,  
};  
  
static struct miscdevice misc = {  
    .minor = 0,//设置为0  系统自动分配次设备号  
    .name = "misc_led",  //我觉得这个是设备节点的名字  就是/dev路径下的文件的名字  
    .fops = &mem_fops,  //文件操作  
};  
  
  
static int led_drv_probe(struct platform_device *dev)   //这里面写功能驱动  
{  
        int ret;  
        struct resource *res;  
        printk("Driver found device which my driver can handle!\n");  
        res=platform_get_resource(dev,IORESOURCE_MEM,0);  
        if(res==NULL)  
            {  
                        printk("no memory resource\n");  
                        return 0;  
            }  
        ok6410_led_setup(res);  
        ret=misc_register(&misc);  
    return ret;  
}  
  
static int led_drv_remove(struct platform_device *dev)  
{  
        printk("Driver found device unpluged!\n");  
        ok6410_led_release();    
    misc_deregister(&misc);  
    return 0;  
}  
  
struct platform_driver led_drv={  
        .probe=led_drv_probe,  
        .remove=led_drv_remove,  
        .driver={  
                    .owner=THIS_MODULE,  
                    .name="plat_led",  //platform总线  里面驱动的名字   这个名字要和设备的名字一样  
            }  
};  
  
  
static int __init platform_led_drv_int(void)  
{  
        return platform_driver_register(&led_drv);  
}  
  
  
static void __exit platform_led_drv_exit(void)  
{  
        platform_driver_unregister(&led_drv);  
}  
  
  
module_init(platform_led_drv_int);  
module_exit(platform_led_drv_exit);  


