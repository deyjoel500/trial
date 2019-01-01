#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
int main()
{
int pid;
scanf("%d",&pid);
kill(pid,2);
return 0;
}
