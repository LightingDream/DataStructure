#include <bits/stdc++.h>
using namespace std;
#define Link true
#define Thread false
typedef bool PointerTag;
typedef char ElemType;

struct BiThrTree{
    ElemType data;
    BiThrTree * lch;
    BiThrTree * rch;
    PointerTag lTag;
    PointerTag rTag;
};
typedef BiThrTree * pTree;

pTree newNode(ElemType data){
    pTree res = (pTree)malloc(sizeof(BiThrTree));
    res->data = data;
    res->lch = NULL;
    res->rch = NULL;
    return res;
}

pTree create(){
    ElemType ch;
    scanf("%c", &ch);
    if(ch == ' ') return NULL;
    else{
        pTree res = newNode(ch);
        res->lch = create();
        res->rch = create();
        return res;
    }
}

void inThreading(pTree rt, pTree &pre){
    if(rt){
        inThreading(rt->lch, pre);
        if(!rt->lch){
            rt->lTag = Thread;
            rt->lch = pre;
        }else rt->lTag = Link;
        if(!pre->rch){
            pre->rch = rt;
            pre->rTag = Thread;
        }else pre->rTag = Link;
        pre = rt;
        inThreading(rt->rch, pre);
    }
}

pTree inOrderThreading(pTree rt){
    pTree res = newNode(-1);
    res->lTag = Link;
    res->rTag = Thread;
    res->rch = res;
    if(rt == NULL) res->lch = res;
    else{
        pTree pre = res;
        res->lch = rt;
        inThreading(rt, pre);
        pre->rTag = Thread;
        pre->rch = res;
        res->rch = pre;
    }
    return res;
}

void inOrder(pTree rt){
    pTree p = rt->lch;
    while(p != rt){
        while(p->lTag == Link) p = p->lch;
        printf("%c ", p->data);
        while(p->rTag == Thread && p->rch != rt){
            p = p->rch;
            printf("%c ", p->data);
        }
        p = p->rch;
    }
    printf("\n");
}

int main(){
    pTree rt = create();
    pTree head = inOrderThreading(rt);
    inOrder(head);
    return 0;
}
