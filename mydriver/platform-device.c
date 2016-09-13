#include <linux/device.h>  
#include <linux/module.h>  
#include <linux/kernel.h>  
#include <linux/init.h>  
#include <linux/string.h>  
#include <linux/init.h>  
#include <linux/platform_device.h>  
  
MODULE_AUTHOR("Hao");  
MODULE_LICENSE("Dual BSD/GPL");  
  
struct platform_device led_dev={  
    .name="plat_led",  //platform总线  里面设备的名字   这个名字要和驱动的名字一样  
    .id=-1,   
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



