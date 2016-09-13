/*********************************************************************************************
#####¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿                  #####
#####                  #####
#####                  #####

* File£º	hello.c
* Author:	Scc
* Desc£º	hello module code
* History:	9 9th 2016
*********************************************************************************************/

#include <linux/init.h>
#include <linux/module.h>
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Scc Jack");

static char *whom = "world";
static int howmany = 1;


static int __init hello_init(void)
{
        printk(KERN_ALERT "Hello world\n");
	int i;
	for(i=0;i<howmany;i++)
	{
        	printk(KERN_ALERT "Hello %s\n",whom);
	}
        return 0;
}
static void __exit hello_exit(void)
{
        printk(KERN_ALERT " Hello world exit\n");
}
module_init(hello_init);
module_exit(hello_exit);
module_param(howmany, int, S_IRUGO);
module_param(whom, charp, S_IRUGO);
EXPORT_SYMBOL(howmany);
EXPORT_SYMBOL(whom);


