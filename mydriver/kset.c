#include <linux/device.h>  
#include <linux/module.h>  
#include <linux/kernel.h>  
#include <linux/init.h>  
#include <linux/string.h>  
#include <linux/sysfs.h>  
#include <linux/stat.h>  
#include <linux/kobject.h>  
  
MODULE_AUTHOR("Hao");  
MODULE_LICENSE("Dual BSD/GPL");  
  
struct kset *kset_p;  
struct kset kset_c;  
struct kset kset_a;  
struct kobject my_kobj;  
  
void my_release(struct kobject *kobject)  
{  
        printk("[call obj_test_release]\n");  
}  
  
ssize_t my_show(struct kobject *kobject,struct attribute *attr,char *buf)  
{  
        printk(KERN_EMERG"IN my_show\n");  
        strcpy(buf,"you are reading!!!");  //在sys文件系统中读属性文件的时候应该读出 you are reading!!!  
        return strlen(buf); //注意返回值  
}  
ssize_t my_store(struct kobject *kobject,struct attribute *attr,char *buf,size_t size)  
{  
        printk(KERN_EMERG"write : %s\n",buf); //在写属性文件的时候   应该在这里打印出来  
        return size;   //注意返回值  
}  
  
  
struct sysfs_ops my_kobject_ops={  //对sys文件夹下面sys_my_kobject文件夹的文件进行操作的函数集  
  
        .show=my_show,  
        .store=my_store,  
};  
  
struct attribute attr_str = {  
    .name = "attr_str",  
    .mode = S_IRWXU,  
};  
   
struct attribute attr_name = {  
    .name = "attr_name",  
    .mode = S_IRUSR,  
};  
  
static struct attribute *def_attrs[] = {  //kobject和kset_c中有两个文件  
                &attr_str,  
                &attr_name,  
                NULL,  
};  
  
struct kobj_type my_ktype =   
{  
    .release   = my_release,  
    .sysfs_ops = &my_kobject_ops,  
    .default_attrs = def_attrs,  
};  
  
  
  
  
  
//kset  uevent_ops 热插拔事件  
int kset_filter(struct kset *kset, struct kobject *kobj)  //struct kobject 就是当前发生热插拔的目录  
{  
            printk("[call kset_filter (kobj->name=%s)]\n", kobj->name);  
            return 1;  //只有返回1  剩下的两个函数才有作用  
}  
const char *kset_name(struct kset *kset, struct kobject *kobj)  
{  
    static char buf[20];  
    printk("[call kset_name (kobj->name=%s)]\n", kobj->name);  
    sprintf(buf, "%s", "New Kset Name");  //返回这个字符串给用户空间的热插拔处理程序  
      
    return buf;  
}  
int kset_uevent(struct kset *kset, struct kobject *kobj,struct kobj_uevent_env *env)  
{  
    int i = 0;  
    printk("[uevent: %s]\n", kobj->name);  
  
    while( i < env->envp_idx){  //将所有的环境变量打印出来  
        printk("[envp[%d]: %s]\n", i, env->envp[i]);  
        i++;  
    }  
  
    return 0;  
}  
  
struct kset_uevent_ops uevent_ops =   
{  
    .filter = kset_filter,  //决定是否把事件传递给用户空间  
    .name   = kset_name,    //将字符串返回给用户空间  
    .uevent = kset_uevent,  //添加环境变量  
};  
   
  
int __init my_kset_init(void)  
{  
                int ret=0;  
            kset_p = kset_create_and_add("kset_p", &uevent_ops, NULL);  //创建并注册一个kset 这个kset没有内嵌kobject  
              
            /*一个kset里面可以有好多个kset  但是方法是用内嵌kobject的方式  只有kobj.kset可以确定kset父目录*/  
            /*如果直接创建kobject 也可以但是就是在这个kobject里面只能有文件 不能有目录了*/  
            kobject_set_name(&kset_c.kobj, "kset_c");  //给kset中内嵌的kobject赋值名字  
            kset_c.kobj.kset = kset_p; //kset_c的父目录是kset_p  
            kset_c.kobj.ktype = &my_ktype;//ktype里面包含那三个重要的结构体  
            kset_c.uevent_ops= &uevent_ops;  
                ret = kset_register(&kset_c); //注册kset_c  
                if (ret)  
                    goto err1;  
                /*直接创建一个kobject  把他的父目录写成kset_p*/  
                  
                kobject_set_name(&kset_a.kobj, "kset_a");  //给kset中内嵌的kobject赋值名字  
            kset_a.kobj.kset = &kset_c; //kset_c的父目录是kset_p  
            kset_a.kobj.ktype = &my_ktype;//ktype里面包含那三个重要的结构体  
                ret = kset_register(&kset_a); //注册kset_c  
                  
                  
                my_kobj.parent=&(kset_p->kobj);  
                my_kobj.kset = kset_p;    
                ret = kobject_init_and_add(&my_kobj, &my_ktype, NULL, "my_kobject");  
                if (ret)  
                    goto err;  
                return 0;  
err:   //如果没有注册成功则把注册的 从内核中删除          
    kset_unregister(&kset_c);  
err1:  
    kset_unregister(kset_p);  
    return ret;  
}  
  
void __exit my_kset_exit(void)  //先卸载谁  后卸载谁 都没关系的  都会出现热插拔事件   
{  
        kset_unregister(kset_p);  //卸载所有kset和kobject  
        kset_unregister(&kset_c);  
        kset_unregister(&kset_a);  
        kobject_del(&my_kobj);  
}  
  
module_init(my_kset_init);  
module_exit(my_kset_exit);  
