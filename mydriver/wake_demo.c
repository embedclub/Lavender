#include <linux/module.h>
#include <linux/types.h>
#include <linux/kobject.h>
#include <linux/device.h>

#define power_attr(_name) \
static struct kobj_attribute _name##_attr = {   \
        .attr   = {                             \
                .name = __stringify(_name),     \
                .mode = 0644,                   \
        },                                      \
        .show   = _name##_show,                 \
        .store  = _name##_store,                \
}

static struct wakeup_source *ws;
static void wake_lock(void)
{
    printk("wake lock is running ...\n");
    if (false == ws->active) 
    {
	__pm_stay_awake(ws);
	printk("stay awake ...\n");
    } else {
        printk("already dodod ffanan de..\n");
    }

}

static void wake_unlock(void)
{
    printk("wake unlock is running ...\n");
    if (true == ws->active) 
    {
	__pm_relax(ws);
	printk("relax awake ...\n");
    } else {
        printk("already relax ffanan de..\n");
    }

}

static ssize_t sysfs_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    wake_unlock();
    return sprintf(buf, "%s\n", "sysfs test read,created by vincent");
}
static ssize_t sysfs_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf,ssize_t count)
{
    printk("from user, length = 0x%X, content = %s\n", count, buf);
    wake_lock();
    if(count)
       return count;
    else
       return -1;
}

power_attr(sysfs);

static struct attribute *my_sysfs_test[] = {
    &sysfs_attr.attr,
    NULL,
};

static struct attribute_group my_attr_group = {
    .attrs = my_sysfs_test,
};
static int sysfs_status = 0 ;
struct kobject *soc_kobj = NULL;
int helloworld_init(void)
{
    int ret = 0;
    printk("Hello Android driver : %s\n",__func__);
    printk("Compile Driver Via eclipse IDE: %s\n",__func__);
    soc_kobj = kobject_create_and_add("socslt", NULL);
    if (!soc_kobj)
        goto err_board_obj;
    ret = sysfs_create_group(soc_kobj, &my_attr_group);
    if (ret)
        goto err_soc_sysfs_create;
    sysfs_status = 1;
 
    ws = wakeup_source_register("sun");
    if (NULL == ws)
	goto err_socslt;

    return 0;

err_socslt:
    kobject_put(soc_kobj);
    sysfs_remove_group(soc_kobj, &my_attr_group);
    printk("wakeup_source_register ERROR : %s\n",__func__);
    return 0;

err_soc_sysfs_create:
    kobject_put(soc_kobj);
    sysfs_remove_group(soc_kobj, &my_attr_group);
    printk("\nsysfs_create_group ERROR : %s\n",__func__);
    return 0;

err_board_obj:
    printk("\nobject_create_and_add ERROR : %s\n",__func__);
    return 0;
}
void helloworld_exit(void)
{
    printk("\nExit Android driver : %s\n",__func__);
    printk("Compile Driver Via eclipse IDE: %s\n",__func__);
    if(sysfs_status == 1)
    {
        sysfs_status = 0;
        kobject_put(soc_kobj);
        sysfs_remove_group(soc_kobj, &my_attr_group);
    }
    wakeup_source_unregister(ws);
}

MODULE_AUTHOR("jack sun");
MODULE_LICENSE("Dual BSD/GPL");
module_init(helloworld_init);
module_exit(helloworld_exit);
