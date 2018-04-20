#include<windows.h>
#include"expression.h"
#include"stack.h"

//输入表达式,将表达式存储到形参head的链表中去
void input_Expression(Expression *head)
{
    Expression *p;
    char s[100];
    int i=0,num=0;
    p=(Expression*)malloc(sizeof(Expression));
    head->next=p;

    goto_xy(11,5);
    gets(s);
    while((s[i]>='0') && (s[i]<='9'))   //操作数可能是两位数甚至更多，假设数值都比较小，计算以后也不会溢出
    {
        num=num*10+s[i++]-'0';
    }
    if(num!=0)
    {

        p->data.data=num;
        p->flag=1;
    }
    else                              //第一个字符可能不是数字而是左括号，其他情况先不讨论
    {

        p->data.ch=s[i++];
        p->flag=2;
    }


    while(s[i]!='\0')
    {
        num=0;
        p=p->next=(Expression*)malloc(sizeof(Expression));
        while((s[i]>='0') && (s[i]<='9'))
        {
            num=num*10+s[i++]-'0';
        }
        if(num!=0)
        {
            p->data.data=num;
            p->flag=1;
        }
        else
        {
            p->data.ch=s[i++];
            p->flag=2;
        }
    }
    p->next=NULL;
}

//输出表达式，将形参head表示的链表里的表达式输出
void output_Expression(Expression *head)
{
    head=head->next;
    while(head!=NULL)
    {
        if(head->flag == 1)
            printf("%d",head->data.data);
        if((head->flag == 2) && (head->data.ch!='#'))
            printf("%c",head->data.ch);
        head=head->next;
    }
}

//检查表达式
Status check_Expression(Expression *head)
{
    Expression *p1,*p2;
    p1=head;
    p1=p1->next;
    while(p1)
    {
        p2=p1->next;
        if((p2!=NULL) && (p1->flag == 2) && p2->flag == 2)
        {
            if((p1->data.ch!='(') && (p1->data.ch!=')'))
                if((p2->data.ch!='(') && (p2->data.ch!=')'))            //两个操作符连续又不包含括号的的话则错误
                    return false;
        }
        p1=p2;
    }
    return ture;
}

//检查括号匹配
Status check_Bracket(Expression *head)
{
    char ch;
    Expression *p=head;
    SqStack *S;
    S=(SqStack*)malloc(sizeof(SqStack));
    initStack(S,10);
    while(p!=NULL)
    {
        if(p->flag == 2)
        {
            if(p->data.ch == '(')
                pushStack(S,p->data.ch);
            if(p->data.ch == ')')
            {
                if(popStack(S,&ch) == false)            //右括号多于左括号的时候
                    return false;
            }
        }
        p=p->next;
    }
    if(isEmptyStack(S))                                 //若栈不为空，则左括号多于右括号
        return ture;
    else
        return false;
}


//将中缀表达式转换成后缀表达式，形参head里的是中缀表达式，返回值为后缀表达式的链表头指针
Expression *transform(Expression *head)
{
    if(head == NULL)
        return NULL;
    char ch1,ch2,ch3;

    Expression *p,*first;                           //创建链表存放后缀表达式
    first=(Expression*)malloc(sizeof(Expression));
    p=(Expression*)malloc(sizeof(Expression));
    first->next=p;
    if(head->flag == 1)                             //将中缀表达式的第一个内容放到后缀表达式中
    {
        p->data.data=head->data.data;
    }
    else
    {
        p->data.ch=head->data.ch;
    }
    p->flag=head->flag;
    head=head->next;


    SqStack *Operator;                              //存放操作符的栈
    Operator=(SqStack*)malloc(sizeof(SqStack));
    initStack(Operator,30);
    pushStack(Operator,'#');


    while(head!=NULL)
    {
        if(head->flag == 1)                                     //flag为1表示内容为操作数，为2表示内容为操作符
        {
            p=p->next=(Expression*)malloc(sizeof(Expression));
            p->data.data=head->data.data;
            p->flag=head->flag;
        }
        if(head->flag == 2)
        {
            ch1=head->data.ch;
            if(ch1 == '(')
                pushStack(Operator,ch1);
            if(ch1 == ')')
            {
                popStack(Operator,&ch2);
                while(ch2!=')')
                {
                    p=p->next=(Expression*)malloc(sizeof(Expression));
                    p->data.ch=ch2;
                    p->flag=2;
                    popStack(Operator,&ch2);
                }
            }
            getTopStack(Operator,&ch2);
            if((ch1 == '+') || (ch1 == '-'))
            {
                if((ch2 == '#') || (ch2 == '('))
                    pushStack(Operator,ch1);
                else
                {
                    popStack(Operator,&ch3);
                    p=p->next=(Expression*)malloc(sizeof(Expression));
                    p->data.ch=ch3;
                    p->flag=2;

                    getTopStack(Operator,&ch2);
                    if((ch2!='#') && (ch2!='('))
                    {
                        popStack(Operator,&ch3);
                        p=p->next=(Expression*)malloc(sizeof(Expression));
                        p->data.ch=ch3;
                        p->flag=2;
                    }
                    pushStack(Operator,ch1);
                }
            }
            if((ch1 == '*') || (ch1 == '/'))
            {
                if((ch2 == '*') || (ch2 == '/'))
                {
                    popStack(Operator,&ch3);
                    p=p->next=(Expression*)malloc(sizeof(Expression));
                    p->data.ch=ch3;
                    p->flag=2;
                    pushStack(Operator,ch1);
                }
                else
                    pushStack(Operator,ch1);
            }

        }
        head=head->next;
    }
    while(!isEmptyStack(Operator))
    {
        popStack(Operator,&ch2);
        p=p->next=(Expression*)malloc(sizeof(Expression));
        p->data.ch=ch2;
        p->flag=2;
    }
    p->next=NULL;
    return first;
}

