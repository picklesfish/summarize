#include<stdio.h>
#include<stdlib.h>
#include"expression.h"

int main()
{
    int a=1;
    while(a==1)
    {
        system("cls");
        output_Window();        //输出窗口
        operation();            //四则运算

        goto_xy(11,21);
        printf("重新计算请按1，否则退出程序:");
        scanf("%d",&a);
        getchar();
    }
    return 0;
}
