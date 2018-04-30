[TOC]

## 数据结构－树(上)

### 定义

 Tree = (D, H), D是具有相同特性的数据元素的集合, H是Ｄ上二元关系的集合, T满足如下定义

**ADT Tree**{

​	**数据对象**: D

​	**数据关系**: H

​	若$D = \emptyset$, H也为$\emptyset$, 称为空树

​	(1) 若D中只有唯一的元素(树根),H为空

​	(2) 若$D^{'} = D - {root}$不为空, 则存在$D^{'}$的一个划分

​	$$D_1,D_2, ...D_m(m>0),\forall j\not=k(1\leq j,k \leq m)有D_j \bigcap D_k = \emptyset $$

​	对于$$\forall i \in [1, m], 都存在唯一的想x_i  \in D_i, 使得<root, x_i> \in H$$

​	(3) 对于(2)的划分, $H-{<root, x_1>, <root, x_2>, ....<root, x_m>}有唯一的一个划分H_1, H_2,... H_m$

​	$$\forall j \not= k \bigwedge 1 \leq j, k \leq m, H_j \bigcap \ H_k = \emptyset$$

​	且$$\forall i(1 \leq i \leq m), H_i 是D_i上的关系, (D_i, H_i)是一棵符合本定义的树,称为root的子树, 各子树构成森林$$

​	**操作集**: 略

​	**H中的关系在树上就是指两结点之间边**

​	对于$<f, s> \in H, f是s的双亲结点, s是f的孩子结点$

}

### 特点

>  递归定义, 树根和子树的根节点满足二元关系

### 基本术语

- 结点: 包含一个数据元素及若干指向其子树的分支
- 结点的度:结点拥有的子树数
- 树的度:树内各节点的度的最大值
- 非终端结点:度大于0的结点
- 叶子结点:度为0的结点
- 内部结点:除树根以外的终端结点
- 树的层次:树根层次为1, 其他结点层次是其双亲结点的层次+1
- 兄弟, 堂兄弟, 祖先, 子孙(类比祖谱)
- 树高(深度):树内结点的最大层次

### 二叉树(Binary Tree)

>  各结点度不超过2的树, 上述定义中每层划分数最大为２

### 二叉树的性质

- 二叉树第i层的最大结点数:$2^{i-1}(归纳法可证)$


- 深度为k的二叉树结点数量最多为 $2^k-1$

- 设二叉树中度为2的结点个数为$n_2$,度为0的结点(叶子结点)个数为$n_0$,度为1的结点的个数为$n_1$

  $$n_0 = n_2 + 1$$

- 满二叉树: 深度为k且结点数量为$2^k-1$的二叉树, 即每层结点数量都是最大值

- 完全二叉树: 与其深度相同的满二叉树在相应位置的结点编号相同

- 结点数为n的完全二叉树深度:$\lfloor\log_2n\rfloor+1或\lceil\log_2{n+1}\rceil $

- 编号为i(从1开始编号)的结点的双亲节点的编号为$\lfloor\frac{i}{2}\rfloor$,0表示不存在双亲节点, 左右孩子结点若存在,其编号分别为$i*2, i*2+1$

- 结点数为n的二叉树有多少种(形状):

  $Catalan数: \frac{C_{2n}^n}{n+1}$

  证明: 固定一个结点rt为根, 则rt的坐子树结点数l满足$l \in [0, n -1]$, 右子树结点数为n-1-l

  设$f(n)表示n个结点二叉树种类数, 则f(n)=\sum_{i=0}^{n-1}f(i)*f(n-1-i)$

  且$f(0)=f(1)=1$,即为$Catalan$数

### 操作集

- 基础

  ```c++
  #include <stdio.h>
  #include <stdlib.h>
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

  pTree getTree(pTree rt, int index){　//根据2进制获取某一结点
      while(index > 1){
          if(index & 1) rt = rt->rch;
          else rt = rt->lch;
          index >>= 1;
          if(rt == NULL) return rt;
      }
      return rt;
  }

  Status getValue(pTree rt, pTree e, ElemType &x){　//get
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
      destroyBiTree(rt);
      if(rt == NULL) printf("Destoryed!\n");
      return 0;
  }
  ```

  ​


- 树的遍历(递归)

  ```c++
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
  ```

- 树的遍历(非递归)

  ```c++
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
        	if((rt->lch == NULL && rt->rch == NULL) ||){
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
        	que = tmp;
        	tmp.clear();
    	}
  }
  ```

- 中序线索化及遍历:

  ```c++
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
  ```


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

  pTree inOrderThreading(pTree rt){//线索化
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
  ```

- 根据前序中序遍历确定后序遍历(确定二叉树的形状)

  >  只能是前序遍历或者后序遍历和中序遍历才能确定一棵二叉树, 前序遍历和后序遍历无法确定

  递归思想:

  [codeUp1096](http://codeup.hustoj.com/problem.php?cid=100000611&pid=0)

  ```c++
  #include <stdlib.h>
  #include <stack>
  #include <string>
  #include <iostream>
  using namespace std;
   
  typedef char ElemType;
  typedef struct BiTree{
      ElemType data;
      BiTree * lch;
      BiTree * rch;
  }BiTree, * pTree;
   
  pTree newNode(ElemType data){
      pTree res = (pTree)malloc(sizeof(BiTree));
      res->data = data;
      res->lch = NULL;
      res->rch = NULL;
      return res;
  }
   
  pTree getTree(string pre, string in){
      ElemType fi = pre[0];
      int pos = in.find(fi);
      pTree res = newNode(fi);
      if(pos > 0)
          res->lch = getTree(pre.substr(1, pos), in.substr(0, pos));
      if(pos + 1 < pre.length())
          res->rch = getTree(pre.substr(pos + 1), in.substr(pos + 1));
      return res;
  }
   
  void postOrder(pTree rt){
      stack<pTree> s;
      s.push(rt);
      pTree pre = NULL;
      while(!s.empty()){
          rt = s.top();
          if((!rt->lch && !rt->rch) || (pre && (pre == rt->lch || pre == rt->rch))){
              cout << rt->data;
              s.pop();
              pre = rt;
          }else{
              if(rt->rch) s.push(rt->rch);
              if(rt->lch) s.push(rt->lch);
          }
      }
      cout << endl;
  }
   
  int main(){
      string pre, in;
      while(cin >> pre >> in) {
          pTree rt = getTree(pre, in);
          postOrder(rt);
      }
      return 0;
  }
  ```


.... 待续
