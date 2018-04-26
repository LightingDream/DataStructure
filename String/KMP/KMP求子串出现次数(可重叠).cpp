#include <bits/stdc++.h>
using namespace std;

int nxt[110];
char substr[110];
char str[110];

void getNext(){
    nxt[0] = -1;
    int i = 0, j = -1;
    while(substr[i]){
        if(j == -1 || substr[i] == substr[j]){
            ++i;
            ++j;
            nxt[i] = substr[i] == substr[j] ? nxt[j] : j;
        }else j = nxt[j];
    }
}

int kmp(){
    int i = 0, j = 0;
    int res = 0;
    while(str[i] && j < strlen(substr)){
        if(j == -1 || str[i] == substr[j]){
            ++i;
            ++j;
        }else j = nxt[j];
        if(j == strlen(substr)){
            ++res;
            j = nxt[j];
        }
    }
    return res;
}

int main(){
    freopen("in.txt", "r", stdin);
    while(~scanf("%s%s", str, substr)){
        getNext();
        int len = strlen(substr);
        printf("%d\n", nxt[len] && nxt[len] % (len - nxt[len]) == 0);
        printf("%d\n", kmp());
    }
    return 0;
}
