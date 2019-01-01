#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/types.h>
#define KEY 100
#define SRV_MSG_TYPE 1
#define CLI_MSG_TYPE 2
void togglecase(char *buf,int cnt);
int main()
{
int msgid,msglen;
struct message
	{
	long type;
	pid_t pid;
	char data[20];
	};
struct message tx,rx;
msgid=msgget(KEY,0660|IPC_CREAT);
if(msgid==-1)
	{
	printf("msgget error\n");
	return 1;
	}
printf("waiting to get from client\n");
msglen=msgrcv(msgid,&rx,sizeof(rx),SRV_MSG_TYPE,0);
if(msglen<0)
	{
	printf("msgrcv error\n");
	return 1;
	}
togglecase(rx.data,strlen(rx.data));
tx.type=CLI_MSG_TYPE;
tx.pid=getpid();
strcpy(tx.data,rx.data);
msgsnd(msgid,&tx,sizeof(tx),0);
printf("processed data send\n");
return 0;

}
void togglecase(char *buf,int cnt)
{
int ii;
for(ii=0;ii<cnt;ii++)
	{
	if(buf[ii]>='A' && buf[ii]<='Z')
		buf[ii]+=0x20;
	else if(buf[ii] >= 'a' && buf[ii] <= 'z')
		buf[ii]-=0x20;
	}
}
