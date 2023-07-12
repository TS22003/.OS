#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
void *Sum(void *arg);
int sum=0;
void *res;
int a[5]={1,2,3,4,5};
void main(int argc, char *argv[])
{
pthread_t T;
pthread_attr_t attr;
pthread_attr_init(&attr);
pthread_create(&T,&attr,*Sum,(void *)a);
pthread_join(T,&res);
printf("Inside Main Thread\n");
printf("Sum = %d\n",sum);
printf("Thread Returned = %s\n",(char *)res);
}

void *Sum(void *param)
{
int i;
int *X = param;
printf("Inside Sum Thread\n");
for(i=0;i<5;i++)
sum+=X[i];
pthread_exit("Sum Thread Completed\n");
}
