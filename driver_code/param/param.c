#include<linux/module.h>
#include<linux/moduleparam.h>
#include <linux/kernel.h>
#include<linux/init.h>
#include<linux/stat.h>

static short int myshort =1;
static int myint =420;
static long int mylong =9999;
static char *mystring = "blah";
static int myintarray[2]={-1,-1};
static int arr_argc=0;

module_param(myshort,short,S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP);
MODULE_PARM_DESC(myshort," a short integer");
module_param(myint,int,S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP);
MODULE_PARM_DESC(myint,"an integer");
module_param(mylong,long,S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP);
MODULE_PARM_DESC(mylong,"a long integer");
module_param(mystring,charp,S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP);
MODULE_PARM_DESC(mystring,"a character string");

module_param_array(myintarray,int,&arr_argc,S_IRUSR|S_IWUSR|S_IWGRP|S_IRGRP);
MODULE_PARM_DESC(myintarray," an array of integers");

static int __init hello_init(void)
{
int i;
printk(KERN_INFO "helloworld\n");
printk(KERN_INFO "myshort is short integer %hd\n",myshort);
printk(KERN_INFO "myint is a integer %d\n",myint);
printk(KERN_INFO "mylong is a long integer%ld\n",mylong);
printk(KERN_INFO "mystring is a string %s\n",mystring);
for(i=0;i<(sizeof myintarray / sizeof (int));i++)
	{
	printk(KERN_INFO "myintarray[%d]=%d\nb",i,myintarray[i]);
	
	}
printk(KERN_INFO "got %d arguments for myintarray\n",arr_argc);
return 0;
}

static void __exit hello_exit(void)
{
printk(KERN_INFO "goodbye\n");
}

MODULE_AUTHOR("JOEL");
MODULE_DESCRIPTION("HELLO");
MODULE_LICENSE("GPL");
module_init(hello_init);
module_exit(hello_exit);
