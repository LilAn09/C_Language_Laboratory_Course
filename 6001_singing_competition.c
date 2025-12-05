#include <stdio.h>
#define MAX_SIZE 100
//函数功能：找到某数组内的最大值
//传入参数：记录的数据个数和数组
int MAX(int m,int nums[]){
    int max=nums[0];
    for(int i=1;i<m;i++){
        if(nums[i]>max){
            max=nums[i];
        }
    }
    return max;
}
//函数功能：找到某数组内的最小值
//传入参数：记录的数据个数和数组
int MIN(int m,int nums[]){
    int min=nums[0];
    for(int i=1;i<m;i++){
        if(nums[i]<min){
            min=nums[i];
        }
    }
    return min;
}

typedef struct score{
    double average_score;
}AVERAGE_SCORE;



int main(){
    int n=0,m=0;
    scanf("%d",&n);
    scanf("%d",&m);
    if (m <= 2) {
        printf("failed\n");
        return 1;
    }
    int sum=0;
    int players_score[MAX_SIZE][MAX_SIZE]={0};
    AVERAGE_SCORE average_score[MAX_SIZE]={0};
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d",&players_score[i][j]);
        }
    }

    for(int i=0;i<n;i++){
        sum=0;
        for(int j=0;j<m;j++){
            sum+=players_score[i][j];
        }
        sum=sum-MAX(m,players_score[i])-MIN(m,players_score[i]);/*对于二维数组，其行数组可以看作数组名进行调用，或者说每一行数组都是一个
                                                                一维数组*/
        average_score[i].average_score=(double)sum/(m-2);
    }

    int winner=0;
    int k=0;
    for(k=1;k<n;k++){
        if(average_score[k].average_score>=average_score[winner].average_score){
            winner=k;
        }
    }
    printf("%.2f",average_score[winner].average_score);
    return 0;
}