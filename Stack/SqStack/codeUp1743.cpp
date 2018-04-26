#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack>
#define MAX_SIZE 100
#define Status int
#define OK 1
#define ERROR 0
#define ElemType Node
#define QElemType Node
/**
 *Sequence Stack
 **/
int prior[256];

void init(){
    prior['+'] = prior['-'] = 0;
    prior['*'] = prior['/'] = 1;
}

typedef struct{
    int v;
    int isOp;
}Node;

Node newNode(int _v, int _isOp){
    Node res;
    res.v = _v;
    res.isOp = _isOp;
    return res;
}

typedef struct{
    QElemType data[MAX_SIZE];
    int front;
    int rear;
}SqQueue;

void initQueue(SqQueue &sq){
    sq.front = sq.rear = 0;

}
Status Push(SqQueue &sq, QElemType x){
    if((sq.rear + 1) % MAX_SIZE == sq.front) return ERROR;
    sq.data[sq.rear++] = x;
    return OK;
}

int IsEmpty(SqQueue sq){
    return sq.front == sq.rear;
}

Status Pop(SqQueue &sq){
    if(sq.front == sq.rear) return ERROR;
    sq.front = (sq.front + 1) % MAX_SIZE;
    return OK;
}

QElemType front(SqQueue sq){
    return sq.data[sq.front];
}

typedef struct{
    ElemType data[MAX_SIZE];
    int top;
}SqStack;

void initStack(SqStack &sq){
    sq.top = 0;
}

int size(SqStack sq){
    return sq.top;
}

int isEmpty(SqStack sq){
    return size(sq) == 0;
}

Status push(SqStack &sq, ElemType x){
    if(sq.top == MAX_SIZE) return ERROR;
    sq.data[sq.top++] = x;
    return OK;
}

Status pop(SqStack &sq){
    if(isEmpty(sq)) return ERROR;
    --sq.top;
    return OK;
}

ElemType top(SqStack sq){
    return sq.data[sq.top - 1];
}

int isNum(char ch){
    return ch >= '0' && ch <= '9';
}

void dealWithOperator(SqStack &sta, SqQueue &sq, char op){
    if(op == '(' || op == ')'){
        if(op == '(') push(sta, newNode(op, 1));
        else{
            while(top(sta).v != '('){
                Push(sq, top(sta));
                pop(sta);
            }
            pop(sta);
        }
        return;;
    }
    while(!isEmpty(sta) && top(sta).v != '(' && prior[op] <= prior[top(sta).v]){
            Push(sq, top(sta));
            pop(sta);
    }
    push(sta, newNode(op, 1));
}

double cal(double a, double b, int op){
    if(op == '+') return a + b;
    if(op == '-') return a - b;
    if(op == '*') return a * b;
    if(op == '/') return a / b;
}

int main(){
    freopen("in.txt", "r", stdin);
    SqStack sta;
    SqQueue sq;
    init();
    initQueue(sq);
    initStack(sta);
    char str[50];
    char op = 0;
    while(scanf("%s", str) != EOF){
        int inNum = 0;
        int num = 0;
     //   printf("1\n");
        for(int i = 0; str[i]; ++i){
            if(isNum(str[i])){
                if(inNum == 0) inNum = 1;
                num = 10 * num + str[i] - '0';
            }else{
                if(inNum == 1){
                    Push(sq, newNode(num, 0));
                    num = 0;
                    inNum = 0;
                }
                if(str[i] != '#')dealWithOperator(sta, sq, str[i]);
            }
        }
        while(!isEmpty(sta)){
            ElemType cur = top(sta);
            Push(sq, top(sta));
           // printf("%d %d\n", cur.v, cur.isOp);
            pop(sta);
        }
        std::stack<double> res;
        while(!IsEmpty(sq)){
            QElemType cur = front(sq);
            if(cur.isOp == 1){
                double op2 = res.top();
                res.pop();
                double op1 = res.top();
                res.pop();
               // printf("%f %f\n", op1, op2);
                res.push(cal(op1, op2, cur.v));
            }else res.push(cur.v);
            Pop(sq);
        }
        printf("%.0f\n", res.top());
        //pop(sta);
    }
    return 0;
}
