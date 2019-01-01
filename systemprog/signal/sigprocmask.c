#include<stdio.h>
#include<signal.h>


int mysigHandler(int signo)
{
printf("%d\n",signo);
}
int main()
{
sigset_t mask;
sigset_t orgmask;
struct sigaction act;
act.sa_handler=mysigHandler;
act.sa_flags=NULL;
sigemptyset(&act.sa_mask);
sigaction(SIGINT,&act,0);
sigemptyset(&mask);
sigaddset(&mask,SIGINT);
printf("printing the value\n");
getchar();
sigprocmask(SIG_BLOCK,&mask,NULL);
printf("after sigprocmask\n");
getchar();
sigprocmask(SIG_UNBLOCK,&mask,NULL);
getchar();
printf("terminating\n");
return 0;
}
