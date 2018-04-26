#include <bits/stdc++.h>
using namespace std;
const int MAX_SIZE = 100;
typedef struct{
    int mat[MAX_SIZE][MAX_SIZE];
    int row;
    int col;
}Matrix;

void read(Matrix &m){
    scanf("%d", &m.row);
    m.col = m.row;
    for(int i = 0; i < m.row; ++i)
        for(int j = 0; j < m.col; ++j)
            scanf("%d", &m.mat[i][j]);
}

void sum(Matrix m){
    int res1 = 0, res2 = 0;
    for(int i = 0; i < m.row; ++i){
        res1 += m.mat[i][i];
        res2 += m.mat[i][m.row - 1 - i];
    }
    printf("%d\n%d\n", res1, res2);
}

int main(){
    Matrix m;
    read(m);
    sum(m);
    return 0;
}
