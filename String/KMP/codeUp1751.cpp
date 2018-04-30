#include <bits/stdc++.h>
using namespace std;
char nxt[110];

void getNext(char * p){
    nxt[0] = -1;
    int i = 0, j = -1;
    while(p[i + 1]){
        if(j == -1 || p[i] == p[j]){
            ++i;
            ++j;
            nxt[i] = p[i] == p[j] ? nxt[j] : j;
        }else j = nxt[j];
    }
}

int kmp(char * s, char * p){
    int i = 0, j = 0;
    int len = strlen(p);
    while(s[i] && j < len){
        if(j == -1 || s[i] == p[j]){
            ++i;
            ++j;
        }else j = nxt[j];
    }
    if(j == len) return i - j + 1;
    return 0;
}

int main(){
    char str[110], substr[110];
    int t = 3;
    while(t--){
        scanf("%s%s", str, substr);
        getNext(substr);
        printf("%d\n", kmp(str, substr));
    }
    return 0;
}
