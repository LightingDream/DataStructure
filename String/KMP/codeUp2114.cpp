#include <bits/stdc++.h>
using namespace std;


inline bool check(char ch){
    return ch >= 'a' && ch <= 'z';
}

int main(){
    freopen("in.txt", "r", stdin);
    char str[2010];
    gets(str);
    int len = strlen(str);
    bool flag = 1;
    if(len % 2 == 0) flag = 0;
    else{
        if(len == 1 || str[len >> 1] != '&') flag = 0;
        else
            for(int i = 0; i < len >> 1; ++i)
                if(!check(str[i]) || str[i] != str[len - 1 - i]){
                    flag = 0;
                    break;
                }
    }
    printf("%s\n", flag ? "YES" : "NO");
    return 0;
}
