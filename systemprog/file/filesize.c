#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int main()
{
int fd;
struct stat buf;
fd=open("text2",O_RDONLY);
fstat(fd,&buf);
printf("%zd",buf.st_size);
return 0;

}
