#include <stdio.h>
//代码功能：统计当前所有空位置的个数
//传入参数：代表当前座位情况的二维数组
int count_empty_seats(int seats[20][5]){
    int count=0;
    for(int row=0;row<20;row++){
        for(int col=0;col<5;col++){
            if(seats[row][col]==0){
                count++;
            }
        }
    }
    return count;
}
//函数功能：检查用户请求是否合理
//传入参数：pieces是单个用户所想购买的票数，seat[20][5]是记录当前位置情况的二维数组
int  is_valid_request(int pieces,int seats[20][5]){
    if(pieces<1||pieces>5){
        return -1;
    }
    if(count_empty_seats(seats)<pieces){
        return -1;
    }
    return 0;
}
//函数功能：寻找是否有连续座位
//传入参数：assigned_rows[]用于记录找到的连续座位的行数
int find_adjacent_seats(int pieces, int seats[20][5], int assigned_rows[], int assigned_cols[]){
    for(int row=0;row<20;row++){
        int cnt=0;
        for(int col=0;col<5;col++){
            if(seats[row][col]==0){
                cnt++;
                if(cnt==pieces){
                    int start_col=col-pieces+1;
                    for(int i=0;i<pieces;i++){
                        assigned_rows[i] = row; 
                        assigned_cols[i] = start_col + i;//记录找到的连续座位的行数和列数
                    }
                    return 1;
                }
            }else{
                cnt=0;//若计数中途发现位置断开，及时清零，代表座位不连续
            }
        }
        cnt=0;//每次外层循环结束后，及时给cnt清零
    }
    return 0;
}
//函数功能：寻找编号最小的空座位
void find_min_empty_seats(int pieces, int seats[20][5], int assigned_rows[], int assigned_cols[]){
    int cnt=0;
    for(int row=0;row<20;row++){
        for(int col=0;col<5;col++){
            if(seats[row][col]==0){
                assigned_rows[cnt]=row;
                assigned_cols[cnt]=col;//发上空座位便马上记录
                cnt++;
                if(cnt==pieces){
                    return;
                }
            }
        }
    }
}
//函数功能：调用上述几个与寻找位置有关的函数，输出找到的座位
//传入参数：times为发起的订单的数量，pieces_of_tickets[]为记录每个订单要买几张票的数组
void book_seats(int times,int pieces_of_tickets[],int seats[][5]){
    char col_to_char[]="ABCDF";//用字符数组记录代表列数的字母
    for(int i=0;i<times;i++){
        int pieces=pieces_of_tickets[i];

        if(is_valid_request(pieces, seats) == -1){
            printf("failed");//先判断购票数量是否合理
            continue;
        }
        int assigned_rows[5];
        int assigned_cols[5];//行列索引值，用于记录要买的位置

        int has_adjacent=find_adjacent_seats(pieces, seats, assigned_rows, assigned_cols);//先判断是否有连续座位
        if(!has_adjacent){
            find_min_empty_seats(pieces, seats, assigned_rows,assigned_cols);//若没有连续座位，则寻找编号最小的空位置
        }

        for(int k=0;k<pieces;k++){
            int row=assigned_rows[k];
            int col=assigned_cols[k];
            seats[row][col]=1;//更新选座
            
            if(k==0){
                printf("%d%c",row+1,col_to_char[col]);
            }else{
                printf(" %d%c",row+1,col_to_char[col]);
            }
            
        }
        printf("\n");
    }
}

int main(){
    int seats[20][5]={0};;
    char col_to_char[]="ABCDF";

    int times=0;
    scanf("%d",&times);
    if(times<1||times>100){
        printf("failed");
        return -1;
    }

    int pieces_of_tickets[times];
    int i=0;
    for(i=0;i<times;i++){
        scanf("%d",&pieces_of_tickets[i]);
    }

    book_seats(times,pieces_of_tickets,seats);
    return 0;
}