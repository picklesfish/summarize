#include<windows.h>
#include"queue.h"
int flag;
/**************顺序队列**********************/

//初始化队列
void InitAQueue(AQueue *Q,int flag)
{
    void *Array;
    if(flag == 1)                   //flag标记为1表示数据类型为char型，2为int型
        Q->size=sizeof(char);
    if(flag == 2)
        Q->size=sizeof(int);
    Q->first=0;
    Q->end=0;
    Q->length=MAX;
    Array=malloc((Q->size)*(Q->length));
    Q->array=Array;
}

//销毁队列
void DestroyAQueue(AQueue *Q)
{
    free(Q->array);
    free(Q);
}

//判断是否队列已满
Status IsFullAQueue(const AQueue *Q)
{
    if(Q->end == Q->length)
        return ture;
    return false;
}

//判断是否为空
Status IsEmptyAQueue(const AQueue *Q)
{
    if(Q->first == Q->end)
        return ture;
    return false;
}

//获取队首元素
Status GetHeadAQueue(AQueue *Q,void *e)
{
    if(IsEmptyAQueue(Q))
        return  false;
    void *elemAddr;
    //char型只有一个字节，所以可以将基类型强制转换为char型，
    //再加上相应的长度实现地址的偏移，下面的与此相同
    elemAddr=(char*)(Q->array)+(Q->first)*(Q->size);
    //将指针elemAddr开始的Q->size个字节的数据复制到指针e指向的地址中
    memcpy(e,elemAddr,Q->size);
    return ture;
}

//查看当前队列长度
int LengthAQueue(AQueue *Q)
{
    if((Q == NULL) || IsEmptyAQueue(Q))
        return 0;
    else
        return (Q->end - Q->first);
}

//进队
Status InAQueue(AQueue *Q,void *data)
{
    if(IsFullAQueue(Q))
        return false;
    void *elemAddr;
    elemAddr=(char*)(Q->array)+(Q->end)*(Q->size);
    memcpy(elemAddr,data,Q->size);
    Q->end++;
    return ture;
}

//出队
Status OutAQueue(AQueue *Q,void *data)
{
    if(IsEmptyAQueue(Q))
        return false;
    void *elemAddr;
    elemAddr=(char*)(Q->array)+(Q->first)*(Q->size);
    memcpy(data,elemAddr,Q->size);
    Q->first++;
    return ture;
}

//清空队列
void ClearAQueue(AQueue *Q)
{
    Q->first=0;
    Q->end=0;
}

//遍历队列
Status TraverseAQueue(const AQueue *Q,void (*foo)(AQueue *Q,void *q))
{
    if((Q == NULL) || IsEmptyAQueue(Q))
        return false;
    int i;
    void *elemAddr;
    i=Q->first;
    while(i < Q->end)
    {
        elemAddr=(char*)(Q->array)+i*(Q->size);
        foo(Q,elemAddr);
        i++;
    }
    return ture;
}

void APrint(AQueue *Q,void *q)
{
    int a;
    char b;
    if(Q->size == sizeof(char))
    {
        memcpy(&b,q,Q->size);
        printf("%c\n",b);
    }
    if(Q->size == sizeof(int))
    {
        memcpy(&a,q,Q->size);
        printf("%d\n",a);
    }
}

/***************链式队列*******************/
//初始化队列,根据形参flag决定数据的类型，1为char型。2为int型。
void InitLQueue(LQueue *Q,int flag)
{
    if(flag == 1)
        Q->size=sizeof(char);
    if(flag == 2)
        Q->size=sizeof(int);
    Node *p;
    p=(Node*)malloc(sizeof(Node));
    p->next=NULL;
    p->data=malloc(Q->size);
    Q->front=p;
    Q->rear=p;
    Q->length=0;
}

//销毁链表
void DestroyLQueue(LQueue *Q)
{
    Node *p1,*p2;
    p1=Q->front;
    while(p1!=NULL)
    {
        p2=p1->next;
        free(p1);
        p1=p2;
    }
    free(Q);
}

//判断队列是否为空
Status IsEmptyLQueue(const LQueue *Q)
{
    if(Q->front == Q->rear)
        return ture;
    return false;
}

//查看队首元素
Status GetHeadLQueue(LQueue *Q,void *e)
{
    if(IsEmptyLQueue(Q))
        return false;
    Node *p=Q->front->next;
    memcpy(e,p->data,Q->size);
    return ture;
}

//获取队列长度
int LengthLQueue(LQueue *Q)
{
    if(Q!=NULL)
        return Q->length;
    return 0;
}

//入队
Status EnLQueue(LQueue *Q,void *data)
{
    Node *p;
    p=(Node*)malloc(sizeof(Node));
    p->data=malloc(Q->size);
    if((Q == NULL) || (p == NULL) || (p->data == NULL))
        return false;
    p->next=NULL;
    (Q->rear)->next=p;

    /******
        printf("   ");
        之前p->data没有分配地址，导致memcpy函数出错，可是不知道为什么加了printf以后程序就没有崩，虽然也是错的。
    *******/
    memcpy(p->data,data,Q->size);

    Q->rear=p;
    Q->length++;
    return ture;
}

//出队
Status DeLQueue(LQueue *Q,void *data)
{
    if((Q == NULL) || IsEmptyLQueue(Q))
        return false;
    Node *p=Q->front->next;
    memcpy(data,p->data,Q->size);
    free(Q->front);
    Q->front=p;
    Q->length--;
    return ture;
}

//清空队列
void ClearLQueue(LQueue *Q)
{
    Node *p=Q->front;
    while(Q->front!=Q->rear)
    {
        free(Q->front);
        Q->front=p;
        p=p->next;
    }
    Q->length=0;
}

//遍历队列
Status TraverseLQueue(const LQueue *Q,void (*foo)(LQueue *Q,void *q))
{
    if((Q == NULL) || (IsEmptyLQueue(Q)))
        return false;
    Node *p;
    p=Q->front;
    while(p!=Q->rear)
    {
        p=p->next;
        foo(Q,p->data);
    }
    return ture;
}

void LPrint(LQueue *Q,void *q)
{
    int a;
    char b;
    if(Q->size == sizeof(int))
    {
        memcpy(&a,q,Q->size);
        printf("%d\n",a);
    }
    if(Q->size == sizeof(char))
    {
        memcpy(&b,q,Q->size);
        printf("%c\n",b);
    }
}



