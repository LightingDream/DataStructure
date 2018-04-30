#include <bits/stdc++.h>
using namespace std;
typedef char ElemType;
struct BiTree{
    ElemType data;
    BiTree * lch;
    BiTree * rch;
};
typedef BiTree * pTree;

pTree newNode(ElemType data){
    pTree res = (pTree)malloc(sizeof(BiTree));
    res->data = data;
    res->lch = NULL;
    res->rch = NULL;
    return res;
}

ElemType ch;

pTree create(){
    scanf("%c", &ch);
    if(ch == ' ') return NULL;
    else{
        pTree res = newNode(ch);
        res->lch = create();
        res->rch = create();
        return res;
    }
}

void preOrder(pTree rt){
    stack<pTree> s;
    while(rt || !s.empty()){
        if(rt) {
            printf("%c ", rt->data);
            s.push(rt);
            rt = rt->lch;
        }
        else{
            rt = s.top();
            s.pop();
            rt = rt->rch;
        }
    }
    puts("");
}

void inOrder(pTree rt){
    stack<pTree> s;
    while(rt || !s.empty()){
        if(rt) {
            s.push(rt);
            rt = rt->lch;
        }
        else{
            rt = s.top();
            printf("%c ", rt->data);
            s.pop();
            rt = rt->rch;
        }
    }
    puts("");
}

bool isLeaf(pTree rt){
    return rt->lch == NULL && rt->rch == NULL;
}

void postOrder(pTree rt){
    stack<pTree> s;
    pTree pre = NULL;
    s.push(rt);
    while(!s.empty()){
        rt = s.top();
        if(isLeaf(rt) || (pre && (pre == rt->lch || pre == rt->rch))) {
            s.pop();
            pre = rt;
            printf("%c ", rt->data);
        }
        else{
            if(rt->rch) s.push(rt->rch);
            if(rt->lch) s.push(rt->lch);
        }
    }
    puts("");
}

void display(pTree rt){
    printf("%c", rt->data);
    if(rt->lch || rt->rch){
        printf("(");
        if(rt->lch) display(rt->lch);
        else printf("^");
        printf(",");
        if(rt->rch) display(rt->rch);
        else printf("^");
        printf(")");
    }
}
int main(){
    pTree rt = create();
    //display(rt);
    preOrder(rt);
    inOrder(rt);
    inOrder(rt);
    return 0;
}
