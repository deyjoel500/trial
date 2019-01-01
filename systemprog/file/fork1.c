#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
int stat;
pid_t id;
id=fork();
if(id==0)
	{
	printf("child process\n");
	exit(5);
	}
wait(&stat);
//printf("%d\n",WEXITSTATUS(stat));
printf("%d\n",stat);
return 0;
}
