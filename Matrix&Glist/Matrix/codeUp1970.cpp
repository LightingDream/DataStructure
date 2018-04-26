#include <bits/stdc++.h>
using namespace std;
const int MAX_SIZE = 110;
typedef int ElemType;
typedef struct {
    int row;
    int col;
    ElemType mat[MAX_SIZE][MAX_SIZE];
}Matrix;

Matrix mul(const Matrix a, const Matrix b){
    Matrix res;
    res.row = a.row;
    res.col = b.col;
    for(int i = 0; i < a.row; ++i)
        for(int j = 0; j < b.col; ++j){
            res.mat[i][j] = 0;
            for(int k = 0; k < a.col; ++k)
                res.mat[i][j] += a.mat[i][k] * b.mat[k][j];
        }
    return res;
}

void read(Matrix &m){
    for(int i = 0; i < m.row; ++i)
        for(int j = 0; j < m.col; ++j)
            scanf("%d", &m.mat[i][j]);
}

void print(Matrix m){
    for(int i = 0; i < m.row; ++i)
        for(int j = 0; j < m.col; ++j)
            printf("%d%c", m.mat[i][j], j == m.col - 1 ? '\n' : ' ');
}

int main(){
    //freopen("in.txt", "r", stdin);
    Matrix a;
    a.row = 2; a.col = 3;
    Matrix b;
    b.row = 3; b.col = 2;
    int x;
    while(~scanf("%d", &x)){
        a.mat[0][0] = x;
        for(int i = 0; i < 2; ++i)
            for(int j = !i; j < 3; ++j)
                scanf("%d", &a.mat[i][j]);
        read(b);
        print(mul(a, b));
    }
    return 0;
}
