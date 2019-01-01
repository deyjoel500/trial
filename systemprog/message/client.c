#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
#define KEY 19920809
#define SRV_MSG_TYPE 1
#define CLI_MSG_TYPE 2
int main()
{
int msgid;
int msglen;
struct message 
	{
	long type;
	pid_t pid;
	char data[50];
	};
struct message tx,rx;
msgid=msgget(KEY,0);
if(msgid<0)
	{
	printf("couldnot open msgget\n");
	return 1;
	}
printf("enter some request to send to server ,msgid %d\n",msgid);
fgets(tx.data,50,stdin);
tx.type=SRV_MSG_TYPE;
tx.pid=getpid();
printf("froom client --%s\n",tx.data);
msgsnd(msgid,&tx,sizeof(tx),0);
printf("message has been send to server\n");
msglen=msgrcv(msgid,&rx,sizeof(rx),CLI_MSG_TYPE,0);
printf("%s\n",rx.data);
return 0;
}
