#include<stdio.h>
#include <unistd.h>
#include<fcntl.h>

#define BUF_SIZE 1024
int main()
{
int inputFd,outputFd,openFlags;
mode_t filePerms;
ssize_t numRead;
char buf[BUF_SIZE];
inputFd=open("text.txt",O_RDONLY);
if(inputFd==-1)
	{
	printf("open error");
	return;
	}
openFlags=O_CREAT|O_WRONLY|O_TRUNC;
filePerms=S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH;
outputFd=open("text2",openFlags,filePerms);
if(outputFd==-1)
	{
	printf("open file");
	return;
	}

while( (numRead=read(inputFd,buf,BUF_SIZE))>0)
	{
	if(write(outputFd,buf,numRead)!=numRead)
		{
		printf("write error\n");
		return;
		}
	printf("%zd\n",numRead);
	}
	
if(numRead==-1)
	{
	printf("read error\n");
	return;
	}

if(close(inputFd)==-1)
	{
	printf("close input");
	return;
	}
if(close(outputFd)==-1)
	{
	printf("close output");
	return;
	}

}
