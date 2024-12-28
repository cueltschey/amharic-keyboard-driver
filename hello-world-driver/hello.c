#include <linux/hid.h>
#include <linux/input.h>
#include <linux/kernel.h>
#include <linux/module.h>

static int __init hello_world_init(void) {
  pr_info("<1>Hello world");
  return 0;
}

static void __exit hello_world_exit(void) { pr_info("<1>Goodbye world"); }

module_init(hello_world_init);
module_exit(hello_world_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Charles Ueltschey");
MODULE_DESCRIPTION("A basic hello world driver for learning purposes");
