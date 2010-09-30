/*
 * sleep.c -- A simple char driver that demonstrates
 *            putting a process to sleep.
 * 
 * Copyright (C) 2010 John Steele
 * $Id: sleep.c, v 1.0.0 2010/09/29
 */

#include <linux/module.h> 
#include <linux/init.h>
#include <linux/kernel.h>      /* printk()          */
#include <linux/wait.h>        /* wait_queue_head_t */
#include <linux/types.h>       /* ssize_t, etc      */
#include <linux/fs.h>          /* file_operations   */
#include <linux/cdev.h>        /* cdev              */
#include <linux/moduleparam.h> /* module_param      */

#include "sleepy.h"            /* definitions       */

/*
 * Dynamically allocated char devices.
 * See driver_init() for details. 
 */
struct cdev *my_devices;

/* 
 * Optionally user specified values. 
 */
int my_major = MY_MAJOR;
int my_minor = MY_MINOR;
int my_num_devices = MY_NUM_DEVICES;

module_param(my_major, int, S_IRUGO);
module_param(my_minor, int, S_IRUGO);
module_param(my_num_devices, int, S_IRUGO);


/*
 * Read from the device.
 */
ssize_t device_read(struct file *filp, char __user *buf, size_t count,
			loff_t *f_pos)
{
	return count;
}


/*
 * Write to the device.
 */
ssize_t device_write(struct file *filp, const char __user *buf, size_t count, 
			loff_t *f_pos)
{
	return count;
} 


/* 
 * The functions defined by this driver
 * that perform various operations on the
 * device.
 */
struct file_operations fops = {
	.owner = THIS_MODULE,	
	.read  = device_read,
	.write = device_write,
};


/*
 * Initializes the provided cdev.
 * 
 * @the_cdev The cdev to initialize.
 * @the_index The index of the cdev in my_devices.
 */
static void setup_cdev(struct cdev *the_cdev, const int the_index)
{
	int error;
	int device_number = MKDEV(my_major, my_minor + the_index);
	cdev_init(the_cdev, &fops);
	the_cdev->owner = THIS_MODULE;
	the_cdev->ops   = &fops;
	error = cdev_add(the_cdev, device_number, 1);	
	
	if (error) {
		printk(KERN_NOTICE "Can't register sleep_module%d device.\n", the_index);
	}
}


/*
 * Cleanup the sleepy_module resources. 
 */
static void __exit device_cleanup(void) 
{
	int i;
	if (my_devices) {
		for (i = 0; i < my_num_devices; i++) {
			cdev_del(&my_devices[i]);	
		}
		
		kfree(my_devices);
	}

	unregister_chrdev_region(MKDEV(my_major, my_minor), my_num_devices);
}


/*
 * Initialize the driver.
 *
 * @return 0 for success, failure code otherwise.
 */
static int __init device_init(void)
{
	int result, i;
	dev_t dev; 
	result = 0;


	if (my_major) {
		dev = MKDEV(my_major, my_minor);		
		result = register_chrdev_region(dev, my_num_devices, "sleepy_module");
	} else {
		result = alloc_chrdev_region(&dev, my_minor, my_num_devices, "sleepy_module");
		my_major = MAJOR(dev); 
	}

	if (result < 0) { 
		printk(KERN_NOTICE "Error sleepy module can't get major.\n"); 
		return result;
	}


	my_devices = kmalloc(my_num_devices * sizeof(struct cdev), GFP_KERNEL);
	if (!my_devices) {
		result = -ENOMEM;
		goto fail;
	}

	memset(my_devices, 0, my_num_devices * sizeof(struct cdev));

	
	for (i = 0; i < my_num_devices; i++) {
		setup_cdev(&my_devices[i], i);
	}		


	return 0;

	fail: 
		device_cleanup();
		return result;
}


module_init(device_init);
module_exit(device_cleanup);


MODULE_AUTHOR("John Steele");
MODULE_LICENSE("DUAL BSD/GPL");

