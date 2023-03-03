#include "hello.h"

MODULE_LICENSE("IDK");
MODULE_DESCRIPTION("My firt kernel module");
MODULE_AUTHOR("You");

static char* str = NULL;
static int n = 0;
static int char_dev = 0;

module_param(str, charp, S_IRUSR | S_IWUSR);
module_param(n, int, S_IRUSR | S_IWUSR);


static struct file_operations fops = {
  .read = my_dev_read,
  .write = my_dev_write,
  .open = my_dev_open,
  .release = my_dev_close
};

static int my_dev_open(struct inode *inode, struct file *file)
{
  printk("device is opened\n");
  return 0;
}

static int my_dev_close(struct inode *inode, struct file *file)
{
  printk("device is closed\n");
  return 0;
}

static ssize_t my_dev_read(struct file *file, char *buf, size_t len, loff_t *off)
{
  return len;
}

static ssize_t my_dev_write(struct file *file, const char *buf, size_t len, loff_t *off)
{
  return len;
}


static int __init my_init_fun(void)
{
  int i = 0;
  
  char_dev = register_chrdev(0, "my_input", &fops);
  for (i = 0; i < n; i++)
    printk("hello %s\n", str);
  printk("major = %d\n", char_dev);

  return(0);
}
module_init(my_init_fun);

static void __exit my_exit_fun(void)
{
  int i = 0;

  for (i = 0; i < n; i++)
    printk("goodbye %s\n", str);
}

module_exit(my_exit_fun);
