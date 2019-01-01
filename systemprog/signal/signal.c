#include<signal.h>
#include<stdio.h>

void mysighandler(int signo)
{
	int sig;
	printf("i am in sighandler %d\n",signo);
	sleep(10);
}

int main()
{
signal(2,mysighandler);
while(1)
	{
	printf("hello world\n");
	sleep(2);
	}
return 0;
}
