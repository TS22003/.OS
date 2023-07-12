//11.a

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
//factorial

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
void *Sum(void *arg);
void *Fact(void *arg);
int sum=0,fact=1;
void main(int argc, char *argv[])
{
pthread_t T1,T2;
pthread_attr_t attr;
pthread_attr_init(&attr);
pthread_create(&T1,&attr,*Sum,argv[1]);
pthread_create(&T2,&attr,*Fact,argv[1]);
pthread_join(T1,NULL);
pthread_join(T2,NULL);
printf("Inside Main Thread\n");
printf("Sum = %d\n",sum);
printf("Factorial = %d\n",fact);
}

void *Sum(void *param)
{
int i,n;
n=atoi(param);
printf("Inside Sum Thread\n");
for(i=1;i<=n;i++)
sum+=i;
printf("Sum Thread Completed\n");
}

void *Fact(void *param)
{
int i,n;
n=atoi(param);
printf("Inside Factorial Thread\n");
for(i=2;i<=n;i++)
fact*=i;
printf("Factorial Thread Completed\n");
}

//  Solution for producer-consumer problem using mutex and semaphore. 5 producers and 5 consumers are used to demonstrate the solution.


#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#define MaxItems 5 // Maximum items a producer can produce or a consumer can consume
#define BufferSize 5 // Size of the buffer

sem_t empty;
sem_t full;
int in = 0;
int out = 0;
int buffer[BufferSize];
pthread_mutex_t mutex;

void *producer(void *pno)
{   
    int item;
    for(int i = 0; i < MaxItems; i++) {
        item = rand(); // Produce an random item
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = item;
        printf("Producer %d: Insert Item %d at %d\n", *((int *)pno),buffer[in],in);
        in = (in+1)%BufferSize;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}
void *consumer(void *cno)
{   
    for(int i = 0; i < MaxItems; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int item = buffer[out];
        printf("Consumer %d: Remove Item %d from %d\n",*((int *)cno),item, out);
        out = (out+1)%BufferSize;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}
int main()
{   

    pthread_t pro[5],con[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty,0,BufferSize);
    sem_init(&full,0,0);

    int a[5] = {1,2,3,4,5}; //Just used for numbering the producer and consumer

    for(int i = 0; i < 5; i++) {
        pthread_create(&pro[i], NULL, (void *)producer, (void *)&a[i]);
    }
    for(int i = 0; i < 5; i++) {
        pthread_create(&con[i], NULL, (void *)consumer, (void *)&a[i]);
    }

    for(int i = 0; i < 5; i++) {
        pthread_join(pro[i], NULL);
    }
    for(int i = 0; i < 5; i++) {
        pthread_join(con[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
  }  
