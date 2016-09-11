/*
   头文件说明：单链表实现，函数名后带_WithOutHead表示不带头结点的单链表
   而正常函数名则表示带头结点，事实上更多是带头结点的
*/
#ifndef SINGLE_LINKLIST_H
#define SINGLE_LINKLIST_H
 
#include <stdio.h>
#include <stdlib.h>
 
typedef int DataType;
 
typedef struct Link{
    DataType data;
    struct Link* next;
}*LinkList, LNode;
 
/*
函数原型声明如下：
void InitLinkList(LinkList *l);                     // 初始化
int LinkListLen(LinkList l);                        // 求链表长度
LNode* GetElem(LinkList l, int i);                  // 按序号查找
LNode* LocateElem(LinkList l, DataType e);          // 按值查找
int LinkListInsert(LinkList* l, int i, DataType e); // 插入结点
int LinkListDelete(LinkList* l, int i);             // 删除结点
void ClearLinkList(LinkList *l);                    // 置空链表
void CreateLinkList(LinkList *l, int n);            // 创建链表
void DispLinkList(LinkList l);                      // 输出链表
*/
 
void InitLinkList(LinkList *l){             // 带头结点的初始化方法
    (*l) = (LinkList)malloc(sizeof(LNode));
    (*l) -> next = NULL;
}
 
 
void InitLinkList_WithOutHead(LinkList *l){ // 不带头结点的初始化方法
    (*l) = NULL;
}
 
/*
   函数：LinkListLen()
   功能：求出链表的长度
   输入输出：参数是链表头结点的指针，返回值是链表长度
   变量说明：
*/
int LinkListLen(LinkList l){
    int length = 0;
    LinkList p = l;
 
    while(p -> next){
        length++;
        p = p -> next;
    }
    return length;
}
 
int LinkListLen_WithOutHead(LinkList l){
    int length = 0;
    LinkList p = l;
 
    while(p){
        length++;
        p = p -> next;
    }
    return length;
}
 
/*
   函数：GetElem()
   功能：获取链表序号为i的节点
   输入输出：参数l是链表头结点指针，i是所要获取的节点的序号
   变量说明：
*/
LNode* GetElem(LinkList l, int i){
    int num = 1;
    LinkList p = l -> next;
 
    if(i > LinkListLen(l)){
        printf("所要获取的位置序号大于链表长度，链表长度为%d\n", LinkListLen(l));
        return NULL;
    }
    while(p && num < i){
        p = p -> next;
        num++;
    }
 
    return p;       
}
 
LNode* GetElem_WithOutHead(LinkList l, int i){
    int num = 1;
    LinkList p = l;
 
    if(i > LinkListLen_WithOutHead(l)){
        printf("所要获取的位置序号大于链表长度，链表长度为%d\n", LinkListLen_WithOutHead(l));
        return NULL;
    }
    while(p && num < i){
        p = p -> next;
        num++;
    }
    return p;
}
/*
   函数：LocateElem()
   功能：按值查找
   输入输出：参数l为链表头结点指针，e为要查找的节点数据，返回值是已找到的节点的地址
   变量说明：
*/
LNode* LocateElem(LinkList l, DataType e){
    LinkList p = l;
 
    while(p){
        p = p -> next;
        if(p -> data == e)
            return p;
    }
    return NULL;
}
 
LNode* LocateElem_WithOutHead(LinkList l, DataType e){
    LinkList p = l;
 
    while(p){
        if(p -> data == e)
            return p;
        p = p -> next;
    }
    return NULL;
}
/*
   函数：LinkListInsert()
   功能：在链表中序号为i的位置插入数据为e的节点
   输入输出：参数l为链表头结点指针的地址，i为序号，e为数据，返回值为插入操作的布尔值
   变量说明：
*/
int LinkListInsert(LinkList* l, int i, DataType e){
    LinkList p = (*l);
    LinkList pr = (LinkList)malloc(sizeof(LNode));
    int num = 1;
 
    if(i > LinkListLen(*l) || i < 1){
        printf("要插入的序号位置大于链表长度或小于1，链表长度为%d\n", LinkListLen(*l));
        return 0;
    }
    while(num < i && p -> next){
        num++;
        p = p -> next;
    }
    pr -> data = e;
    pr -> next = p -> next;
    p -> next = pr;
 
    return 1;
}
 
