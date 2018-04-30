#include <bits/stdc++.h>
using namespace std;
const int MAX_SIZE = 12505;
#define ElemType int
typedef struct{
    ElemType data;
    int id;
}Trimat;
typedef struct{
    Trimat B[MAX_SIZE];
    int row;
    int col;
    int k;
}Matrix;

void read(Matrix &m){
    int r, c;
    ElemType v;
    int cnt = 0;
    scanf("%d%d", &r, &c);
    for(int i = 0; i < r; ++i)
        for(int j = 0; j < c; ++j){
            scanf("%d", &v);
            if(v){
                m.B[cnt].data= v;
                m.B[cnt].id = i * c + j;
                cnt++;
            }
        }
    m.row = r;
    m.col = c;
    m.k = cnt;
}

bool cmp(Trimat a, Trimat b){
    return a.id < b.id;
}
void trsmat(Matrix &m){
    for(int i = 0; i < m.k; ++i){
        Trimat &o = m.B[i];
        int r = o.id / m.col;
        int c = o.id % m.col;
        o.id = c * m.row + r;
    }
    int tmp = m.row;
    m.row = m.col;
    m.col = tmp;
    sort(m.B, m.B + m.k, cmp);
}

void print(Matrix m){
    int k = 0;
    for(int i = 0; i < m.row; ++i){
        for(int j = 0; j < m.col; ++j){
            if(k < m.k && i * m.col + j == m.B[k].id){
                printf("%d", m.B[k].data);
                ++k;
            }else printf("0");
            printf(" ");
        }
        printf("\n");
    }
}

int main(){
    freopen("in.txt", "r", stdin);
    Matrix m;
    read(m);
    trsmat(m);
    print(m);
    return 0;
}
