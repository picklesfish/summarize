/****************************************************************************************
    File Name               :expression.h
    Author                  :ZhongHuiMing
    Create Date             :2018/4/16
*****************************************************************************************/

/**************************************************************
*	Multi-Include-Prevent Section
**************************************************************/
#ifndef EXPRESSION_H_INCLUDED
#define EXPRESSION_H_INCLUDED

/******************************************************
*   Include File Section
******************************************************/
#include<stdio.h>
#include<stdlib.h>
#include"stack.h"

/******************************************************
*   Struct Define Section
******************************************************/
union number            //表达式用链表来存储，其中数字与字符用共用体来解决
{
    int data;
    char ch;
};

typedef struct expression
{
    union number data;
    int flag;                  //1表示data为数字，2表示为字符
    struct expression *next;
}Expression;

/**********************************************************
*   End-Multi-Include-Prevent Section
***********************************************************/
#endif // EXPRESSION_H_INCLUDED

//输入表达式
void input_Expression(Expression *head);

//输出表达式
void output_Expression(Expression *head);

//将中缀表达式转换成后缀表达式
Expression *transform(Expression*first);

//根据后缀表达式计算结果
void count(Expression *first);

//检查表达式
Status check_Expression(Expression *head);

//检查括号匹配问题
Status check_Bracket(Expression *head);

//四则运算总函数
void operation();

/****为了节省空间，就在这里加入输出要用的函数了****/

//控制光标函数
void goto_xy(int x,int y);

//输出窗口函数
void output_Window();



