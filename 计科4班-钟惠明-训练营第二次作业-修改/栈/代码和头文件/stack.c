#include"expression.h"
#include"stack.h"

/*************************************顺序栈(基于数组的)******************************************/

Status initStack(SqStack *s,int sizes)  //初始化栈
{
    ElemType *Array;
    Array=(ElemType*)malloc(sizeof(ElemType)*sizes);
    if((s == NULL) || (Array == NULL))
        return false;
    s->array=Array;
    s->top=-1;
    s->size=sizes;
    return ture;
}


Status isEmptyStack(SqStack *s)     //判断栈是否为空
{
    if(s->top == -1)
        return ture;
    else
        return false;
}


Status IsFullStack(SqStack *s)      //判断栈是否已满
{
    if(s->top+1 == s->size)
        return ture;
    else
        return false;
}

Status getTopStack(SqStack *s ,ElemType *e)   //得到栈顶元素
{
    if((s == NULL) || isEmptyStack(s))
        return false;
    *e=s->array[s->top];
    return ture;
}


Status clearStack(SqStack *s)   //清空栈
{
    if(s == NULL)
        return false;
    s->top=-1;
    return ture;
}


Status destoryStack(SqStack *s)  //销毁栈
{
    if(s == NULL)
        return false;
    free(s->array);
    free(s);
    return ture;
}

Status stackLength(SqStack *s,int *length)   //检测栈长度
{
    if(s == NULL)
        return false;
    *length=s->top;
    return ture;
}

Status pushStack(SqStack *s,ElemType datas)  //入栈
{
    if(s == NULL)
        return false;
    if(IsFullStack(s))                      //若栈满，则重新开辟一个比原来数组大一倍的新数组，并将栈的数据都放到新的数组里，再把数组放到栈中
    {
        ElemType *Array;
        int i;
        Array=(ElemType*)malloc(sizeof(ElemType)*(s->size)*2);
        if(Array == NULL)                   //若开辟空间失败，则栈满，返回；
            return false;
        for(i=0;i<s->size;i++)              //数据传送到新数组里
            Array[i]=s->array[i];
        free(s->array);                     //释放原数组
        s->array=Array;
        s->size=(s->size)*2;                //相应的栈长度也要改变
        printf("\n%d\n\n",s->size);
    }
    s->array[++s->top]=datas;
    return ture;
}

Status popStack(SqStack *s,ElemType *datas)   //出栈
{
    if((s == NULL) || IsFullStack(s))
        return false;
    *datas=s->array[s->top--];
    return ture;
}


/******************************************链栈(基于链表的)**********************************/

Status initLStack(LinkStack *s)   //初始化
{
    StackNode *head;
    head=(StackNode*)malloc(sizeof(StackNode));
    if((s == NULL) || (head == NULL))
    {
        return false;
    }
    head->next=NULL;
    s->head=head;
    s->length=0;
    return ture;
}

Status isEmptyLStack(LinkStack *s)  //判断栈是否为空
{
    if((s->length == 0) || (s->head)->next == NULL)
        return ture;
    else
        return false;
}

Status getTopLStack(LinkStack *s,dataType *e)  //得到栈顶元素
{
    if((s == NULL) || isEmptyLStack(s))
        return false;
    StackNode *head,*p;
    head=s->head;
    p=head->next;
    *e=p->data;
    return ture;
}

Status clearLStack(LinkStack *s)   //清空栈
{
    if(s == NULL)
        return false;
    StackNode *head,*p;
    head=s->head;                   //栈顶指针并没有存放数据，故清空的时候不用释放

    head=head->next;
    p=head->next;
    while(head!=NULL)
    {
        free(head);
        head=p;
        p=head->next;
    }
    return ture;
}


Status destoryLStack(LinkStack *s)   //销毁栈
{
    if(s == NULL)
        return false;
    StackNode *head,*p;
    head=s->head;
    while(head!=NULL)
    {
        p=head->next;
        free(head);
        head=p;
    }
    free(s);                            //与上面清空不同，这里销毁还需要把栈结构释放掉
    return ture;
}

Status LStackLength(LinkStack *s,int *length)    //检测栈长度
{
    if(s == NULL)
        return false;
    *length=s->length;
        return ture;
}

Status pushLStack(LinkStack *s,dataType datas)   //入栈
{
    StackNode *head,*p;
    p=(StackNode*)malloc(sizeof(StackNode));
    if((s == NULL) || (p == NULL))              //p为空表示内存不足，此时栈满
        return false;
    head=s->head;
    p->data=datas;
    p->next=head->next;                    //头插法进栈，栈顶指针里不存放数据
    head->next=p;

    s->length++;
    return ture;
}

Status popLStack(LinkStack *s,dataType *datas)   //出栈
{
    if((s == NULL) || isEmptyLStack(s))
        return false;
    StackNode *head,*p;
    head=s->head;
    p=head->next;
    *datas=p->data;
    head->next=p->next;
    free(p);
    return ture;
}

int testLStack()           //测试链栈
{
    LinkStack *MyStack;
    MyStack=(LinkStack*)malloc(sizeof(LinkStack));
    int i,x;
    initLStack(MyStack);
    for(i=0;i<20;i++)
    {
        pushLStack(MyStack,i);
    }
    for(i=0;i<20;i++)
    {
        popLStack(MyStack,&x);
        printf("%d\n",x);
    }
    return 0;
}

int testStack()             //测试顺序栈
{
    SqStack *head;
    head=(SqStack*)malloc(sizeof(SqStack));
    initStack(head,10);
    int i;
    char x;
    char ch='b';
    for(i=1;i<20;i++)
    {
        pushStack(head,ch);
    }
    for(i=1;i<20;i++)
    {
        popStack(head,&x);
        printf("%c\n",x);
    }
    return 0;
}


