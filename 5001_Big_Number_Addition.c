#include <stdio.h>
#include <string.h>
#define MAX_SIZE 51
//函数功能：实现字符串的倒换，方便进行后续操作
//传入参数：传入一个字符串
int Reverse_Order(char str[]){
    char *p,*q,temp;//定义两个指针用于对原字符串进行操作，同时定义一个中间变量
    p=str;//一个指针指向字符串的首位置
    q=str+strlen(str)-1;//另一个指向字符串的末位置
    while(p<q){
        temp=*p;
        *p=*q;
        *q=temp;
        p++;
        q--;
    }
    return 0;
}

int main(){
    char str_1[MAX_SIZE],str_2[MAX_SIZE];
    gets(str_1);//gets()会自动添加\0
    Reverse_Order(str_1);
    gets(str_2);
    Reverse_Order(str_2);//定义两个字符串用于储存位数极多的数字

    char str_3[MAX_SIZE+1];//在定义一个字符串用于存储相加后的数字

    int i=0;
    int quotient=0;//记录进位
    while (str_1[i]!='\0' && str_2[i]!='\0')
    {
        str_3[i]=(str_1[i]-'0'+str_2[i]-'0'+quotient)%10+'0';//记得适时在整数和字符之间转换
        quotient=(str_1[i]-'0'+str_2[i]-'0'+quotient)/10;
        i++;
    }
    if(str_1[i]=='\0' && str_2[i]=='\0'){\
        if(quotient==0){
            str_3[i]='\0';
            Reverse_Order(str_3);
        }else{
            str_3[i]=quotient+'0';
            str_3[i+1]='\0';
            Reverse_Order(str_3);
        }
        
    }else if(str_1[i]=='\0' && str_2[i]!='\0'){
        while (str_2[i]!='\0')
        {
            str_3[i]=(str_2[i]-'0'+quotient)%10+'0';
            quotient=(str_2[i]-'0'+quotient)/10;
            i++;
        }
        if(quotient==0){
            str_3[i]='\0';
            Reverse_Order(str_3);
        }else{
            str_3[i]=quotient+'0';
            str_3[i+1]='\0';
            Reverse_Order(str_3);
        }
    }else{
        while (str_1[i]!='\0')
        {
            str_3[i]=(str_1[i]-'0'+quotient)%10+'0';
            quotient=(str_1[i]-'0'+quotient)/10;
            i++;
        }
        if(quotient==0){
            str_3[i]='\0';
            Reverse_Order(str_3);
        }else{
            str_3[i]=quotient+'0';
            str_3[i+1]='\0';
            Reverse_Order(str_3);//输出前将其倒转
        }  
    }
    puts(str_3);

    return 0;
}