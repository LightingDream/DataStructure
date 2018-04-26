#include <stdio.h>
#include <stdlib.h>
typedef int Status;
#define True 1
#define False 0

typedef struct{
    char arr[10][11];
}MazeType;

typedef struct{
    int r, c;
}PosType;

typedef struct{
    int ord;
    PosType seat;
    int di;
}ElemType;

typedef struct SElemType{
    ElemType data;
    struct SElemType * next;
}SElemType;

typedef struct {
    SElemType * head;
    int len;
}Stack;

SElemType * NewNode(ElemType e){
    SElemType * res = (SElemType *)malloc(sizeof(SElemType));
    res->data = e;
    res->next = NULL;
    return res;
}

void InitStack(Stack &S){
    //if(S.head != NULL) free(S.head);
    S.head = NewNode({0, {-1, -1}, 0});
    S.len = 0;
}

void Push(Stack &S, ElemType x){
    SElemType * e = NewNode(x);
    e->next = S.head->next;
    S.head->next = e;
    ++S.len;
}

Status StackEmpty(Stack S){
    return S.len == 0;
}

void Pop(Stack &S, ElemType &e){
    if(StackEmpty(S)) return;
    SElemType * tmp = S.head->next;
    e = tmp->data;
    S.head->next = tmp->next;
    free(tmp);
    --S.len;
}

void PrintMaze(MazeType maze){
    for(int i = 0; i < 10; ++i)
        for(int j = 0; j < 10; ++j)
            printf("%c%s", maze.arr[i][j], j == 9 ? "\n" : "");
}

void FootPrint(PosType pos, MazeType &maze){
    maze.arr[pos.r][pos.c] = '*';
}

void MarkPrint(PosType pos, MazeType &maze){
    maze.arr[pos.r][pos.c] = '!';
}

Status Pass(PosType pos, MazeType maze){
    return maze.arr[pos.r][pos.c] == ' ';
}

Status Equals(const PosType a, const PosType b){
    return a.r == b.r && a.c == b.c;
}

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

PosType NextPos(PosType pos, int di){
    return {pos.r + dx[di], pos.c + dy[di]};
}

ElemType Top(Stack S){
    return S.head->next->data;
}

Status MazePath(Stack &S, MazeType &maze, PosType start, PosType end){
    PosType curPos = start;
    ElemType e;
    int curStep;
    do{
        if(Pass(curPos, maze)){
            FootPrint(curPos, maze);
            curStep = StackEmpty(S) ? 1 : Top(S).ord + 1;
            e = {curStep, curPos, 0};
            Push(S, e);
            if(Equals(curPos, end)) return True;
            curPos = NextPos(curPos, 0);
        }else{
            if(!StackEmpty(S)){
                Pop(S, e);
                while(e.di == 3 && !StackEmpty(S)){
                    MarkPrint(e.seat, maze);
                    Pop(S, e);
                }
                if(e.di < 3){
                    e.di++;
                    Push(S, e);
                    curPos = NextPos(e.seat, e.di);
                }
            }
        }
    }while(!StackEmpty(S));
    return False;
}

int main(){
   // freopen("in.txt", "r", stdin);
    MazeType maze;
    PosType start, end;
    for(int i = 0; i < 10; ++i) {
        gets(maze.arr[i]);
        for(int j = 0; j < 10; ++j)
            switch(maze.arr[i][j]){
                case 'S': start = {i, j}, maze.arr[i][j] = ' ';
                    break;
                case 'E': end = {i, j}, maze.arr[i][j] = ' ';
                    break;
                default:
                    break;
            }
    }
    Stack S;
    InitStack(S);
    Status result = MazePath(S, maze, start, end);
    PrintMaze(maze);
    return 0;
}
