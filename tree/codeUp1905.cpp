#include <bits/stdc++.h>
using namespace std;

int cal(int x){
    int res = 0;
    while(x > 1){
        ++res;
        x >>= 1;
    }
    return res;
}

int main(){
    int n, m;
    while(scanf("%d%d", &m, &n) != EOF){
        if(n == 0 && m == 0) break;
        int time = n / m;
        int high = cal(time);
        int ans = (1 << high) - 1;
        ans +=  min(1 << high, n - m * (1 << high) + 1);
        printf("%d\n", ans);
    }
    return 0;
}
