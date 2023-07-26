//11.a

//program with two threads and main thread; also passing parameters to child threads
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
void *sum(void *arg);
void *mul(void *arg);
int sm=0, prod=1;
void main(int argc, char * argv[])
{
  pthread_t T1,T2;
  pthread_attr_t attr;//set of thread attributes
  pthread_attr_init(&attr);//get the default attributes
    
  pthread_create(&T1, &attr, sum, argv[1]);
  pthread_create(&T2, &attr, mul, argv[1]);
  pthread_join(T1,NULL);
  pthread_join(T2,NULL);
  
  printf("Inside main thread\n");
  printf("sum=%d\n",sm);
  printf("product=%d\n",prod);
 }
void *sum(void *parm) 
{ 
  int i, n; 
   n = atoi(parm);//string to integer i.e., ASCII to int
  printf("inside  sum thread\n");
  
  for(i=1; i<=n;i++)
  {
    sm+=i;     
  }
 printf("sum thread completed\n");
}
void *mul(void *parm)
{
  int i, n;
  n = atoi(parm);
  printf("inside mul thread\n");
  for(i=2; i<=n;i++)
  {
    prod =prod *i;
  }
  printf("mul thread completed  product\n");
}


//the main thread catching the returned status of child thread

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
void *sum(void *arg);
int a[5]={1,2,3,4,5};
int sm=0;
void *res;
void main()
{
  pthread_t T1;
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_create(&T1, &attr, sum, (void *)a);
  pthread_join(T1,&res);//&res is the pointer to the location where the exit status of the thread mentioned in th is stored
  printf("Inside main thread\n");
  printf("sum=%d\n",sm);
  printf("thread returned: %s\n",(char *)res);
  //pthread_exit(NULL); // main() is blocked and kept alive untill all its thread are done with execution
 }
void *sum(void *parm) 
{ 
  int i; 
  int *x=parm;
   printf("inside thread\n");
   for(i=0;i<5;i++)
    sm+=x[i]; 
      
 pthread_exit("sum calculated"); //a thread is terminated whether its work is done or not 

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
