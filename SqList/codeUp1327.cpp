#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
using namespace std;
#define MAX_SIZE 11
#define ElemType string
#define Status int
#define OK 1
#define ERROR 0

typedef struct{
    ElemType data;
    int next;
}NodeType[MAX_SIZE];

void InitList(NodeType space){
    for(int i = 2; i < MAX_SIZE - 1; ++i)
        space[i].next = i + 1;
    space[MAX_SIZE - 1].next = 0;
    space[1].next = 0;
    space[0].next = 2;
}

int GetFree(NodeType space){
    int res = space[0].next;
    if(space[0].next)
        space[0].next = space[space[0].next].next;
    return res;
}

int ListLength(NodeType space){
    int len = 0;
    int cur = space[1].next;
    while(cur){
        ++len;
        cur = space[cur].next;
    }
    return len;
}

Status Insert(NodeType space, int pos, ElemType x){
    if(pos < 0 || pos > ListLength(space)) return ERROR;
    int cur = 1;
    int fr = GetFree(space);
    if(fr == 0) return ERROR;
    for(int j = 0; j < pos; ++j)
        cur = space[cur].next;
    space[fr].data = x;
    space[fr].next = space[cur].next;
    space[cur].next = fr;
    return OK;
}

void Free(NodeType space, int x){
    space[x].next = space[0].next;
    space[0].next = x;
    //space[x].data = "";
}

Status Delete(NodeType space, int pos){
    if(pos < 0 || pos >= ListLength(space)) return ERROR;
    int cur = 1;
    for(int j = 0; j < pos; ++j)
        cur = space[cur].next;
    int tmp = space[cur].next;
    space[cur].next = space[tmp].next;
    Free(space, tmp);
    return OK;
}

int Query(NodeType space, ElemType x){
    int cur = space[1].next;
    while(cur){
        if(space[cur].data == x) return cur;
        cur = space[cur].next;
    }
    return -1;
}

void Print(NodeType space){
    for(int i = 0; i < MAX_SIZE; ++i)
        printf("%-8s%2d\n", space[i].data.c_str(), space[i].next);
    for(int i = 0; i < 20; ++i)
        printf("*");
    printf("\n");
}

int StringToInt(string x){
    int res = 0;
    int len = x.length();
    for(int i = 0; i < len; ++i)
        res = res * 10 + (x[i] - '0');
    return res;
}

int main(){
    freopen("in.txt", "r", stdin);
    NodeType l;
    InitList(l);
    char str[50];
    string op, mid, r;

    while(gets(str)){
        op = "";
        mid = "";
        r = "";
        int len = strlen(str);
        int i;
        for(i = 0; i < len; ++i){
            if(str[i] == ' ') break;
            op += str[i];
        }
        for(++i; i < len; ++i){
            if(str[i] == ' ') break;
            mid += str[i];
        }
        for(++i; i < len; ++i) r += str[i];
        if(op == "show") Print(l);
        if(op == "insert"){
            int pos = StringToInt(mid) - 1;
            Insert(l, pos, r);
        }
        if(op == "delete") Delete(l, StringToInt(mid) - 1);
        if(op == "search") {
            printf("%2d\n", Query(l, mid));
            for(int i = 0; i < 20; ++i)
                printf("*");
            printf("\n");
        }
    }
    return 0;
}
