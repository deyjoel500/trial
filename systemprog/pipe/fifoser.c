#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
void togglecase(char *buf,int cnt);

int main()
{
int srvfd,clifd,cnt;
char buf[20];
while(1)
	{
	srvfd=open("srvvfifo",O_RDONLY);
	printf("server first fd %d\n",srvfd);
	if(srvfd<0)
		{
		mkfifo("srvvfifo",0640);
		printf("s ff\n");
		srvfd=open("srvvfifo",O_RDONLY);
		printf(" s fff %d\n",srvfd);
		}
	//clifd=open("cliiififo",O_WRONLY);
	//printf("client fifo open success\n");
	cnt=read(srvfd,buf,20);
	togglecase(buf,cnt);
	printf("toggle success\n");
	sleep(1);
	clifd=open("cliiififo",O_WRONLY);
	printf("client fifo open success\n");
	write(clifd,buf,strlen(buf)+1);
	printf("client wriiten\n");
	close(srvfd);
	close(clifd);
	}

}

void togglecase(char *buf,int cnt)
{
int ii;
for(ii=0;ii<cnt;ii++)
	{
	if(buf[ii]>='A' && buf[ii]<='Z')
		buf[ii]+=0x20;
	else if(buf[ii]>='a' && buf[ii] <='z')
		buf[ii]-=0x20;
	}
}

