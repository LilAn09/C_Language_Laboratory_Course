#include <stdio.h>

// 函数原型声明(函数的具体实现需要你在文件末尾完成)
void sort_interest(int *interest, int n);

int main() {
    int n;
    scanf("%d", &n);
    int interest[100];
    for (int i = 0; i < n; i++) {
        scanf("%d", &interest[i]);
    }
    sort_interest(interest, n);
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%d", interest[i]);
    }
    printf("\n");
    return 0;
}

// 你需要实现的函数
void sort_interest(int *interest, int n) {
    int is_exchange;
    int temp=0;
    for(int i=0;i<n-1;i++){
        is_exchange=0;
        for(int j=0;j<n-i-1;j++){
            if(*(interest+j)<*(interest+j+1)){
                temp=*(interest+j);
                *(interest+j)=*(interest+j+1);
                *(interest+j+1)=temp;
                is_exchange=1;
            }
        }
        if(is_exchange==0){
            break;
        }
    }
    return ;
}