#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/wait.h>
#include <linux/types.h>
#include <linux/fs.h>



struct file_operations fops = {
	.owner = THIS_MODULE,	
	.read  = device_read,
	.write = device_write,
};


ssize_t device_read(struct file *filp, char __user *buff, size_t count,
			loff_t *f_pos)
{

}


ssize_t device_write(struct file *filp, const char __user *buff, size_t count, 
			loff_t *f_pos)
{

} 


void __exit device_cleanup(void) 
{

}


int __init device_init(void)
{

}


module_init(device_init);
module_exit(device_cleanup);

