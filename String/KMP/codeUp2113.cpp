#include <bits/stdc++.h>
using namespace std;



int main(){
    freopen("in.txt", "r", stdin);
    char str[10010];
    gets(str);
    int len = strlen(str);
    int blank = 0;
    int alphaB = 0;
    int alphaS = 0;
    int digit = 0;
    for(int i = 0; i < len; ++i){
        if(str[i] == ' ') blank++;
        else
            if(str[i] >= '0' && str[i] <= '9') ++digit;
            else
                if(str[i] >= 'A' && str[i] <= 'Z') ++alphaB;
                else ++alphaS;
    }
    printf("%d %d %d %d\n", alphaB, alphaS, digit, blank);
    return 0;
}
