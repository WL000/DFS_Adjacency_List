/*DFS�����ڽӱ�*/
#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX_NUM 20
#define STACK_INIT_SIZE 20
#define STACKINCREMENT 10
typedef struct ArcNode
{
    int adjvex;               //ָ�򶥵�Ļ�
    struct ArcNode *nextarc;   //ָ����һ������ָ��
} ArcNode;

typedef struct VNode
{
    char data;             //������Ϣ
    ArcNode *firstarc;    //ָ���һ�������ö���Ļ���ָ��
} VNode,AdjList[MAX_VERTEX_NUM];

typedef struct
{
    AdjList vertices;
    int vexnum,arcnum;   //����ͼ�������ͻ���
} ALGraph;

typedef struct{
    char *base;
    char *top;
    int stacksize;
} Stack;      //ջ�ṹ��
int visited[MAX_VERTEX_NUM];//���ʱ�־����

void InitStack(Stack *S)
{
    //��ʼ��ջ
    S->base=(char *)malloc(STACK_INIT_SIZE*sizeof(char));
    if(!S->base) exit(1);
    S->top=S->base;
    S->stacksize=STACK_INIT_SIZE;
}

int isEmpty(Stack *S)
{
    //ջΪ�շ���true,���򷵻�false
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
    //��ջ
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
    //ջ��Ԫ�س�ջ����e����ֵ
    char e;
    if(S->top==S->base)
        exit(1);
    e=*--(*S).top;
    return e;
}
int LocateVex(ALGraph G,char v)
{
    /*Ѱ�����������ھ����е�λ��*/
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
    /*�����ڽӱ�*/
    int i,m,n;
    char v1,v2;
    ArcNode *p,*q;
    p=NULL;
    q=NULL;//��ֹҰָ��
    printf("����������ͼ�Ķ�����:\n");
    scanf("%d",&G->vexnum);
    printf("����������ͼ�ı���:\n");
    scanf("%d",&G->arcnum);
    printf("�����붥����Ϣ��\n");
    for(i=0; i<G->vexnum; i++)
    {
        fflush(stdin);
        scanf("%c",&G->vertices[i].data);
        G->vertices[i].firstarc=NULL;   //��ʼ����ָ��
    }
    printf("������ߣ�\n");
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
    //������ȱ�������ͼ�ڽӱ�
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
    /*���Ժ���*/
    ALGraph  G;
    Stack s;//����ջ
    InitStack(&s);//��ʼ��ջ
    Creat_T(&G);//�����ڽӱ�
    DFSTraverse(&G,&s);//DFS
    return 0;
}
