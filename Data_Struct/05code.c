#include<stdio.h>
#include<pthread.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include <semaphore.h>
 
void* ticketport1(void*);
void* ticketport2(void*);
 
int tickets=100;
sem_t mutex,full;              //定义两个信号量
 
int main()
{
         int ret;
         pthread_t id1,id2;
 
         ret=sem_init(&mutex,0,1);                        //初始化mutex信号量为1
         ret+=sem_init(&full,0,0);                            //初始化full信号量为0
         if(ret!=0)
         {
                   perror("sem_init");
         }
         ret=pthread_create(&id1,NULL,ticketport1,NULL);
         if(ret<0)
         {
                   perror("creat thread1:");
                   exit(-1);
         }
         ret=pthread_create(&id2,NULL,ticketport2,NULL);
         if(ret<0)
         {
                   perror("creat thread2:");
                   exit(-1);
         }
        
         pthread_join(id1,NULL);
         pthread_join(id2,NULL);
         return 0;
}
 
void* ticketport1(void* arg)
{
         while(1)
         {
                   sem_wait(&mutex);                  //mutex信号量进行P操作
                   if(tickets>0)
                   {
                            usleep(1000);
                            printf("thread1 sell ticket: %d\n",tickets--);
                            sem_post(&full);                //full信号量进行V操作
                   }
                   else
                   {
                            sem_post(&full);                //full信号量进行V操作
                            break;
                   }
                  
         }
         return (void*)0;
}
 
void* ticketport2(void* arg)
{
         while(1)
         {
                   sem_wait(&full);               //full信号量进行P操作
                   if(tickets>0)
                   {
                            usleep(1000);
                            printf("thread2 sell ticket: %d\n",tickets--);
                            sem_post(&mutex);         //mutex信号量进行V操作
                   }
                   else
                   {
                            sem_post(&mutex);         //mutex信号量进行V操作
                            break;
                   }
                  
         }
         return (void*)0;
}
