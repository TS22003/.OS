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
   // program to print n odd numbers using shm_open and mmap system calls.
//child
    
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<sys/shm.h>
#include<sys/mman.h>

int main(int argc, char *argv[]) {
    int n, i=1;
    void *shmptr;
    int shmid = shm_open("OS", O_CREAT|O_RDWR, 0666);
    ftruncate(shmid, 4096);
    shmptr = mmap(0, 4096, PROT_WRITE, MAP_SHARED, shmid, 0);
    printf("\nChild Printing:\n");
    n = atoi(argv[1]);
    
    while(n != 0) {
        if(i%2 != 0) {
            sprintf(shmptr, "%d ", i);
            printf("%d ", i);
            shmptr += strlen(shmptr);
            n--;
        }
        i++;
    }

    return 0;
}

//parent

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<sys/shm.h>
#include<sys/mman.h>

int main(int argc, char *argv[]) {
    int n, i;
    pid_t pid;
    void *shmptr;
    int shmid;

    if (argc > 1) {
        sscanf(argv[1], "%d", &n);
        if(n<1) {
            printf("\nWrong input given!!\n");
            return 0;
        }
    } else {
        printf("\nN is not passed in the command line!!\n");
        exit(0);
    }

    pid = fork();
    if(pid == 0) {
        //This is the child process
        execlp("./odd", "odd", argv[1], NULL);
    } else if(pid > 0) {
        wait(NULL);
        printf("\n[PARENT] Child process completed\n");
        shmid = shm_open("OS", O_RDONLY, 0666);
        ftruncate(shmid, 4096);
        shmptr = mmap(0, 4096, PROT_READ, MAP_SHARED, shmid, 0);
        printf("\nParent Printing:\n");
        printf("%s\n", (char *)shmptr);
        shm_unlink("OS");
    }

    return 0;
}

//with shmget
//child
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/shm.h>
#include<sys/mman.h>

int main(int argc, char *argv[]) {
    int i = 1, n;
    void *shmptr;
    int shmid = shmget((key_t)1122, 4096, 0666);
    shmptr = shmat(shmid, NULL, 0666);

    printf("\nChild Printing:\n");
    n = atoi(argv[1]);

    while(n != 0) {
        if(i%2 != 0) {
            sprintf(shmptr, "%d ", i);
            printf("%d ", i);
            shmptr += strlen(shmptr);
            n--;
        }
        i++;
    }

    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
//parent

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<sys/shm.h>
#include<sys/mman.h>

int main(int argc, char *argv[]) {
    int i, n;
    pid_t pid;
    const int SIZE = 4096;
    void *shmptr;
    int shmid = shmget((key_t)1122, 4096, 0666|IPC_CREAT);
    shmptr = shmat(shmid, NULL, 0666);

    if(argc > 1) {
        sscanf(argv[1], "%d", &i);
        if(i < 1) {
            printf("\nWrong input is passed:\n");
            return 0;
        }
    } else {
        printf("\nN is not passed in the command line\n");
        return 1;
    }

    pid = fork();
    if(pid == 0) {
        //This is the child process part
        execlp("./odd", "odd", argv[1], NULL);
    } else if(pid > 0) {
        wait(NULL);
        printf("\n[PARENT] Child completed\n");
        printf("\nParent printing:\n");
        printf("%s\n", (char *)shmptr);
        shmdt(shmptr); 
    } 

    return 0;
}
