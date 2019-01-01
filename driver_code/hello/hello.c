#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int hello_init(void)
{
printk(KERN_ALERT "hello world\n");
return 0;
}

static void hello_exit(void)
{
printk(KERN_ALERT " Good bye\n");

}
MODULE_AUTHOR("Greg Kroah-Hartman <greg@kroah.com>");
MODULE_DESCRIPTION("Tiny i2c chip");
MODULE_LICENSE("GPL");

module_init(hello_init);
module_exit(hello_exit);
