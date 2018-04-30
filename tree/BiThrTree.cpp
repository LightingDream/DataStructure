#include <bits/stdc++.h>
using namespace std;
typedef int ElemType;
typedef struct BiThrTree{
    ElemType data;
    BiThrTree * lch;
    BiThrTree * rch;
    bool lTag;
    bool rTag;
}BiThrTree, * pTree;

pTree newNode(ElemType data){	//newNode
    pTree res = (pTree)malloc(sizeof(BiThrTree));
    res->data = data;
    res->lch = NULL;
    res->rch = NULL;
    res->lTag = true;
    res->rTag = true;
    return res;
}


void inThreading(pTree rt, pTree &pre){
    if(rt){
        inThreading(rt->lch, pre);
        if(!pre->rch){
            pre->rTag = false;
            pre->rch = rt;
        }
        if(!rt->lch){
            rt->lTag = false;
            rt->lch = pre;
        }
        pre = rt;
        inThreading(rt->rch, pre);
    }
}

pTree inOrderThreading(pTree rt){
    pTree res = newNode(-1);
    res->lTag = true;
    res->rTag = false;
    res->rch = res;
    if(!rt){
        res->lch = res;
    }else{
        res->lch = rt;
        pTree pre = res;
        inThreading(rt, pre);
        //printf("%d %d\n", pre->data, res->data);
        pre->rTag = false;
        pre->rch = res;
        res->rch = pre;
    }
    return res;
}

void inOrder(pTree rt){
    pTree p = rt->lch;
    while(p != rt){
        //printf("%d\n", p->data);
        while(p->lTag == true) p = p->lch;
        printf("%-3d", p->data);
        while(p->rTag == false && p->rch != rt){
            p = p->rch;
            printf("%-3d", p->data);
        }
        p = p->rch;
    }
    puts("");
}

void inOrderReverse(pTree rt){
    pTree p = rt->rch;
    while(p != rt){
        while(p->rTag == true) p = p->rch;
        printf("%-3d", p->data);
        while(p->lTag == false && p->lch != rt){
            p = p->lch;
            printf("%-3d", p->data);
        }
        p = p->lch;
    }
    puts("");
}

int main(){
    pTree rt = newNode(1);
    pTree tree2 = newNode(3);
    pTree tree3 = newNode(6);
    pTree tree4 = newNode(5);
    rt->lch = tree2;
    rt->rch = tree3;
    tree2->rch = tree4;
    pTree head = inOrderThreading(rt);
    inOrder(head);
    inOrderReverse(head);
    return 0;
}
