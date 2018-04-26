#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100
#define Status int
#define OK 1
#define ERROR 0
typedef int ElemType;
/**
 *Sequence Stack
 **/
typedef struct{
    ElemType data[MAX_SIZE];
    int top;
}SqStack;

void initStack(SqStack &sq){
    sq.top = 0;
}

int getSize(SqStack sq){
    return sq.top;
}

int isEmpty(SqStack sq){
    return getSize(sq) == 0;
}

Status push(SqStack &sq, ElemType x){
    if(sq.top == MAX_SIZE) return ERROR;
    sq.data[sq.top++] = x;
    return OK;
}

Status pop(SqStack &sq, ElemType &x){
    if(getSize(sq) == 0) return ERROR;
    x = sq.data[--sq.top];
    return OK;
}

int main(){
    SqStack sq;
    initStack(sq);
    int n;
    while(scanf("%d", &n) != EOF){
        while(n){
            push(sq, n % 8);
            n /= 8;
        }
        int ans = 0;
        ElemType x;
        while(!isEmpty(sq)){
            pop(sq, x);
            ans = 10 * ans + x;
        }
        printf("%d\n", ans);
    }
    return 0;
}
