#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
int fd;
char buf[100];
fd=open("/dev/mydev",O_RDONLY);
if(fd<0)
	{
	printf("fd failed\n");
	}
int stat;
stat=read(fd,buf,sizeof(buf));
printf("read characters %d\n",stat);
buf[stat-1]=0;
puts(buf);
close(fd);
return 0;
}
