#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/types.h>

int main()
{
int fds[2],ii,n,id;
char readbuf[100];
char writebuf[100];
id=pipe(fds);
if(fork()==0)
	{
	close(fds[1]);
	while(1)
		{
		n=read(fds[0],readbuf,100);
	//	close(fds[0]);
		printf("number of character it read %d\n",n);
		printf("read from fds[0] and output to screen:\n");
		for(ii=0;ii<n;ii++)
			{
			if(isupper(readbuf[ii]))
				readbuf[ii]=tolower(readbuf[ii]);
			else
				readbuf[ii]=toupper(readbuf[ii]);
			}
		puts(readbuf);
		if(n==-1)
			{
			return 0;
			}
		}
	}
else
	{
	close(fds[0]);
	while(1)
		{
		printf("enter the string\n");
		scanf("%s",writebuf);
		write(fds[1],writebuf,strlen(writebuf)+1);
		printf("written to fds[1]\n");
	//	close(fds[1]);
		}
	}
return 0;
}
