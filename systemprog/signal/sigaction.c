#include<stdio.h>
#include<signal.h>
void sigHandler(int signo)
{
printf("i am in sighandler\n");
sleep(10);
}
int main()
{
struct sigaction act;
act.sa_handler=sigHandler;
act.sa_flags=0;
act.sa_mask;
sigemptyset(&act.sa_mask);
sigaddset(&act.sa_mask,SIGQUIT);
sigaction(SIGINT,&act,0);
while(1)
	{
	printf("hello world\n");
	sleep(2);
	}
return 0;
}
