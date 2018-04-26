#include <bits/stdc++.h>
using namespace std;
typedef char AtomType;
struct Glist{
    bool tag;
    union{
        AtomType atom;
        struct Node{
            Glist * hp;
            Glist * tp;
        }ptr;
    }u;
    Glist(bool tag = true){
        this->tag = tag;
    }
};

namespace Solution{
    void split(string &l, string &s){
        int k = 0;
        int pos = 0;
        do{
            if(s[pos] == '(') ++k;
            if(s[pos] == ')') --k;
            ++pos;
        }while(pos < s.length() && (s[pos] != ',' || k != 0));
        l = s.substr(0, pos);
        if(pos < s.length() - 1) s = s.substr(pos + 1);
        else s = "";
    }
    Glist * solve(string s){
        if(s == "()") return NULL;
        Glist * l = new Glist();
        if(s.length() == 1){
            l->tag = false;
            l->u.atom = s[0];
            return l;
        }
        s = s.substr(1, s.length() - 2);
        string left;
        Glist * p = l;
        do{
            //cout << "F: " << s << endl;
            split(left, s);
            //cout << left << " " << s << endl;
            p->u.ptr.hp = solve(left);
            if(s != ""){
                Glist * q = new Glist();
                p->u.ptr.tp = q;
                p = q;
            }
        }while(s != "");
        p->u.ptr.tp = NULL;
        //s.su
        return l;
    }

    int length(Glist * l){
        int len = 0;
        while(l){
            ++len;
            l = l->u.ptr.tp;
        }
        return len;
    }

    int depth(Glist * l){
        if(l == NULL || l->tag == false) return 0;
        int mx = 0;
        for(Glist * cur = l; cur; cur = cur->u.ptr.tp)
            mx = max(mx, depth(cur->u.ptr.hp));
        return mx + 1;
    }
}

void Print(Glist * x){
    if(x == NULL || x->tag == false){
        if(x == NULL) printf("()");
        else printf("%c", x->u.atom);
        return;
    }
    printf("(");
    while(x){
        Print(x->u.ptr.hp);
        x = x->u.ptr.tp;
        if(x) printf(",");
    }
    printf(")");
}

int main(){
    Glist * l = Solution::solve("((),a,(b,c),(b,(d,c,b)))");
    Print(l);
    printf("\n%d\n", Solution::length(l));
    printf("%d\n", Solution::depth(l));
    return 0;
}
