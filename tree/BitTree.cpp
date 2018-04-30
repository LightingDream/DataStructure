#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <queue>
using namespace std;
#define Status int
#define OK 1
#define ERROR 1
typedef int ElemType;

typedef struct BiTree{			//结构定义
    ElemType data;
    BiTree * lch;
    BiTree * rch;
}BiTree, * pTree;

pTree newNode(ElemType data){	//newNode
    pTree res = (pTree)malloc(sizeof(BiTree));
    res->data = data;
    res->lch = NULL;
    res->rch = NULL;
    return res;
}

void initTree(pTree &rt){		//init
    rt = NULL;
}

void destroyBiTree(pTree &rt){	//destory
    if(rt != NULL) {
        destroyBiTree(rt->lch);
        destroyBiTree(rt->rch);
        free(rt);
        rt = NULL;
    }
}

Status BiTreeEmpty(pTree rt){	//isEmpty
    return rt == NULL;
}

inline int max(int a, int b){
    return a >= b ? a : b;
}

int BiTreeDepth(pTree rt){		//树的高度
    if(rt == NULL) return 0;
    return 1 + max(BiTreeDepth(rt->lch), BiTreeDepth(rt->rch));
}

pTree getTree(pTree rt, int index){//根据2进制获取某一结点
    while(index > 1){
        if(index & 1) rt = rt->rch;
        else rt = rt->lch;
        index >>= 1;
        if(rt == NULL) return rt;
    }
    return rt;
}

Status getValue(pTree rt, pTree e, ElemType &x){//get
    int depth = BiTreeDepth(rt);
    for(int i = 1; i < 1 << depth; ++i){
        pTree elem = getTree(rt, i);
        if(elem == e) {
            x = elem->data;
            return OK;
        }
    }
    return ERROR;
}

Status assignValue(pTree rt, pTree e, ElemType x){//set
    int depth = BiTreeDepth(rt);
    for(int i = 1; i < 1 << depth; ++i){
        pTree elem = getTree(rt, i);
        if(elem == e) {
            elem->data = x;
            return OK;
        }
    }
    return ERROR;
}

pTree getParent(pTree rt, pTree e){			//获取双亲结点
    int depth = BiTreeDepth(rt);
    for(int i = 1; i < 1 << depth; ++i){
        pTree elem = getTree(rt, i);
        if(elem && (elem->lch == e || elem->rch == e)) return elem;
    }
    return NULL;
}


//先序遍历
void preOrder(pTree rt){
	if(rt == NULL) return;
  	printf("%-3d", rt->data);
  	preOrder(rt->lch);
  	preOrder(rt->rch);
}
//中序遍历
void inOrder(pTree rt){
  	if(rt == NULL) return;
  	inOrder(rt->lch);
  	printf("%-3d", rt->data);
  	inOrder(rt->rch);
}
//后序遍历
void postOrder(pTree rt){
    if(rt == NULL) return;
  	postOrder(rt->lch);
  	postOrder(rt->rch);
  	printf("%-3d", rt->data);
}

//stack, queue借助STL
void inOrder1(pTree rt){
  	stack<pTree> s;
  	s.push(rt);
  	while(!s.empty()){
      	while(s.top()) s.push(s.top()->lch);
      	s.pop();
      	if(!s.empty()){
        	pTree tmp = s.top();
      		printf("%-3d", tmp->data);
      		s.pop();
       		s.push(tmp->rch);
        }
  	}
}

void inOrder2(pTree rt){
 	stack<pTree> s;
  	while(rt || !s.empty()){
      	if(rt) {
          	s.push(rt);
          	rt = rt->lch;
        }else{
          	rt = s.top();
      	  	printf("%-3d", rt->data);
          	s.pop();
       	  	rt = rt->rch;
        }
  	}
}

void preOrder1(pTree rt){
  	stack<pTree> s;
  	while(rt || !s.empty()){
      	if(rt){
          	printf("%-3d", rt->data);
          	s.push(rt);
          	rt = rt->lch;
      	}else{
          	rt = s.top();
          	s.pop();
          	rt = rt->rch;
      	}
  	}
}

void postOrder1(pTree rt){
  	pTree pre = NULL;
  	stack<pTree> s;
  	s.push(rt);
  	while(!s.empty()){
      	rt = s.top();
      	if((rt->lch == NULL && rt->rch == NULL) ||(pre != NULL && (pre == rt->lch || pre == rt->rch))){
          	printf("%-3d", rt->data);
          	s.pop();
          	pre = rt;
      	}else{
          	if(rt->rch != NULL) s.push(rt->rch);
          	if(rt->lch != NULL) s.push(rt->lch);
      	}
  	}
}

void display(pTree rt){
  	if(rt != NULL){
      	printf("%-3d", rt->data);
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
}

void levelOrder(pTree rt){
  	queue<pTree> que, tmp;
  	que.push(rt);
  	while(!que.empty()){
      	while(!que.empty()){
      		rt = que.front();
      		que.pop();
      		printf("%-3d", rt->data);
          	if(rt->lch) tmp.push(rt->lch);
          	if(rt->rch) tmp.push(rt->rch);
        }
      	puts("");
      	que.swap(tmp);
  	}
}
//test


int main(){
    ElemType elem;
    pTree rt = newNode(1);
    pTree tree2 = newNode(3);
    pTree tree3 = newNode(6);
    pTree tree4 = newNode(5);
    rt->lch = tree2;
    rt->rch = tree3;
    tree2->rch = tree4;
    printf("Depth: %d\n", BiTreeDepth(rt));
    if(getValue(rt, tree3, elem)) printf("OldValue: %d\n", elem);
    else printf("Not in!\n");
    assignValue(rt, tree3, 7);
    if(getValue(rt, tree3, elem)) printf("NewValue: %d\n", elem);
    else printf("Not in!\n");
    pTree p = getParent(rt, tree3);
    if(p) printf("%d\n", p->data);

    preOrder(rt),puts("");
    preOrder1(rt), puts("");
    inOrder(rt),puts("");
    inOrder1(rt), puts("");
    inOrder2(rt), puts("");
    postOrder(rt),puts("");
    postOrder1(rt), puts("");
    levelOrder(rt);
    display(rt), puts("");

    destroyBiTree(rt);
    if(rt == NULL) printf("Destoryed!\n");
    return 0;
}
