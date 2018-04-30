#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
using namespace std;
#define LIST_INCREMENT 10
#define LIST_INIT_SIZE 100
#define ElemType string
#define Status int
#define OK 1
#define ERROR 0

typedef struct{
    ElemType data[LIST_INIT_SIZE];
    int length;
    int listSize;
}SqList;

void InitList(SqList &l, int sz){
    l.listSize = sz;
    l.length = 0;
}

Status Insert(SqList &l, int pos, ElemType x){
    if(pos < 0 || pos > l.length) return ERROR;
  //  if(l.length == l.listSize) expand(l);
    for(int i = l.length - 1; i >= pos; --i)
        l.data[i + 1] = l.data[i];
    l.data[pos] = x;
    ++(l.length);
    return OK;
}

Status Delete(SqList &l, int pos, ElemType &x){
    if(pos < 0 || pos >= l.length) return ERROR;
    x = l.data[pos];
    for(int i = pos; i < l.length - 1; ++i)
        l.data[i] = l.data[i + 1];
    --(l.length);
    return OK;
}

int Query(SqList l, ElemType x){
    for(int i = 0; i < l.length; ++i)
        if(l.data[i] == x) return i;
    return -1;
}

Status DeleteValue(SqList &l, ElemType x){
    int pos = Query(l, x);
    if(pos == -1) return ERROR;
    for(int i = pos; i < l.length - 1; ++i)
        l.data[i] = l.data[i + 1];
    --(l.length);
    return OK;
}

void Print(SqList l){
    int len = l.length;
    if(len == 0){
        printf("\n");
        return;
    }
    for(int i = 0; i < l.length; ++i)
        printf("%s%c", l.data[i].c_str(), i == len - 1 ? '\n' : ' ');
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
    SqList l;   InitList(l, LIST_INIT_SIZE);
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
       //     printf("%d %s\n", pos, r.c_str());
            Insert(l, pos, r);
        //    printf("Insert End\n");
        }
        if(op == "delete") DeleteValue(l, mid);
        if(op == "search") printf("%d\n", Query(l, mid) + 1);
    }

    return 0;
}
