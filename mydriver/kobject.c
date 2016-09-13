#include <linux/device.h>  
#include <linux/module.h>  
#include <linux/kernel.h>  
#include <linux/init.h>  
#include <linux/string.h>  
#include <linux/sysfs.h>  
#include <linux/stat.h>  
#include <linux/kobject.h>  
/*设备驱动需要的头文件 */
  
MODULE_AUTHOR("Sun Jack");  
MODULE_LICENSE("Dual BSD/GPL");  
  
/* kobject的结构体 */ 
struct kobject my_kobject;  
  
ssize_t my_show(struct kobject *kobject,struct attribute *attr,char *buf)  
{  
        printk(KERN_EMERG"IN my_show\n");  
        strcpy(buf,"you are reading!!!");  //在sys文件系统中读属性文件的时候应该读出 you are reading!!!  
        return 0;  
}  
ssize_t my_store(struct kobject *kobject,struct attribute *attr,char *buf,size_t size)  
{  
        printk(KERN_EMERG"write : %s\n",buf); //在写属性文件的时候   应该在这里打印出来  
        return 0;  
}  
  
void my_release(struct kobject *my_koject)  
{  
    printk(KERN_EMERG"being release\n");  
}  
  
  
struct sysfs_ops my_kobject_ops={  //对sys文件夹下面sys_my_kobject文件夹的文件进行操作的函数集  
  
        .show=my_show,  
        .store=my_store,  
};  
  
struct attribute my_kobject_file={  //对sys文件夹下面sys_my_kobject文件夹里面创建文件即文件属性  
        .name="my_kobject_file",  
        .mode=S_IRWXU,  
          
};  
  
static struct attribute *def_attrs[] = {   
       &my_kobject_file,  
       NULL,  
};  
  
struct kobj_type my_kobject_type={  //kobject属性  包含sysfs_ops和attribute  
        .release=my_release,  
        .sysfs_ops=&my_kobject_ops,  
        .default_attrs=def_attrs,  
};  
  
/*struct kobject my_kobject= 
{ 
        .name="sys_my_kobject", 
        .ktype=&my_kobject_type, 
         
};*/   //2.6.18版本的koject_init和koject_add只有一个参数所以应该先把这些值都赋值给kobject  
//但是2.6.18版本的这个模块始终挂不上 不知道为什么~~  
  
int my_kobject_init(void)  
{  
        /*需要1.struct kobject my_koject 
                    2.struct kobj_type my_kobject_type(包含struct sysfs_ops my_kobject_ops和struct attribute my_kobject_file) 
                    3.struct kobject *parent 这里没有所以就用NULL 
                    4.kobject的名字 */  
        //kobject_init_and_add(&my_kobject,&my_kobject_type,NULL,"sys_my_kobject");   
        kobject_init(&my_kobject,&my_kobject_type);  
        kobject_add(&my_kobject,NULL,"sys_my_kobject");  
        printk(KERN_EMERG"module insmod success!!!\n");   
}  
  
void my_kobject_exit (void)  
{  
        kobject_del(&my_kobject);//删除koject对象  
        printk(KERN_EMERG"module rmmod success!!!\n");  
}  
  
module_init(my_kobject_init);  
module_exit(my_kobject_exit);  
