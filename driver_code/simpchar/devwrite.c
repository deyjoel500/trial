#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

int main()
{
int fd;
char buf[100];
fd=open("/dev/mydev",O_WRONLY);
if(fd<0)
{
printf("fd failed\n");
return 0;
}
printf("enter the string\n");
fgets(buf,100,stdin);
write(fd,buf,strlen(buf)+1);
close(fd);
}
