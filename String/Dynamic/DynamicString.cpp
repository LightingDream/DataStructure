#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 110
typedef struct{
   char *ch;
   int len;
}Str;

int strLength(const char *p){		//获取串长
   int len = 0;
   while(*p){
       ++p;
       ++len;
   }
   return len;
}

void strAssign(Str &str, const char *p){	//赋值
   int length = strLength(p);
   if(length == 0) {					   //空串
       free(str.ch);
       str.ch == NULL;
   }
   else {
       str.ch = (char *)malloc((length + 1) * sizeof(char)); //开辟空间
       for(int i = 0; i <= length; ++i)			//赋值[0, len],p[len]为'\0'
       	str.ch[i] = p[i];
	}
   str.len = length;
}

int StrLength(Str str){
	return str.len;
}

int strCompare(Str s1, Str s2){					//按字典序比较
   for(int i = 0; i < s1.len && i < s2.len; ++i)
       if(s1.ch[i] != s2.ch[i])
           return s1.ch[i] - s2.ch[i];
   return s1.len - s2.len;
}

int index(Str str, Str substr){
    int len1 = StrLength(str);
    int len2 = StrLength(substr);
    for(int i = 0; i <= len1 - len2; ++i){
        int j, k = i;
        for(j = 0; j < len2 && str.ch[k] == substr.ch[j]; ++k, ++j);
        if(j == len2) return i;
    }
    return -1;
}

void strPrint(Str str){
   if(str.len == 0) {
       printf("\n");
       return;
   }
   printf("%s\n", str.ch);
}

int nxt[MAX_SIZE + 1];//index from 1
void getNext(Str substr){
    nxt[0] = -1;
    int i = 0, j = -1;
    while(i < StrLength(substr)){
        if(j == -1 || substr.ch[i] == substr.ch[j]){
            ++i;
            ++j;
            nxt[i] = j;
        }else j = nxt[j];
    }
}

int kmp(Str str, Str substr){
    getNext(substr);
    int i = 0, j = 0;
    while(i < StrLength(str) && j < StrLength(substr)){
        if(j == -1 || str.ch[i] == substr.ch[j]){
            ++i;
            ++j;
        }else j = nxt[j];
    }
    if(j == StrLength(substr)) return i - j;
    return -1;
}

int main(){
    Str str;
    Str substr;
    strAssign(str, "adrui");
    strAssign(substr, "ui");
    strPrint(str);
    strPrint(substr);
    printf("%d\n", index(str, substr));
    printf("%d\n", kmp(str, substr));
    return 0;
}
