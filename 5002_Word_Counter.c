#include <stdio.h>
#include <string.h>
#define MAX_SIZE 100
//功能：接受指向字符数组的指针，统计不同单词的数量
int counter_word(char(*p)[MAX_SIZE],int n){
    int cnt=0;
    for(int i=0;i<n;i++){
        int is_the_same=0;//用来统计是否存在相同的单词
        for(int j=0;j<i;j++){
            if(strcmp(*(p+i),*(p+j))==0){
                is_the_same=1;
                break;//发现有相同的单词，记录并跳出循环
            }
        }
        if(!is_the_same){
            cnt++;
        }
    }
    return cnt;
}

int main(){
    char word[MAX_SIZE][MAX_SIZE]={0};
    char ch;
    int n=0;
    ch = getchar();
    for(int i=0;i<MAX_SIZE-1;i++){
        int j=0;
        while (!((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))){
        // 遇到回车或输入结束（EOF），直接停止读取
        if (ch == '\n' || ch == EOF) {
            goto END_READ;  // 跳出所有循环，结束读取
        }else{
            ch = getchar();
        }//如果未读到字母，一直持续这个过程（相当于跳过）
    }
        while (1){
            if((ch>='A' && ch<='Z')||(ch>='a' && ch<='z')){
                if(ch>='A' && ch<='Z'){
                    ch=ch+'a'-'A';
                }//大写改为小写
                word[i][j]=ch;
                j++;
            }else{
                break;//如果在读取字母的过程中出现其他符号，则跳出读取循环
            }
        ch=getchar();
        }
        if(j>0){
        word[i][j]='\0';
        n++;
        }//用{0}初始化二维字符数组时，所有未显式赋值的元素都会被默认设为 ASCII 码值为0对应的字符
    }
    END_READ:
    ;//标签必须跟在 “可执行语句” 后面，不能直接跟变量声明。
    char (*p)[MAX_SIZE]=word;
    printf("%d",counter_word(p,n));
    return 0;
}
