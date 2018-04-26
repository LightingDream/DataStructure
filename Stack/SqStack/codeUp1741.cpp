#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 10000
#define Status int
#define OK 1
#define ERROR 0
typedef char ElemType;
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

Status pop(SqStack &sq){
    if(getSize(sq) == 0) return ERROR;
    --sq.top;
    return OK;
}

void Print(SqStack sq){
    for(int i = 0; i < sq.top; ++i)
        putchar(sq.data[i]);
}

int main(){
    freopen("in.txt", "r", stdin);
    SqStack sq;
    initStack(sq);
    char ch;
    while(scanf("%c", &ch) != EOF){
        switch(ch){
            case '#': pop(sq);
                break;
            case '@': initStack(sq);
                break;
            case '\n':{
                        push(sq, '\n');
                        Print(sq);
                        initStack(sq);
                      }
                break;
            default:
                push(sq, ch);
                break;
        }
    }
    Print(sq);
    printf("\n");
    return 0;
}
