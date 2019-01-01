#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main()
{
int fd;
fd=open("dup",O_RDWR|O_CREAT,0660);
printf("%d\n",fd);
printf("this is banglore\n");
dup2(fd,1);
printf("this is beml\n");
printf("this is pg\n");
return 0;
}
