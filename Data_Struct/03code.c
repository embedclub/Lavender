/* 头文件 */
#include<stdio.h>
#include<pthread.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>

void* ticketport1(void*);//线程函数声明
void* ticketport2(void*);//线程函数声明
signed int tickets=100;         //火车票的起始值


int main(void)
{
         pthread_t id1,id2;
         int ret;
         ret=pthread_create(&id1,NULL,ticketport1,NULL);       //创建线程1
         if(ret<0)
         {
                   perror("creat thread1:");
                   exit(-1);
         }
         ret=pthread_create(&id2,NULL,ticketport2,NULL);       //创建线程2
         if(ret<0)
         {
                   perror("creat thread2:");
                   exit(-1);
         }
         pthread_join(id1,NULL);                    //等待线程1结束
         pthread_join(id2,NULL);                    //等待线程2结束
         return  0;
}
 
void* ticketport1(void* arg)
{
         while(1)
         {
                   if(tickets>0)
                   {
                            //usleep(1000);
                            //售票点1每卖一张票，自减一
                            printf("ticketport1 sells ticket: %d\n",tickets--);    
                   }
                   else
                   {
                            break;
                   }
         }
         return (void*)0;
}
 
void* ticketport2(void* arg)
{
         while(1)
         {
                   if(tickets>0)
                   {
                            //usleep(1000);
                            //售票点2每卖一张票，自减一
                            printf("ticketport2 sells ticket: %d\n",tickets--);
                   }
                   else
                   {
                            break;
                   }
         }
         return (void*)0;
}
