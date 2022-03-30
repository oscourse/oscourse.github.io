#include <linux/init.h>
#include <linux/module.h>
MODULE_LICENSE("Dual BSD/GPL");

// called when module is installed
int __init init_module()
{
	printk(KERN_ALERT "mymodule: Hello World!\n");

	return 0;
}



// called when module is removed
void __exit cleanup_module()
{
	printk(KERN_ALERT "mymodule: Goodbye, cruel world!!\n");
}

