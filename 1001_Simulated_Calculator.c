#include <stdio.h>
int main()
{   
	int a=0,b=0;
	int is_correct=1;//状态判断
	char c;
	
	scanf("%d",&a);//读入一个整数（使用scanf可以读入多位数）
	c=getchar();//若键盘输入非整数符号，进入这一步，将该符号保存在c中
	
	while(c!='='){
		scanf("%d",&b);
		
		if(c=='+'){
			a=a+b;
		}else if(c=='-'){
			a=a-b;
		}else if(c=='*'){
			a=a*b;
		}else if(c=='/'){
			a=a/b;
		}else{
			is_correct=0;//若读入非加减乘除的符号，判断状态为不正确并跳出循环
			break;
		}
		
		c=getchar();//在while循环里面更新读到的符号
	}
	
	if(is_correct==1){
		printf("%d",a);
	}else{
		printf("错误的运算符:%c",c);
	}
		 
   	return 0;
}