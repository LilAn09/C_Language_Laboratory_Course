#include <stdio.h>
//函数功能：通过递归计算玩家1选择首尾的数之后最终与玩家2的分差
//参数：nums是读入的数组，left是数组的首位置，right是数组的末位置
int dfs(int nums[],int left,int right){
    int choose_left=0,choose_right=0;

    if(left>right){
        return 0;
    }else{
        choose_left=nums[left]-dfs(nums,left+1,right);
        choose_right=nums[right]-dfs(nums,left,right-1);
    }
        return choose_left>choose_right?choose_left:choose_right;//判断更大分差（玩家1减玩家2）并返回
}

int main(){
    int n;
    scanf("%d",&n);

    int nums[n];
    
    int i=0;
    for(i=0;i<n;i++){
        scanf("%d",&nums[i]);
    }//读入数组

    int left=0,right=n-1;//通过left和right实时更新数组
    if(dfs(nums,0,n-1)>=0){
        printf("true");
    }else{
        printf("false");
    }


    return 0;
}