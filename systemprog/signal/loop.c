#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
int pid;
pid=getpid();
while(1)
	{
	printf("i am in loop\n");
	printf("pid is %d\n",pid);
	sleep(2);
	}
return 0;

}
