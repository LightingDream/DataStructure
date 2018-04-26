#include <stdio.h>
#include <stdlib.h>
#define ElemType int
/**
 *
 *@author adrui
 *@problemId CodeUp 1324
 **/
typedef struct Node{
    ElemType data;
    Node * next;
}LNode;

LNode * NewNode(ElemType x){
    LNode * res = (LNode *)malloc(sizeof(LNode));
    res->data = x;
    res->next = NULL;
    return res;
}

void InsertHead(LNode * head, LNode *tmp){
    tmp->next = head->next;
    head->next = tmp;
}

void InsertTail(LNode * head, LNode * tmp){
    LNode * cur = head;
    while(cur->next) cur = cur->next;
    cur->next = tmp;
}

void Merge1(LNode * A, LNode * B, LNode * &C){
    C = A;
    LNode * p = A->next;
    LNode * q = B->next;
    free(B);
    LNode * r = C;
    while(p != NULL && q != NULL){
        if(p->data <= q->data){
            r->next = p;
            r = r->next;
            p = p->next;
        }else{
            r->next = q;
            r = r->next;
            q = q->next;
        }
    }
    if(p != NULL) r->next = p;
    if(q != NULL) r->next = q;
}

void Merge2(LNode * A, LNode * B, LNode * &C){
    C = A;
    LNode * p = A->next;
    LNode * q = B->next;
    free(B);
    LNode * r;
    while(p != NULL && q != NULL){
        if(p->data <= q->data){
            r = p;
            p = p->next;
        }else{
            r = q;
            q = q->next;
        }
        InsertHead(C, r);
    }
    while(p != NULL) {
        r = p;
        p = p->next;
        InsertHead(C, r);
    }
    while(q != NULL) {
        r = q;
        q = q->next;
        InsertHead(C, r);
    }
}

void Print(LNode * head){
    LNode * cur = head->next;
    if(cur == NULL) {
        printf("\n");
        return;
    }
    printf("%d", cur->data);
    cur = cur->next;
    while(cur != NULL){
        printf(" %d", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

int main(){

    int m, n;
    int v;
    while(scanf("%d", &m) != EOF){
        LNode * A = NewNode(-1);
        LNode * B = NewNode(-1);
        LNode * C;
        for(int i = 0; i < m; ++i){
            scanf("%d", &v);
            InsertTail(A, NewNode(v));
        }
        scanf("%d", &n);
        for(int i = 0; i < n; ++i){
            scanf("%d", &v);
            InsertTail(B, NewNode(v));
        }
        Merge1(A, B, C);
        Print(C);
    }

    return 0;
}

