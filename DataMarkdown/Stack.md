[TOC]



##  栈(Stack)

>  是一种限制存取点的线性表, 只能在一端进行插入或删除操作



##  栈顶和栈底

-  栈顶:  指栈中允许进行插入和删除操作的一端
-  栈底:  栈的另一端



##栈的特性

典型的先入后出



##  栈的存储结构

1.  顺序存储结构: `顺序栈`
2.  链式存储结构: `链栈`



## 顺序栈

1.  结构定义(相关宏定义参考线性表):

   ```c++
   typedef struct {
       ElemType data[MAX_SIZE]; //顺序存储, 先进后出
       int top;			    //存栈顶位置(只能在栈顶一端插入或删除)
   }SqStack;
   ```

2.  操作集:

    ```c++
       /*
    *初始化, 这里top存栈定元素的下一个位置, 同时也是栈的大小
    */
       void initStack(SqStack &sq){
       sq.top = 0;
       }
    ```

   int size(SqStack &sq){   //栈大小
       return sq.top;
   }

   int isEmpty(SqStack sq){ //判栈是否为空
       return size(sq) == 0;
   }

   Status push(SqStack &sq, ElemType x){ //入栈
       if(sq.top == MAX_SIZE) return ERROR;
       sq.data[sq.top++] = x;
       return OK;
   }

   Status pop(SqStack &sq, ElemType &x){ //出栈
       if(isEmpty(sq)) return ERROR;
       x = sq.data[--sq.top];
       return OK;
   }

   Status top(SqStack sq, ElemType &x){  //获取栈顶元素
       if(isEmpty(sq)) return ERROR;
       x = sq.data[sq.top - 1];
       return OK;
   }
    ​```

3. 特点:

   - 有容量限制
   - 插入删除简单  

##  链栈

1.  结构定义:

   ```c++
   typedef struct LNode{
       ElemType data;		//数据域
       struct LNode * next;//指针域
   }LNode;
   /*
    * 一个头结点(不存储信息)指向表头
    */
   ```

2.  操作集:

   ```c++
   /*
    *新建结点
    */
   LNode * newNode(ElemType x){
       LNode * res = (LNode *)malloc(sizeof(LNode));
       res->data = x;
       res->next = NULL;
       return res;
   }
   /*
    *插入操作, 这里栈顶第一个结点是表头的next指向的结点, 插入删除都在表头一端
    *先入栈的元素在链表中后被删除(先进后出)
    *由于是链式结构, 所以一般没有容量限制, 插入操作都能够成功
    */
   void push(LNode * head, ElemType x){
       LNode * tmp = newNode(x); 
       tmp->next = head->next;  //头插法
       head->next = tmp; 
   }

   int isEmpty(LNode * head){		//判空
       return head->next == NULL;
   }

   Status pop(LNode * head, ElemType x){
       if(isEmpty(head)) return ERROR; //栈为空
       LNode * tmp = head->next; //当前栈顶
       head->next = tmp->next;   //修改栈顶
       x = tmp->data;            //返回元素值
       free(tmp);				
       return OK;
   }

   Status top(LNode * head, ElemType &x){
       if(isEmpty(head)) return ERROR;
       x = head->next->data;
       return OK;
   }
   ```

3. 特点

   -  无容量限制
   -  存储密度 < 1(指针域)



##  栈的应用

-  后缀表达式求值
- 函数调用时保护现场
- 递归过程





