#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#define KEY 19920809
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
	char data[50];
	};
struct message tx,rx;
msgid=msgget(KEY,0660|IPC_CREAT);
if(msgid<0)
	{
	printf("couldnot create message queue\n");
	return 1;
	}
else
	printf("opened message queue,id is %d\n",msgid);
	
printf("server: waiting for message\n");
msglen=msgrcv(msgid,&rx,sizeof(rx),SRV_MSG_TYPE,0);
if(msglen==-1)
	{
	printf("error in msgrcv\n");
	return 1;
	}
printf("received message of size %d from client\n",msglen);
printf("%s\n",rx.data);
togglecase(rx.data,strlen(rx.data));
tx.type=CLI_MSG_TYPE;
tx.pid=getpid();
strcpy(tx.data,rx.data);
msgsnd(msgid,&tx,sizeof(tx),0);
printf("sent processed message to client is %s\n",tx.data);
return 0;
}   

void togglecase(char *buf,int cnt)
{
int ii;
for (ii=0;ii<cnt;ii++)
	{
	if(buf[ii]>='A' && buf[ii]<='Z')
		buf[ii]+=0x20;
	else if(buf[ii]>='a' && buf[ii]<='z')
		buf[ii]-=0x20;
	}
}
