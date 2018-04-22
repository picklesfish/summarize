/*******************************************************************************************
*   File Name               :           queue.h
*   SYSTEM                  :           win10
*   create Data             :           2018.4.21
*
*******************************************************************************************/
/**************************************************************
*	Multi-Include-Prevent Section
**************************************************************/
#ifndef QUEUE_H_INCLUDE
#define QUEUE_H_INCLUDE

/******************************************************
*   Include File Section
******************************************************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
/*******************************************************
*   Macro Define Section
*******************************************************/
#define MAX 100
/******************************************************
*   Struct Define Section
******************************************************/
//顺序队列结构体
typedef struct queue
{
    void *array;            //数据域
    int first;
    int end;
    int length;             //队列的长度
    int size;               //数据域内存的大小
}AQueue;

typedef enum
{
    false,
    ture
}Status;

/****************************链式队列结构体****************************/
typedef struct node
{
    void *data;
    struct node *next;
}Node;

typedef struct Lqueue
{
    Node *front;
    Node *rear;
    int length;             //队列的长度
    int size;               //数据域内存的大小
}LQueue;

/**********************************************************
*   End-Multi-Include-Prevent Section
***********************************************************/
#endif // QUEUE_H_INCLUDE

/*****************************顺序队列******************************/
//初始化队列,根据形参flag决定数据的类型，1为char型。2为int型。
void InitAQueue(AQueue *Q,int flag);

//销毁队列
void DestoryAQueue(AQueue *Q);

//判断是否队列已满
Status IsFullAQueue(const AQueue *Q);

//判断是否为空
Status IsEmptyAQueue(const AQueue *Q);

//获取队首元素
Status GetHeadAQueue(AQueue *Q,void *e);

//进队
Status InAQueue(AQueue *Q,void *data);

//出队
Status OutAQueue(AQueue *Q,void *data);

//清空队列
void ClearAQueue(AQueue *Q);

//遍历队列
Status TraverseAQueue(const AQueue *Q,void (*foo)(AQueue *Q,void *q));

void APrint(AQueue *Q,void *q);

/*******************链式队列***********************/
//初始化队列,根据形参flag决定数据的类型，1为char型。2为int型。
void InitLQueue(LQueue *Q,int flag);

//销毁链表
void DestroyLQueue(LQueue *Q);

//判断队列是否为空
Status IsEmptyLQueue(const LQueue *Q);

//查看队首元素
Status GetHeadLQueue(LQueue *Q,void *e);

//获取队列长度
int LengthLQueue(LQueue *Q);

//入队
Status EnLQueue(LQueue *Q,void *data);

//出队
Status DeLQueue(LQueue *Q,void *data);

//清空队列
void ClearLQueue(LQueue *Q);

//遍历队列
Status TraverseLQueue(const LQueue *Q,void (*foo)(LQueue *Q,void *q));

//操作函数
void LPrint(LQueue *Q,void *q);






