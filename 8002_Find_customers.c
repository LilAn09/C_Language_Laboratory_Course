#include <stdio.h>

// 函数原型声明(函数的具体实现需要你在文件末尾完成)
void find_top_k_index(int *interest, int n, int k, int *top_k_index);

int main() {
    int n;
    scanf("%d", &n);
    int k;
    scanf("%d", &k);
    int interest[100];
    for (int i = 0; i < n; i++) {
        scanf("%d", &interest[i]);
    }
    int top_k_index[100];  // 其长度固定为 100，但实际上只需将返回结果写入到其前 k 个元素即可
    find_top_k_index(interest, n, k, top_k_index);
    for (int i = 0; i < k; i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%d", top_k_index[i]);
    }
    printf("\n");
    return 0;
}

// 你需要实现的函数
void find_top_k_index(int *interest, int n, int k, int *top_k_index) {
    // 请将返回结果写入到 top_k_index 数组中
    // 其长度固定为 100，但实际上只需将返回结果写入到其前 k 个元素即可

    // 请在此处编写代码
    //由于我们最终想得到的是客户的原有序号，所以不要进行交换操作
    int max=0;
    int temp=0;
    for(int p=0;p<k;p++){
        max=p;
        for(int q=0;q<n;q++){//外层循环是在确定第x大的数字
            if(interest[q]>interest[max]){
                max=q;//内层一旦发现更大的数，便马上更新max值
                }
            }
        interest[max]=-1;//不进行交换，而是将max对应的值赋负值，不影响接下来的比较
        top_k_index[p]=max;
    }
    return;
}