#include <linux/device.h>  
#include <linux/module.h>  
#include <linux/kernel.h>  
#include <linux/init.h>  
#include <linux/string.h>  
#include <linux/init.h>  
#include <linux/platform_device.h>  
  
MODULE_AUTHOR("Hao");  
MODULE_LICENSE("Dual BSD/GPL");  
  
  
static int led_drv_probe(struct platform_device *dev)   //这里面写功能驱动  
{  
        printk("Driver found device which my driver can handle!\n");  
    return 0;  
}  
  
static int led_drv_remove(struct platform_device *dev)  
{  
        printk("Driver found device unpluged!\n");  
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
