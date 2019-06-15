#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <string.h> 
struct argument  
{  
    int num;  
    char string[30];  
};  
int main()  
{  
    int i,ret;  
    void *thread1_func(void *);  
    void *thread2_func(void *);  
    void *thread_return1,*thread_return2;/*用来接收两个线程退出后的返回值*/  
    pthread_t thread1,thread2;  
    struct argument arg1,arg2;  
    arg1.num=1949;  
    strcpy(arg1.string,"中华人民共和国成立");  
    arg2.num=2009;  
    strcpy(arg2.string,"建国六十周年");  
    pthread_create(&thread1,NULL,thread1_func,(void *)&arg1);  
    pthread_create(&thread2,NULL,thread2_func,(void *)&arg2);  
    for(i=0;i<=2;i++)  
    {  
        printf("我是最初的进程！\n");  
        sleep(2);  
    }  
    ret=pthread_join(thread1,&thread_return1);/*等待第一个线程退出，并接收它的返回值*/  
    if(ret!=0)  
        printf("调用pthread_join获取线程1返回值出现错误！\n");  
    else  
        printf("pthread_join调用成功！线程1退出后带回的值是%d\n",(int)thread_return1);  
    ret=pthread_join(thread2,&thread_return2);/*等待第二个线程退出，并接收它的返回值*/  
    if(ret!=0)  
        printf("调用pthread_join获取线程2返回值出现错误！\n");  
    else  
        printf("pthread_join调用成功！线程2退出后带回的值是%d\n",(int)thread_return2);  
    return 0;  
}  
void *thread1_func(void *arg)  
{  
    int i;  
    struct argument *arg_thread1;/*这里定义了一个指向argument类型结构体的指针arg_thread1，用它来接收传过来的参数的地址*/  
    arg_thread1=(struct argument *)arg;  
    for(i=0;i<=3;i++)  
    {  
        printf("我来自线程1，传递给我的参数是%d,%s。\n",(*arg_thread1).num,(*arg_thread1).string);  
        sleep(2);  
    }  
    return (void *)123;  
}  
void *thread2_func(void *arg)  
{  
    int i;  
    struct argument arg_thread2;/*这里定义了一个argument类型的结构体arg_thread2，用来接收传过来的指针参数指向的值。
                                                                                  这种方法和thread1_func函数中的方法都是可行的*/  
    arg_thread2=*(struct argument *)arg;      
    for(i=0;i<=3;i++)  
    {  
        printf("我来自线程2，传递给我的参数是%d,%s。\n",arg_thread2.num,arg_thread2.string);  
        sleep(2);  
    }  
    return (void *)456;  
} 
