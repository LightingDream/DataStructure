#include <stdio.h>
/**
 *CodeUp 1323
 *Sequence List
**/
#define MAX_SIZE 210
#define ElemType int
#define Status int
#define OK 1
#define ERROR 0
typedef struct{
    ElemType data[MAX_SIZE];
    int length;
}SqList;

int LocateElem(SqList l, ElemType x){
    for(int i = 0; i < l.length; ++i)
        if(l.data[i] == x) return i;
    return -1;
}

int ListLength(SqList l){
    return l.length;
}

void InitList(SqList &l){
    l.length = 0;
}

Status GetElem(SqList l, int pos, ElemType &e){
    if(pos < 0 || pos >= l.length) return ERROR;
    e = l.data[pos];
    return OK;
}

Status Insert(SqList &l, int pos, ElemType x){
    int len = ListLength(l);
    if(pos < 0 || pos > len || len == MAX_SIZE)
        return ERROR;
    for(int i = len - 1; i >= pos; --i)
        l.data[i + 1] = l.data[i];
    l.data[pos] = x;
    ++(l.length);
    return OK;
}

Status Delete(SqList &l, int pos, ElemType &e){
    if(pos < 0 || pos >= l.length) return ERROR;
    e = l.data[pos];
    for(int i = pos; i < l.length - 1; ++i)
        l.data[i] = l.data[i + 1];
    --(l.length);
    return OK;
}

void Print(SqList l){
    int len = ListLength(l);
    for(int i = 0; i < len; ++i)
        printf("%d%c", l.data[i], i == len - 1 ? '\n' : ' ');
}

void Union(SqList &la, SqList lb){
    int len_la = ListLength(la);
    int len_lb = ListLength(lb);
    for(int i = 0; i < len_lb; ++i){
        if(LocateElem(la, lb.data[i]) == -1)
            Insert(la, len_la++, lb.data[i]);
        Print(la);
    }
}

SqList la, lb;

int main(){

    int m, n;
    int v;

    while(scanf("%d", &m) != EOF){
        InitList(la);
        InitList(lb);
        for(int i = 0; i < m; ++i){
            scanf("%d", &v);
            Insert(la, i, v);
        }
        scanf("%d", &n);
        for(int i = 0; i < n; ++i){
            scanf("%d", &v);
            Insert(lb, i, v);
        }
        Print(la);
        Print(lb);
        Union(la, lb);
        printf("\n");
    }

    return 0;
}
