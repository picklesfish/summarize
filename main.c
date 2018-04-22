#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"queue.h"

int main()
{
    int i,x,flag;
    char ch1,ch2='a';
    flag=1;
    AQueue *Q1,*Q2;
    Q1=(AQueue*)malloc(sizeof(AQueue));
    Q2=(AQueue*)malloc(sizeof(AQueue));

    LQueue *Q3,*Q4;
    Q3=(LQueue*)malloc(sizeof(LQueue));
    Q4=(LQueue*)malloc(sizeof(LQueue));

    /************************/
    printf("\n字符型顺序队列\n");
    InitAQueue(Q1,flag);
    void (*foo1)(AQueue *Q,void *q);
    foo1=&APrint;
    for(i=0;i<10;i++)
    {
        ch1=ch2+i;
        InAQueue(Q1,&ch1);
    }
    TraverseAQueue(Q1,foo1);

    /************************/
    printf("\n字符型链式队列\n");
    InitLQueue(Q3,flag);
    void (*foo3)(LQueue *Q,void *q);
    foo3=&LPrint;
    for(i=0;i<10;i++)
    {
        ch1=ch2+i;
        EnLQueue(Q3,&ch1);
    }
    TraverseLQueue(Q3,foo3);

    /****************************/
    flag=2;
    printf("\n整型顺序队列\n");
    InitAQueue(Q2,flag);
    void (*foo2)(AQueue *Q,void *q);
    foo2=&APrint;
    for(i=0;i<10;i++)
    {
        InAQueue(Q2,&i);
    }
    TraverseAQueue(Q2,foo1);

    /***************************/
    printf("\n整型链式队列\n");
    InitLQueue(Q4,flag);
    void (*foo4)(LQueue *Q,void *q);
    foo4=&LPrint;
    for(i=0;i<10;i++)
    {
        EnLQueue(Q4,&i);
    }
    TraverseLQueue(Q4,foo4);

    getchar();
    return 0;
}






