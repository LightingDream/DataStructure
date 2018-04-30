

[TOC]



##  队列(Queue)

>  也是一种限制存取点的线性表



## 队首和队尾

-  队首: 队列允许进行删除操作的一端
-  队尾: 队列允许进行插入操作的一端



## 队列的特性

​    **先入先出**



## 队列的存储结构

1.  顺序存储结构: 顺序队
2.  链式存储结构: 链队



## 顺序队

1.  结构定义:

   ```c++
   typedef struct{
       ElemType data[MAX_SIZE]; //顺序存储
       int front;			    //队首指针
       int rear;                //队尾指针
   }SqQueue;
   ```

2. 特点:

   -  同其它静态分配的顺序存储结构一样, 容量有限
   -  在两端都可以进行操作(一边插入, 一边删除)
   -  指针移动是同向的, 所以`front`和`rear`都有可能到达数组末端

3.  **假溢出**:

   当`front`和`rear` 都到达数组末端时, 这时队列为空, 但是不能插入元素， 称为`假溢出`,  会降低存储空间利用率

4. **循环队列**解决**假溢出**:

   利用取模操作`%` , 当`front`或者`rear` 指针到达数组末端时能够继续移动到数组首部, 这样就能继续使用数组空间, 这种数据结构称为`循环队列`

   `eg`: 

   ``` c++
   rear = MAX_SIZE - 1;
   rear = (rear + 1) % MAX_SIZE;
   /*
    *rear = 0, 移动到数组首部
    */
   ```

   ​

5. 操作集:

   ```c++
   /*
    * 这里使用front指向队首元素, rear指向队尾元素的下一个位置
    * front和rear不同指向都有差异, 这里只是一种
    */

   //队列大小(手画一下循环队列就明白了), 注意取模
   //这里能够得出队列为空时, front = rear
   //队列满时, (rear + 1) % MAX_SIZE = front, 此时有一个空间没有存储元素, 最大size是MAX_SIZE - 1
   int size(SqQueue sq){
       return (sq.rear - sq.front + MAX_SIZE) % MAX_SIZE;
   }

   //判空
   int isEmpty(SqQueue sq){
       return size(sq) == 0;//或者写成sq.front == sq.rear
   }

   int isFull(SqQueue sq){
       return sq.size() == MAX_SIZE - 1;//或者写成(sq.rear + 1) % MAX_SIZE == sq.front
   }

   Status push(SqQueue &sq, ElemType x){
       if(isFull(sq)) return ERROR; //队列已满
       sq.data[sq.rear] = x;
       sq.rear = (sq.rear + 1) % MAX_SIZE;
       return OK;
   }

   Status pop(SqQueue &sq, ElemType &x){
       if(isEmpty(sq)) return ERROR;//队列为空
       x = sq.data[sq.front];
       sq.front = (sq.front + 1) % MAX_SIZE;
       return OK;
   }

   Status top(SqQueue sq, ElemType &x){
       if(isEmpty(sq)) return ERROR;
       x = sq.data[sq.front];
       return OK;
   }
   ```



## 链队

1.  结构定义:

   ```c++
   typedef struct LNode{
       ElemType data;
       struct LNode * next;
   }LNode;//结点

   typedef struct {
       LNode * front;
       LNode * rear;
   }LinkQueue;//front指向队首, rear指向队尾
   ```

2.  操作集:

   ```c++
   LNode * newNode(ElemType x){
       LNode * res = (LNode *)malloc(sizeof(LNode));
       res->data = x;
       res->next = NULL;
   }
   //队为空时头结点的front和rear都为空
   int isEmpty(LinkQueue lq){
       return lq.front == NULL;//或者是lq.rear == NULL
   }

   void push(LinkQueue &lq, ElemType x){
       LNode * tmp = newNode(x);
       if(isEmpty(lq)){        //空队列
           lq.front = lq.rear = tmp;
           return;
       }
       //尾插法
       lq.rear->next = tmp;
       lq.rear = tmp;
   }

   Status pop(LinkQueue &lq, ElemType &x){
       if(isEmpty(lq)) return ERROR;
       LNode * tmp = lq.front;
       if(tmp->next == NULL) lq.front = lq.rear = NULL;
       else lq.front->next = tmp->next;
       x = tmp->data;
       free(tmp);
       return OK;
   }

   Status front(LinkQueue lq, ElemType &x){
       if(isEmpty(lq)) return ERROR;
       x = lq.front->data;
       return OK;
   }
   ```

3. 特点:

   -  无容量限制
   -  插入删除时`front`和`rear` 都可能修改




