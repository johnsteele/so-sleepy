#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/wait.h>
#include <linux/types.h>
#include <linux/fs.h>



ssize_t device_read(struct file *filp, char __user *buff, size_t count,
			loff_t *f_pos)
{
	return count;
}


ssize_t device_write(struct file *filp, const char __user *buff, size_t count, 
			loff_t *f_pos)
{
	return count;
} 


struct file_operations fops = {
	.owner = THIS_MODULE,	
	.read  = device_read,
	.write = device_write,
};


void __exit device_cleanup(void) 
{

}


int __init device_init(void)
{
	int result;
	result = 0;
	return result;
}


module_init(device_init);
module_exit(device_cleanup);


MODULE_AUTHOR("John Steele");
MODULE_LICENSE("DUAL BSD/GPL");

