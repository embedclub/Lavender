/*****************************************************************
 ********                      Kset                       ********
 * 时间： 2016.09.17  19.30
 * 功能： Kset使用的示例代码，Kset是Kobject的集合
	  Kset用于保存子目录
 * 作者： Sun Jack
 * 验证平台：已经在tina2.0的源码 + R16的开发板上使用成功
 * 编译方式：采用在内核里面直接添加代码，并编译成模块测试
 * 存在问题：
 * 版本： V1.0
 ***                                                           ***
 *****************************************************************/

#include <linux/device.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/stat.h>
#include <linux/kobject.h>

MODULE_AUTHOR("Sun Jack");
MODULE_LICENSE("Dual BSD/GPL");

struct kset kset_p;
struct kset kset_c;

int kset_filter(struct kset *kset, struct kobject *kobj)
{
	printk("Filter: kobj %s.\n", kobj->name);
	return 1;
}

//有信息传递给用户空间，就可以把信息写到buf里面
const char *kset_name(struct kset *kset, struct kobject *kobj)
{
	static char buf[20];
	printk("Name: kobj %s.\n", kobj->name);
	sprintf(buf, "%s", "kset_name");
	return buf;
}

int kset_uevent(struct kset *kset, struct kobject *kobj, struct kobj_uevent_env *env)
{
	int i = 0;
	printk("uevent: kobj %s.\n", kobj->name);

	while (i < env->envp_idx) {
		printk("%s.\n", env->envp[i]);
		i++;
	}
}

struct kset_uevent_ops uevent_ops = {
	.filter	= kset_filter,
	.name	= kset_name,
	.uevent	= kset_uevent,
};

int kset_test_init()
{
	printk("kset test init.\n");
	//kset_p表示父目录
	kobject_set_name(&kset_p.kobj, "kset_p");
	kset_p.uevent_ops = &uevent_ops;
	kset_register(&kset_p);//注册目录

	//父目录下创建子目录，就会引起热插拔事件	
	//kset_c表示子目录
//	kobject_set_name(&kset_c.kobj, "kset_c");
//	//基类和继承 表示kset_c的父目录是kset_p
//	kset_c.kobj.kset = &kset_p;
//	kset_register(&kset_c);
	return 0;
}

int kset_test_exit()
{
	printk("kset test exit.\n");
	kset_unregister(&kset_p);
	kset_unregister(&kset_c);
	return 0;
}

module_init(kset_test_init);
module_exit(kset_test_exit);
