#include<stdio.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<string.h>
#define MEM_SIZE 10
int main(int argc,char *argv[])
{
char *addr;
int fd;
if((argc<=2)||(strcmp(argv[1],"--help")==0))
	{
	printf("wrong coomand\n");
	return 1;
	}	
fd=open(argv[1],O_RDWR);
if(fd==-1)
	{
	printf("error in opening file descriptor\n");
	return 1;
	}
addr=mmap(NULL,MEM_SIZE,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
if(addr==MAP_FAILED)
	{
	printf("mmap failed\n");
	return 1;
	}
ftruncate(fd,20);
close(fd);
if(argc>2)
	{
	if(strlen(argv[2])>=MEM_SIZE)
		{
		printf("size is too large\n");
		return 1;
		}
	memset(addr,0,MEM_SIZE-1);
	strncpy(addr,argv[2],MEM_SIZE-1);
	printf("copied data\n");
	}
return 0;
}
