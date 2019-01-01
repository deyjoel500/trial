#include <linux/module.h>	
#include <linux/kernel.h>	
#include <linux/proc_fs.h>	
#include <asm/uaccess.h>	
#include<asm/io.h>
#include<linux/init.h>
#include<linux/fs.h>
#include<linux/poll.h>
#include<linux/ioport.h>
#include<linux/errno.h>
#define PROCFS_MAX_SIZE		1024
#define PROCFS_NAME 		"buffer1k"
static struct proc_dir_entry *Our_Proc_File;
static char procfs_buffer[PROCFS_MAX_SIZE];
static unsigned long procfs_buffer_size = 0;
static int procfile_read(char *buffer,char **buffer_location,off_t offset, int buffer_length, int *eof, void *data)
{
	int ret;
	
	printk(KERN_INFO "procfile_read (/proc/%s) called\n", PROCFS_NAME);
	
	if (offset > 0) {
		/* we have finished to read, return 0 */
		ret  = 0;
	} else {
		/* fill the buffer, return the buffer size */
		memcpy(buffer, procfs_buffer, procfs_buffer_size);
		ret = procfs_buffer_size;
	}

	return ret;
}
static int procfile_write(struct file *file, const char *buffer, unsigned long count,void *data)
{
	/* get buffer size */
	procfs_buffer_size = count;
	if (procfs_buffer_size > PROCFS_MAX_SIZE ) {
		procfs_buffer_size = PROCFS_MAX_SIZE;
	}
	
	/* write data to the buffer */
	if ( copy_from_user(procfs_buffer, buffer, procfs_buffer_size) ) {
		return -EFAULT;
	}
	
	return procfs_buffer_size;
}
static int mydev_init(void)
{
	/* create the /proc file */
	Our_Proc_File = create_proc_entry(PROCFS_NAME, 0644, NULL);
	
	if (Our_Proc_File == NULL) {
		remove_proc_entry(PROCFS_NAME, &proc_root);
		printk(KERN_ALERT "Error: Could not initialize /proc/%s\n",
			PROCFS_NAME);
		return -ENOMEM;
	}

	Our_Proc_File->read_proc  = procfile_read;
	Our_Proc_File->write_proc = procfile_write;
	Our_Proc_File->owner 	  = THIS_MODULE;
	Our_Proc_File->mode 	  = S_IFREG | S_IRUGO;
	Our_Proc_File->uid 	  = 0;
	Our_Proc_File->gid 	  = 0;
	Our_Proc_File->size 	  = 37;

	printk(KERN_INFO "/proc/%s created\n", PROCFS_NAME);	
	return 0;	/* everything is ok */
}
static void mydev_cleanup(void)
{
	remove_proc_entry(PROCFS_NAME, &proc_root);
	printk(KERN_INFO "/proc/%s removed\n", PROCFS_NAME);
}

MODULE_AUTHOR("joel");
MODULE_DESCRIPTION("mmmm");
MODULE_LICENSE("GPL");
//module_init(mydev_init);
//module_exit(mydev_cleanup);
