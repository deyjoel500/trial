#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/types.h>
int main()
{
int clifd,srvfd,cnt;
char txmsg[20];
char rxmsg[20];
//srvfd=open("srvfifo",O_WRONLY);
while(1)
	{
	srvfd=open("srvvfifo",O_WRONLY);
	printf("enter the string\n");
	fgets(txmsg,20,stdin);
	write(srvfd,txmsg,strlen(txmsg)+1);
	clifd=open("cliiififo",O_RDONLY);
	printf("client first fifo fd %d\n",clifd);
	if(clifd<0)
		{
		mkfifo("cliiififo",0640);
		printf("c ff\n");
		clifd=open("cliiififo",O_RDONLY);
		printf("c fff%d\n",clifd);
		}
	//printf("enter the string\n");
	//fgets(txmsg,20,stdin);
	//write(srvfd,txmsg,strlen(txmsg)+1);
	printf("waiting for response from server\n");
	cnt=read(clifd,rxmsg,20);
	puts(rxmsg);
	close(srvfd);
	close(clifd);
	}

}
