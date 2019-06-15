#include<stdio.h>
#include<pthread.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
void* ticketport1(void*);
void* ticketport2(void*);
int tickets=100;
pthread_mutex_t mutex;                 
pthread_cond_t  qready=PTHREAD_COND_INITIALIZER;             //静态初始化条件变量;
int main()
{
         int ret;
         pthread_t id1,id2;
         pthread_mutex_init(&mutex,NULL);                                  //初始化互斥量
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
}
 
void* ticketport1(void* arg)
{
         pthread_mutex_lock(&mutex);                //给互斥量上锁
         while(tickets > 0)
         {
                   if(tickets%2 == 1)
                   {
                            usleep(1000);
                            printf("thread1 sell ticket: %d\n",tickets--);
                            pthread_cond_signal(&qready);      //条件改变，发送信号，通知ticketport2
                   }
                  else
                   {
                            pthread_cond_wait(&qready,&mutex);    //解开mutex,并等待qready改变
                   }
                   pthread_mutex_unlock(&mutex);            //给互斥量解锁
         }
         return (void*)0;
}
 
void* ticketport2(void* arg)
{
         pthread_mutex_lock(&mutex);                //给互斥量上锁
         while(tickets > 0)
         {
                   if(tickets%2==0)
                  {
                            usleep(1000);
                            printf("thread2 sell ticket: %d\n",tickets--);
                            pthread_cond_signal(&qready);      //条件改变，发送信号，通知ticketport1
                   }
                   else
                   {
                            pthread_cond_wait(&qready,&mutex);   //解开mutex,并等待qready改变
                   }
                   pthread_mutex_unlock(&mutex);            //给互斥量解锁
         }
         return (void*)0;
}
