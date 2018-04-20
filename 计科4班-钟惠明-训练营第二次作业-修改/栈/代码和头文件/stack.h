/****************************************************************************************
    File Name               :stack.h
    Author                  :ZhongHuiMing
    Create Date             :2018/4/16
*****************************************************************************************/


/**************************************************************
*	Multi-Include-Prevent Section
**************************************************************/
#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

/******************************************************
*   Include File Section
******************************************************/
#include <stdio.h>
#include<stdlib.h>

/*******************************************************
*   Macro Define Section
*******************************************************/
#define ElemType char                   //下面顺序栈元素类型为char型，链式栈元素类型为int型
#define dataType int

/******************************************************
*   Struct Define Section
******************************************************/
typedef enum
{
    false,
    ture
}Status;

/***顺序栈用到的结构体***/
typedef struct stack
{
    ElemType *array;        //存放栈的数组
    int top;                //栈顶指针
    int size;               //长度
}SqStack;

/***链式栈用到的结构体***/
typedef struct StackNode
{
    dataType data;
    struct StackNode *next;
}StackNode;

typedef struct ListStack
{
    StackNode *head;             //栈顶指针，里面不存放数据
    int length;
}LinkStack;

/**********************************************************
*   End-Multi-Include-Prevent Section
***********************************************************/
#endif // STACK_H_INCLUDED


/************顺序栈(基于数组的)，元素类型为char****************************/


Status initStack(SqStack *s,int sizes);  //初始化栈，形参sizes为栈的长度


Status isEmptyStack(SqStack *s);     //判断栈是否为空


Status IsFullStack(SqStack *s);      //判断栈是否已满


Status getTopStack(SqStack *s ,ElemType *e);   //得到栈顶元素


Status clearStack(SqStack *s);   //清空栈


Status destoryStack(SqStack *s);  //销毁栈


Status stackLength(SqStack *s,int *length);   //检测栈长度


Status pushStack(SqStack *s,ElemType datas);  //入栈


Status popStack(SqStack *s,ElemType *datas);   //出栈


/**********************链栈(基于链表的),元素类型为int****************************/

Status initLStack(LinkStack *s);   //初始化


Status isEmptyLStack(LinkStack *s); //判断栈是否为空


Status getTopLStack(LinkStack *s,dataType *e);  //得到栈顶元素


Status clearLStack(LinkStack *s);   //清空栈


Status destoryLStack(LinkStack *s) ;  //销毁栈


Status LStackLength(LinkStack *s,int *length);    //检测栈长度


Status pushLStack(LinkStack *s,dataType datas);   //入栈


Status popLStack(LinkStack *s,dataType *datas);   //出栈

//下面两个函数为栈测试
int testLStack();          //测试链式栈

int testStack();            //测试顺序栈


