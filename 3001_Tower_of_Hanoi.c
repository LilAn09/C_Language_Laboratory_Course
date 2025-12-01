#include <stdio.h>
void A_to_C(int n);
void A_to_B(int n);
void B_to_C(int n);
void C_to_B(int n);
void B_to_A(int n);
void C_to_A(int n);

void A_to_C(int n){
    if(n==1){
        printf("Move disk from A to C\n");
    }else{
    A_to_B(n-1);
    printf("Move disk from A to C\n");
    B_to_C(n-1);
    }
}
void A_to_B(int n){
    if(n==1){
        printf("Move disk from A to B\n");
    }else{
    A_to_C(n-1);
    printf("Move disk from A to B\n");
    C_to_B(n-1);
    }    
}
void B_to_C(int n){
    if(n==1){
        printf("Move disk from B to C\n");
    }else{
    B_to_A(n-1);
    printf("Move disk from B to C\n");
    A_to_C(n-1);
    }    
}
void C_to_B(int n){
    if(n==1){
        printf("Move disk from C to B\n");
    }else{
    C_to_A(n-1);
    printf("Move disk from C to B\n");
    A_to_B(n-1);
    }    
}
void B_to_A(int n){
    if(n==1){
        printf("Move disk from B to A\n");
    }else{
    B_to_C(n-1);
    printf("Move disk from B to A\n");
    C_to_A(n-1);
    } 
}
void C_to_A(int n){
    if(n==1){
        printf("Move disk from C to A\n");
    }else{
    C_to_B(n-1);
    printf("Move disk from C to A\n");
    B_to_A(n-1);
    }
}

int main(){
    int n;
    scanf("%d",&n);
    A_to_C(n);
    return 0;
}