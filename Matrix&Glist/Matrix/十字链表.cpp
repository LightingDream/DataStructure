#include <bits/stdc++.h>
using namespace std;
typedef int ElemType;
#define MAX_SIZE 3
typedef struct Node{
    int row;
    int col;
    ElemType data;
    struct Node * next;
    struct Node * down;
}Node;
typedef struct{
    Node * rhead;
    Node * chead;
    int row;    //row num
    int col;    // col num
    int k;      //非零元素num
}CrossList;

void init(CrossList &M){
    M.k = 0;
    if(M.rhead) free(M.rhead);
    if(M.chead) free(M.chead);
}

Node * newNode(int r, int c, int data){
    Node * res = (Node *)malloc(sizeof(Node));
    res->row = r;
    res->col = c;
    res->data = data;
    res->down = NULL;
    res->next = NULL;
    return res;
}

void createCrossListMat(CrossList &M, int mat[][MAX_SIZE], int m, int n){
    M.rhead = (Node *)malloc(m * sizeof(Node));
    M.chead = (Node *)malloc(n * sizeof(Node));
    M.row = m;
    M.col = n;
    Node ** cur_c = (Node **)malloc(n * sizeof(Node*));
    for(int i = 0; i < n; ++i)
        cur_c[i] = &M.chead[i];
    for(int i = 0; i < m; ++i){
        Node * cur = &M.rhead[i];
        for(int j = 0; j < n; ++j)
            if(mat[i][j]){
                Node * tmp = newNode(i, j, mat[i][j]);
                cur->next = tmp;
                cur = tmp;
                cur_c[j]->down = tmp;
                cur_c[j] = tmp;
                ++M.k;
            }
    }
}
int main(){
    int mat[][MAX_SIZE] = {{0, 1, 0}, {1, 1, 0}, {1, 0, 1}};
    CrossList M;
    init(M);
    createCrossListMat(M, mat, 3, 3);
    for(int i = 0; i < 3; ++i){
        Node * cur = &M.rhead[i];
        cur = cur->next;
        while(cur){
            printf("(%d->%d, %d) ", cur->row, cur->col, cur->data);
            cur = cur->next;
        }
        printf("\n");
    }
    for(int i = 0; i < 3; ++i){
        Node * cur = &M.chead[i];
        cur = cur->down;
        while(cur){
            printf("(%d->%d, %d) ", cur->row, cur->col, cur->data);
            cur = cur->down;
        }
        printf("\n");
    }
    return 0;
}
