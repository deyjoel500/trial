#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include<string.h>
#define KEY 100

int main()
{
int semid,shmid;
char *shm;
struct sembuf smop;
shmid=shmget(KEY,512,0);
shm=shmat(shmid,NULL,0);
semid=semget(KEY,2,0);
strcpy(shm,"viven");
smop.sem_num=0;
smop.sem_op=+1;
smop.sem_flg=0;
semop(semid,&smop,1);
smop.sem_num=1;
smop.sem_op=-1;
smop.sem_flg=0;
semop(semid,&smop,1);
printf("%s",shm+256);
return 0;
}
