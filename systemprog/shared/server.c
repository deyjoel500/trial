#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include<string.h>
#define KEY 100
void togglecase(char *buf,int cnt);
int main()
{
int semid,shmid;
char *shm;
struct sembuf smop;
shmid=shmget(KEY,512,IPC_CREAT|0640);
shm=shmat(shmid,NULL,0);
semid=semget(KEY,2,IPC_CREAT|0640);
semctl(semid,0,SETVAL,0);
semctl(semid,1,SETVAL,0);
smop.sem_num=0;
smop.sem_op=-1;
smop.sem_flg=0;
semop(semid,&smop,1);
printf("%s",shm);
strcpy(shm+256,shm);
togglecase(shm+256,strlen(shm+256));
smop.sem_num=1;
smop.sem_op=+1;
smop.sem_flg=0;
semop(semid,&smop,1);
}
void togglecase(char *buf,int cnt)
{
int ii;
for(ii=0;ii<cnt;ii++)
	{
	if((buf[ii]>='A')&&(buf[ii]<='Z'))
		buf[ii]+=0x20;
	if((buf[ii] >='a')&& (buf[ii]<='z'))
		buf[ii]-=0x20; 
	}
}
