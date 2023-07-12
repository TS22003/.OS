//Pallindrome
//$  chmod a+x pallindrome.sh
//$ ./pallindrome.sh
#!/bin/bash

echo "Enter a string :"
read str1
length=${#str1}
for((i=$length-1;i>=0;i--))
do
    str2="$str2${str1:i:1}"
done
if [ $str1 -eq $str2 ]
then 
    echo "$str1 is plaindrome"
else
    echo "$str1 is not a plaindrome"
fi
echo "$str1 and $str2"

// oddchild
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
int k=1,odd=1,n;
void *ptr;
int shmid = shmget((key_t)151515,4096,IPC_CREAT|0666);
ptr = shmat(shmid,NULL,0666);
printf("CHILD\n");
sscanf(argv[1],"%d",&n);
n = atoi(argv[1]);
while(k<=n)
{
sprintf(ptr,"%d ",odd);
printf("%d ",odd);
ptr+=strlen(ptr);
k++;
odd+=2;
}
return 0;
}

//odd parent

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
execlp("./odd","odd",argv[1],NULL);
}
else if(pid >0)
{
wait(NULL);
printf("\nPARENT : Child Completed\n");
shmid = shmget((key_t)151515,4096,0666);
ptr = shmat(shmid,NULL,0666);
printf("Parent printing\n");
printf("%s",(char *)ptr);
printf("\n");
shmdt(ptr);
}
return 0;
}
