#include <linux/device.h>  
#include <linux/module.h>  
#include <linux/kernel.h>  
#include <linux/init.h>  
#include <linux/string.h>  
#include <linux/init.h>  
#include <linux/platform_device.h>  
  
MODULE_AUTHOR("Hao");  
MODULE_LICENSE("Dual BSD/GPL");  
  
  
#define GPIOM_PA_BASE   0x7f008820  
  
  
struct resource led_resource []= {    
    [0]={  
            .name  = "led io-mem",  //设备资源的名字    
            .start = GPIOM_PA_BASE,    
            .end   = GPIOM_PA_BASE + 0xc,    
            .flags = IORESOURCE_MEM,  
            }    
};  
  
struct platform_device led_dev={  
    .name="plat_led",  //platform总线  里面设备的名字   这个名字要和驱动的名字一样  
    .id=-1,   
    .num_resources=ARRAY_SIZE(led_resource),  //ARRAY_SIZE求资源结构体的个数的  
    .resource=led_resource,  
};  
  
static int __init platform_led_dev_init(void)  
{  
        int ret=0;  
        ret=platform_device_register(&led_dev);  
        if(ret)  
        {  
                printk("platform_device_register failed!!\n");  
        }  
        return ret;  
}  
  
static void __exit platform_led_dev_exit(void)  
{  
        platform_device_unregister(&led_dev);  
}  
  
module_init(platform_led_dev_init);  
module_exit(platform_led_dev_exit);  
