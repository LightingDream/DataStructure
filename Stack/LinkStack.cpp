#include <stdio.h>
#include <stdlib.h>
typedef int ElemType
typedef struct LNode{
    ElemType data;
    LNode * next;
}LNode;

LNode * newNode(ElemType x){
    LNode * res = (LNode *)malloc(sizeof(LNode));
    res->data = x;
    res->next = NULL;
    return res;
}

int main(){

    return 0;
}
