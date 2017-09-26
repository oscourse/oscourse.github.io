/**
 * The miscellaneous character device says "hello" to the user space program.
 * Please note that this is a template of our simple miscellaneous character
 * device. It is recommended to test the miscellaneous character device in a VM.
 * @author Kevin Cheng
 * @since  09/25/2017
 */

/* Include all the necessary libraries here. */
#include <linux/init.h>       /* Contains macros such as __init and __exit. */
#include <linux/module.h>     /* Contains headers for the loadable kernel modules. */
#include <linux/kernel.h>     /* Contains types, macro and function of kernel. */

/* Define your macros here. */

/* Specify the module licence and module information such as author, version and
 * description.
 */
MODULE_LICENSE("GPL");

/* [Optional] Forward declarations of function prototypes for the device
 * operations. For the function operation prototype, please refer to
 * http://elixir.free-electrons.com/linux/v4.4/source/include/linux/fs.h#L1600
 */

/* Define the operations of miscellaneous device. For the operation prototypes,
 * please refer to
 * http://elixir.free-electrons.com/linux/v4.4/source/include/linux/fs.h#L1600
 */

/* Define a miscellaneous device. Please refer to
 * http://elixir.free-electrons.com/linux/v4.4/source/include/linux/miscdevice.h#L58
 */

/* Initialize the miscellaneous device. */
static int __init initialize(void) {
  /* Register the miscellaneous device. */

  printk(KERN_INFO "Registration is successful.\n");
  return 0;
}

/* Clean up before exit. */
static void __exit cleanup(void) {
  /* Deregister the miscellaneous device. */

  printk(KERN_INFO "Good Bye!\n");
}

module_init(initialize);
module_exit(cleanup)
