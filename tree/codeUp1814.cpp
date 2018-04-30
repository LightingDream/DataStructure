#include <bits/stdc++.h>
using namespace std;
const int maxn = 10010;

struct R{
    int l, r;
    int sum;
    bool lazy;
}seg[maxn << 2];

void build(int rt, int l, int r){
    seg[rt].l = l;
    seg[rt].r = r;
    seg[rt].sum = r - l + 1;
    seg[rt].lazy = 0;
    if(l == r) return;
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid);
    build(rt << 1 | 1, mid + 1, r);
}

void pd(int x){
    seg[x].lazy = 1;
    seg[x].sum = 0;
}

void pushdown(int rt){
    if(seg[rt].lazy){
        pd(rt<<1);
        pd(rt<<1|1);
        seg[rt].lazy = 0;
    }
}

void pushUp(int x){
    seg[x].sum = seg[x << 1].sum + seg[x << 1 | 1].sum;
}

void update(int rt, int ul, int ur){
    //cout << rt << endl;
    //cout << endl << ul << " " << ur << " ";
    //cout << seg[rt].l << " " << seg[rt].r << endl;
    if(ul <= seg[rt].l && ur >= seg[rt].r){
        seg[rt].sum = 0;
        seg[rt].lazy = 1;
        return;
    }
    pushdown(rt);
    int mid = (seg[rt].l + seg[rt].r) >> 1;
    if(ul <= mid) update(rt << 1, ul, ur);
    if(ur > mid)  update(rt << 1 | 1, ul, ur);
    pushUp(rt);
}

int main(){
    int L, q;
    while(cin >> L >> q){
        if(L == 0 && q == 0) break;
        build(1, 1, L + 1);
        while(q--){
            int l, r;
            cin >> l >> r;
            update(1, l + 1, r + 1);
        }
        cout << seg[1].sum << endl;
    }
    return 0;
}