//根据后缀表达式计算结果并输出
void count(Expression *first)
{
    LinkStack *Operand;                             //存放操作数的栈
    Operand=(LinkStack*)malloc(sizeof(LinkStack));
    initLStack(Operand);
    int result=0;
    int a,b;
    while(first!=NULL)
    {
        if(first->flag == 1)
            pushLStack(Operand,first->data.data);
        if(first->flag == 2)
        {
            popLStack(Operand,&a);
            popLStack(Operand,&b);
            switch(first->data.ch)
            {
                case '-':result=b-a;
                         break;
                case '+':result=b+a;
                         break;
                case '*':result=b*a;
                         break;
                case '/':result=b/a;
                         break;
                case '#':break;
            }
            pushLStack(Operand,result);
        }
        first=first->next;
    }
    popLStack(Operand,&result);
    goto_xy(11,13);
    printf("计算结果为：%d",result);
}


//四则运算
void operation()
{
    int flag=0;                                     //用来标记表达式是否错误
    Expression *head,*first;
    head=(Expression*)malloc(sizeof(Expression));
    input_Expression(head);                          //输入中缀表达式
    if((check_Bracket(head) == false) || (check_Expression(head) == false))     //表达式错误
    {
        flag=1;
        goto_xy(12,12);
        printf("表达式输入错误，请重新输入！");
        Sleep(1000);
        system("cls");
        output_Window();
        goto_xy(11,11);
        printf("你刚才输入的表达式为：");
        output_Expression(head);
        goto E;                                     //使用goto语句是防止递归调用回溯后再次输出原表达式
    }
    first=transform(head);                          //中中缀表达式转换为后缀表达式
    goto_xy(11,12);
    printf("后缀表达式为：");
    output_Expression(first);                       //输出表达式
    count(first);                                   //根据后缀表达式计算结果

    E:if(flag == 1)
        operation();
}


//控制光标函数，使光标跳转到（X，Y）坐标上
void goto_xy(int x,int y)
{
    HANDLE hOut;
    COORD pos={0,0};
    hOut=GetStdHandle(STD_OUTPUT_HANDLE);
    pos.X=x;
    pos.Y=y;
    SetConsoleCursorPosition(hOut,pos);
}

//输出窗口函数
void output_Window()
{
    int i;
    goto_xy(10,3);
    printf("____________________________________________________________");
    goto_xy(10,15);
    printf("____________________________________________________________");
    goto_xy(10,22);
    printf("____________________________________________________________");
    for(i=4;i<=22;i++)
    {
        goto_xy(10,i);
        printf("$");
        goto_xy(69,i);
        printf("$");
    }
    goto_xy(30,2);
    printf("利用栈进行的四则运算");
    goto_xy(11,4);
    printf("请在这里输入你要计算的四则运算表达式:");
    goto_xy(11,16);
    printf("你可以使用的运算符为： +  -  *  /  (   )");
    goto_xy(13,17);
    printf("#注意#： 如果你输入其他字符，系统会将它丢弃；或者你没有");
    goto_xy(11,18);
    printf("输入有效运算符的话，运算结果可能会出错。");
    goto_xy(11,19);
    printf("运算数的范围：（-1000，1000）");
    goto_xy(11,20);
    printf("表达式输入结束后请按回车键");
    goto_xy(55,23);
    printf("作者：钟惠明");
}