int LinkListInsert_WithOutHead(LinkList *l, int i, DataType e){
    LinkList p = (*l);
    LinkList pr = (LinkList)malloc(sizeof(LNode));
    int num = 1;
 
    if(i > LinkListLen_WithOutHead(*l) || i < 1){
        printf("要插入的序号位置大于链表长度，链表长度为%d\n", LinkListLen_WithOutHead(*l));
        return 0;
    }
    while(num < i - 1 && p){
        num++;
        p = p -> next;
    }
    pr -> data = e;
    pr -> next = p -> next;
    p -> next = pr;
 
    return 1;
}
/*
   函数：LinkListDelete()
   功能：删除链表中序号为i的节点
   输入输出：参数l是链表头结点指针的地址值，i是要删除的节点序号,返回值是删除操作的布尔值
   变量说明：
*/
int LinkListDelete(LinkList* l, int i){
    LinkList p = (*l) -> next;
    LinkList pr = NULL;
    int num = 1;
 
    if(i > LinkListLen(*l)){
        printf("要删除的节点序号大于链表长度了，链表长度为%d\n", LinkListLen(*l));   
        return 0;
    }
    while(num < i - 1 && p){
        p = p -> next;
        num++;
    }
    pr = p -> next;
    p -> next = p -> next -> next;
    free(pr);
 
    return 1;
}
 
int LinkListDelete_WithOutHead(LinkList* l, int i){
    LinkList p = (*l);
    LinkList pr = NULL;
    int num = 1;
 
    if(i > LinkListLen_WithOutHead(*l)){
        printf("要删除的节点序号大于链表长度了，链表长度为%d\n", LinkListLen_WithOutHead(*l));
        return 0;
    }
    while(num < i - 1 && p){
        p = p -> next;
        num++;
    }
    pr = p -> next;
    p -> next = p -> next -> next;
    free(pr);
 
    return 1;
}
/*
   函数：ClearLinkList()
   功能：用于清除链表
   输入输出：参数为链表头结点的指针的地址，无返回值
   变量说明：p用于动态指向链表节点，pr用于释放内存
*/
 
void ClearLinkList(LinkList *l){
    LinkList p = (*l);
    LinkList pr = NULL;
 
    while(p){
        pr = p;
        p = p -> next;
        free(pr);
    }
    (*l) -> next = NULL;
}
 
void ClearLinkList_WithOutHead(LinkList *l){
    LinkList p = (*l);
    LinkList pr = NULL;
 
    while(p){
        pr = p;
        p = p -> next;
        free(pr);
    }
    (*l) = NULL;
}
 
/*
   函数：CreateLinkList()
   功能：创建链表
   输入输出：参数是链表头结点的指针的地址l，和要创建的节点个数n，无返回值
   变量说明：i用于循环语句临时变量，p用于动态指向链表节点，pr用于申请内存空间
*/
 
void CreateLinkList(LinkList *l, int n){
    DataType input_data;
    int i = 0;
    LNode *p = (*l);
    LNode *pr = NULL;
     
    for(i = 0; i < n; i++){
        printf("Now input the %d data :", i);       
        scanf("%d", &input_data);                               // 此处输入数据使用DataType类型
 
        pr = (LinkList)malloc(sizeof(LNode));
        pr -> data = input_data;
        pr -> next = NULL;
        p ->next = pr;
        p = p -> next;
    }
}
 
void CreateLinkList_WithOutHead(LinkList *l, int n){
    DataType input_data;
    int i;
    LinkList p = (*l);
    LinkList pr = NULL;
 
    if(p == NULL){
        printf("Now input the 0 data :");
        scanf("%d", &input_data);
        pr = (LinkList)malloc(sizeof(LNode));
        pr -> data = input_data;
        pr -> next = NULL;
        (*l) = pr;              // 切记此处不应该是p = pr，因为p只是指向*l而不能代表*l
    }
    for(i = 1; i < n; i++){
        printf("Now input the %d data :", i);
        scanf("%d", &input_data);
 
        pr = (LinkList)malloc(sizeof(LNode));
        pr -> data = input_data;
        pr -> next = NULL;
        // 注意这颇为巧妙的2句代码
        p -> next = pr;
        p = p -> next;
    }
}
/*
   函数：DispLinkList()
   功能：输出链表所有元素
   输入输出：参数是链表头结点，无返回值
   变量说明：i用于显示序号，p用于动态指向链表的节点
*/
 
 
void DispLinkList_WithOutHead(LinkList l){
    LinkList p = l;
    int i = 0;
 
    while(p){
        printf("The %d data = %d\n", i++, p -> data);
        p = p -> next;
    }
}
 
void DispLinkList(LinkList l){                          
    LinkList p = l -> next;
    int i = 0;
 
    while(p){
        printf("The %d data = %d\n", i++, p -> data);
        p = p -> next;
    }
}
#endif

