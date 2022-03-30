#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/module.h>

static int myopen(struct inode *inode, struct file *file)
{
	printk("myopen called in module\n");
	return 0;
}

static int myclose(struct inode *inodep, struct file *filp)
{
	printk("myclose called in module\n");
	return 0;
}

static ssize_t mywrite(struct file *file, const char __user *buf, size_t len, loff_t *ppos)
{
	char *module_buf;

	printk("mywrite function called in module\n");

	module_buf = (char *)kmalloc(len, GFP_USER);
	if(!module_buf) 
		return -1; //kmalloc failed

	len = copy_from_user(module_buf, buf, len);

	printk("Received this string from user: %s\n", module_buf);

	kfree(module_buf); // clean up

	return len; 

}

static ssize_t myread(struct file *file, char __user *buf, size_t len, loff_t *ppos)
{
	char *module_buf;
	int buflen = strlen("Hello World!\n") + 1;

	printk("myread function called in module\n");

	if( len < buflen)
		return -1; // not enough space in user buffer to return string.

	module_buf = (char *)kmalloc(buflen, GFP_USER);
	if(!module_buf) 
		return -1; //kmalloc failed

	sprintf(module_buf, "Hello World\n");

	len = copy_to_user(buf, module_buf, buflen);

	kfree(module_buf); // clean up

	return len; 
}

static const struct file_operations myfops = {
    .owner	= THIS_MODULE,
    .read	= myread,
    .write	= mywrite,
    .open	= myopen,
    .release	= myclose,
    .llseek 	= no_llseek,
};

struct miscdevice mydevice = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "chatroom",
    .fops = &myfops,
    .mode = S_IRUGO | S_IWUGO,
};

static int __init my_init(void)
{
	printk("my_init called\n");

	// register the character device
	if (misc_register(&mydevice) != 0) {
		printk("device registration failed\n");
		return -1;
	}

	printk("character device registered\n");
	return 0;
}

static void __exit my_exit(void)
{
	printk("my_exit called\n");
	misc_deregister(&mydevice);
}

module_init(my_init)
module_exit(my_exit)
MODULE_DESCRIPTION("Miscellaneous character device module\n");
MODULE_AUTHOR("Kartik Gopalan");
MODULE_LICENSE("GPL");

