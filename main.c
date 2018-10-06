/*DFS遍历邻接表*/
#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX_NUM 20
#define STACK_INIT_SIZE 20
#define STACKINCREMENT 10
typedef struct ArcNode
{
    int adjvex;               //指向顶点的弧
    struct ArcNode *nextarc;   //指向下一条弧的指针
} ArcNode;

typedef struct VNode
{
    char data;             //顶点信息
    ArcNode *firstarc;    //指向第一条依附该顶点的弧的指针
} VNode,AdjList[MAX_VERTEX_NUM];

typedef struct
{
    AdjList vertices;
    int vexnum,arcnum;   //无向图顶点数和弧数
} ALGraph;

typedef struct{
    char *base;
    char *top;
    int stacksize;
} Stack;      //栈结构体
int visited[MAX_VERTEX_NUM];//访问标志数组

void InitStack(Stack *S)
{
    //初始化栈
    S->base=(char *)malloc(STACK_INIT_SIZE*sizeof(char));
    if(!S->base) exit(1);
    S->top=S->base;
    S->stacksize=STACK_INIT_SIZE;
}

int isEmpty(Stack *S)
{
    //栈为空返回true,否则返回false
    if(S->top-S->base==0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void Push(Stack *S,char e)
{
    //入栈
    if(S->top-S->base>=S->stacksize)
    {
        S->base=(char *)realloc(S->base, (S->stacksize+STACKINCREMENT) * sizeof(char));
        if(!S->base)
        {
            exit(1);
        }
        else
        {
            S->top=S->base+S->stacksize;
            S->stacksize+=STACKINCREMENT;
        }
    }
    *S->top++=e;
}

char Pop(Stack *S)
{
    //栈顶元素出栈，用e返回值
    char e;
    if(S->top==S->base)
        exit(1);
    e=*--(*S).top;
    return e;
}
int LocateVex(ALGraph G,char v)
{
    /*寻找两个定点在矩阵中的位置*/
    int i;
    for(i=0; i<G.vexnum; i++)
    {
        if(G.vertices[i].data==v)
            return i;
    }
    return -1;
}
void Creat_T(ALGraph *G)
{
    /*创建邻接表*/
    int i,m,n;
    char v1,v2;
    ArcNode *p,*q;
    p=NULL;
    q=NULL;//防止野指针
    printf("请输入无向图的顶点数:\n");
    scanf("%d",&G->vexnum);
    printf("请输入无向图的边数:\n");
    scanf("%d",&G->arcnum);
    printf("请输入顶点信息：\n");
    for(i=0; i<G->vexnum; i++)
    {
        fflush(stdin);
        scanf("%c",&G->vertices[i].data);
        G->vertices[i].firstarc=NULL;   //初始化该指针
    }
    printf("请输入边：\n");
    for(i=0; i<G->arcnum; i++)
    {
        fflush(stdin);
        scanf("%c%c",&v1,&v2);
        m=LocateVex(*G,v1);
        n=LocateVex(*G,v2);
        p=(ArcNode *)malloc(sizeof(ArcNode));
        if(!p) exit(1);
        p->nextarc=NULL;
        p->adjvex=-1;
        p->adjvex=m;
        p->nextarc=G->vertices[n].firstarc;
        G->vertices[n].firstarc=p;
        q=(ArcNode *)malloc(sizeof(ArcNode));
        if(!p) exit(1);
        q->nextarc=NULL;
        q->adjvex=n;
        q->nextarc=G->vertices[m].firstarc;
        G->vertices[m].firstarc=q;
    }
}
void DFSTraverse(ALGraph *G,Stack *s)
{
    //深度优先遍历无向图邻接表
    int i,n;
    char v;
    ArcNode *p;
    p=NULL;
    for(i=0; i<G->vexnum; i++)
    {
        visited[i]=0;
    }
    for(i=0; i<G->vexnum; i++)
    {
        if(!visited[i])
        {
            visited[i]=1;
            printf("%c->",G->vertices[i].data);
            Push(s,G->vertices[i].data);
            p=G->vertices[i].firstarc;
            while(!isEmpty(s))
            {
                while(p)
                {
                    if(!visited[p->adjvex])
                    {
                        visited[p->adjvex]=1;
                        printf("%c->",G->vertices[p->adjvex].data);
                        Push(s,G->vertices[i].data);
                        p=G->vertices[p->adjvex].firstarc;
                    }
                    else
                        p=p->nextarc;
                }//while
                v=Pop(s);
                n=LocateVex(*G,v);
                p=G->vertices[n].firstarc;
            }//while
        }//IF
    }//for
    printf("NULL\n");
    free(p);
}

int main()
{
    /*测试函数*/
    ALGraph  G;
    Stack s;//申请栈
    InitStack(&s);//初始化栈
    Creat_T(&G);//建立邻接表
    DFSTraverse(&G,&s);//DFS
    return 0;
}
