#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/moduleparam.h>
#include<linux/init.h>
#include<linux/fs.h>
#include<linux/poll.h>
#include<linux/ioport.h>
#include<linux/errno.h>
#include <linux/cdev.h>

#define MAX_BUF_SIZE 1024

static int mydev_open(struct inode *inode,struct file *file);
static int mydev_close(struct inode *inode,struct file *file);
static ssize_t mydev_read(struct file *file,char *buf,size_t count,loff_t *offset);
static ssize_t mydev_write(struct file *file,char *buf,size_t count,loff_t *offset);

#define MYDEV_MAJOR 42
#define MYDEV_MINOR 0
#define MYDEV_NO_DEV 10
#define MYDEV_NAME "mychardev"

typedef struct{
char buf[1024];
int noOfchar;
struct cdev mycdev;
}mydev_t;

mydev_t mydev;

struct file_operations mydev_ops={
.open=mydev_open,
.release=mydev_close,
.read=mydev_read,
.write=mydev_write
};

static int mydev_init(void)
{
int res=0;
dev_t devno=0;
devno=MKDEV(MYDEV_MAJOR,MYDEV_MINOR);
res=register_chrdev_region(devno,MYDEV_NO_DEV,MYDEV_NAME);
if(res<0)
	{
	printk(KERN_ALERT "registration failed\n");
	return res;
	}
else
	printk(KERN_ALERT "registration success\n");
cdev_init(&mydev.mycdev,&mydev_ops);
mydev.mycdev.owner=THIS_MODULE;
res=cdev_add(&mydev.mycdev,devno,1);
if(res)
	{
	printk(KERN_ALERT "cdev_add failed\n");
	goto fail_exit;
	}
printk(KERN_ALERT "cdev_add success\n");
mydev.noOfchar=0;
return 0;
fail_exit:
	unregister_chrdev_region(devno,MYDEV_NO_DEV);
	return res;
}

void mydev_cleanup(void)
{
cdev_del(&mydev.mycdev);
dev_t devno=MKDEV(MYDEV_MAJOR,MYDEV_MINOR);
unregister_chrdev_region(devno,MYDEV_NO_DEV);
printk(KERN_ALERT "unloaded\n");
}

static int mydev_open(struct inode *inode,struct file *file)
{
try_module_get(THIS_MODULE);
file->private_data=&mydev;
if(file->f_mode & FMODE_READ)
	printk(KERN_INFO "read access\n");
if(file->f_mode & FMODE_WRITE)
	printk(KERN_INFO "write access\n");
return 0;
}

static int mydev_close(struct inode *inode, struct file *file)
{
module_put(THIS_MODULE);
printk(KERN_INFO "closed\n");
return 0;
}

static ssize_t mydev_read(struct file *file,char *buf,size_t count,loff_t *offset)
{
mydev_t *t_dev=file->private_data;
if(count>t_dev->noOfchar)
count=t_dev->noOfchar;
copy_to_user(buf,t_dev->buf,count);
printk(KERN_INFO "read success\n");
return (ssize_t)count;
}

static ssize_t mydev_write(struct file *file,char *buf,size_t count, loff_t *offset)
{
mydev_t *t_dev=file->private_data;
if(count>MAX_BUF_SIZE)
count=MAX_BUF_SIZE;
copy_from_user(t_dev->buf,buf,count);
t_dev->noOfchar=count;
printk(KERN_INFO "write success\n");
return (ssize_t)count;
}

MODULE_AUTHOR ("joel");
MODULE_DESCRIPTION("character driver");
MODULE_LICENSE("GPL");

module_init(mydev_init);
module_exit(mydev_cleanup);
