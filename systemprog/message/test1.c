#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<ctype.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#define KEY 100
#define SRV_MSG_TYPE 1
#define CLI_MSG_TYPE 2
int main()
{
int msgid, msglen;
struct message
	{
	long type;
	pid_t pid;
	char data[20];
	};
struct message tx,rx;
msgid=msgget(KEY,0);
if(msgid==-1)
	{
	printf("msgget error\n");
	return 1;
	}
printf("enter the string to get processed\n");
fgets(tx.data,20,stdin);
tx.type=SRV_MSG_TYPE;
tx.pid=getpid();
msgsnd(msgid,&tx,sizeof(tx),0);
printf("waiting\n");
msglen=msgrcv(msgid,&rx,sizeof(rx),CLI_MSG_TYPE,0);
if(msglen<0)
	{
	printf("msgrcv error\n");
	return 1;
	}
puts(rx.data);
return 0;
}
