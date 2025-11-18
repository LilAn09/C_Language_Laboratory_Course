#include <stdio.h>

int is_leap_year(int year){
    if((year%4 == 0&&year%100 != 0)||(year%400 == 0)){
        return 1;
    }else{
        return 0;
    }
}//判断闰年的函数

int main(){
    int year,month,day,time=0;

    int is_correct=1;//判断输入是否正确

    int i=0,j=0,k=0;
    int day_of_month[]={0,31,28,31,30,31,30,31,31,30,31,30,31};/*将平年
    的各月份日期读入*/

    scanf("%4d-%2d-%2d",&year,&month,&day);
    if(is_leap_year(year)==1){
        day_of_month[2]=day_of_month[2]+1;
    }//后续循环不涉及year这一年，所以单独判断
    if(year<1990||month>12||day>day_of_month[month]){
        is_correct=0;
    }//若读入的数据不正确，更新其状态

    if(is_correct==0){
        printf("Invalid input");
    }else{    
    for(i=1990;i<=(year-1);i++){
        time=time+365+is_leap_year(i);
    }//先把year之前过的整年日期加上

    for(j=1;j<=(month-1);j++){
        time=time+day_of_month[j];

    }//再把month之前过的整月日期加上

    time=time+day-1;//在加上日（注意要减一，可以举例自己判断）

    if((time%5)<=3 && (time%5)>=1){
        printf("working");
    }else{
        printf("rest");
    }//通过判断余数来确定工作状态
}
    return 0;
}