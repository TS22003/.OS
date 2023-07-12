//Simulation of "grep" command 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char* argv[])
{
FILE *fp;
char ch,temp[100];
if(argc<3)
{
printf("\nYou are not passing the Filename\n");
exit(1);
}
fp=fopen(argv[2],"r");
if(fp==NULL)
{
printf("File doesn't exist\n");
exit(1);
}
while(!feof(fp))
{
fgets(temp,100,fp);
if(strstr(temp,argv[1]))
{
printf("%s",temp);
break;
}
}
fclose(fp);
return 0;
}

// without shmget and shmat
// cc fibparent1.c -lrt
//  cc fibchild1.c -o -fib
//./a.out 10
// fibchild

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
int k=2,n1,n2,n3;
void *ptr;
int shmid = shm_open("VK",O_CREAT | O_RDWR,0666);
ftruncate(shmid,4096);
ptr = mmap(0,4096,PROT_WRITE,MAP_SHARED,shmid,0);
printf("CHILD\n");
int i = atoi(argv[1]);
n1=0;
n2=1;
sprintf(ptr,"%d ",n1);
ptr+=strlen(ptr);
printf("%d ",n1);
sprintf(ptr,"%d ",n2);
ptr+=strlen(ptr);
printf("%d ",n2);
while(k!=i)
{
n3=n1+n2;
sprintf(ptr,"%d ",n3);
printf("%d ",n3);
n1=n2;
n2=n3;
ptr+=strlen(ptr);
k++;
}
return 0;
}

//fibparent 
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
int main(int argc, char *argv[])
{
int i,k,n1,n2,n3;
pid_t pid;
const int SIZE=4096;
void *ptr;
int shmid;
if(argc>1)
{
sscanf(argv[1],"%d",&i);
if(i<1)
{
printf("Error Input : %d\n",i);
return 0;
}
}
else
{
printf("Error : Not passing N in Command Line\n");
exit(0);
}
pid = fork();
if(pid==0)
{
execlp("./fib","fib",argv[1],NULL);
}
else if(pid >0)
{
wait(NULL);
printf("\nPARENT : Child Completed\n");
shmid = shm_open("VK",O_RDONLY,0666);
ptr = mmap(0,SIZE,PROT_READ,MAP_SHARED,shmid,0);
printf("Parent printing\n");
printf("%s",(char *)ptr);
printf("\n");
shm_unlink("VK");
}
return 0;
}

// using shmget and shmat
// fibchild

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
int k=2,n1,n2,n3;
void *ptr;
int shmid = shmget((key_t)121212,4096,0666|IPC_CREAT);
ptr = shmat(shmid,NULL,0666);
printf("CHILD\n");
int i = atoi(argv[1]);
n1=0;
n2=1;
sprintf(ptr,"%d ",n1);
ptr+=strlen(ptr);
printf("%d ",n1);
sprintf(ptr,"%d ",n2);
ptr+=strlen(ptr);
printf("%d ",n2);
while(k!=i)
{
n3=n1+n2;
sprintf(ptr,"%d ",n3);
printf("%d ",n3);
n1=n2;
n2=n3;
ptr+=strlen(ptr);
k++;
}
return 0;
}

//fibparent
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <fcntl.h>
int main(int argc, char *argv[])
{
int i,k,n1,n2,n3;
pid_t pid;
const int SIZE=4096;
void *ptr;
int shmid;
if(argc>1)
{
sscanf(argv[1],"%d",&i);
if(i<1)
{
printf("Error Input : %d\n",i);
return 0;
}
}
else
{
printf("Error : Not passing N in Command Line\n");
exit(0);
}
pid = fork();
if(pid==0)
{
execlp("./fib","fib",argv[1],NULL);
}
else if(pid >0)
{
wait(NULL);
printf("\nPARENT : Child Completed\n");
shmid = shmget((key_t)121212,4096,0666);
ptr = shmat(shmid,NULL,0666);
printf("Parent printing\n");
printf("%s",(char *)ptr);
printf("\n");
shmdt(ptr);
}
return 0;
}


