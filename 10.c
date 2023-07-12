//Simulation of "cat" command 
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[])
{
FILE *fp1;
char ch;
if(argc<2)
{
printf("\nYou are not passing the Filename\n");
exit(1);
}
fp1=fopen(argv[1],"r");
if(fp1==NULL)
{
printf("File doesn't exist\n");
exit(1);
}
while((ch=fgetc(fp1))!=EOF)
printf("%c",ch);
fclose(fp1);
return 0;
}

//Prime child
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc,char *argv[])
{
int i,j,m,n,f;
void *ptr;
int shmid = shmget((key_t)171717,4096,IPC_CREAT|0666);
ptr = shmat(shmid,NULL,0666);
printf("CHILD\n");
sscanf(argv[1],"%d",&m);
sscanf(argv[2],"%d",&n);
m = atoi(argv[1]);
n = atoi(argv[2]);
for(i=m;i<=n;i++)
{
f=0;
for(j=2;j<=i/2;j++)
{
if(i%j==0)
{
f=1;
break;
}
}
if(f==0)
{
sprintf(ptr,"%d ",i);
printf("%d ",i);
ptr+=strlen(ptr);
}
}
return 0;
}
//prime parent
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
int main(int argc, char *argv[])
{
int i;
pid_t pid;
const int SIZE=4096;
void *ptr;
int shmid;
if(argc<2)
{
printf("Error : Not passing arguments in Command Line\n");
exit(0);
}
else
{
pid = fork();
if(pid==0)
{
execlp("./prime","prime",argv[1],argv[2],NULL);
}
else if(pid >0)
{
wait(NULL);
printf("\nPARENT : Child Completed\n");
shmid = shmget((key_t)171717,4096,0666);
ptr = shmat(shmid,NULL,0666);
printf("Parent printing\n");
printf("%s",(char *)ptr);
printf("\n");
shmdt(ptr);
}
return 0;
}
}
