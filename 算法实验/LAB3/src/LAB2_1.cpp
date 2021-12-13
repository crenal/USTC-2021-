#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdio.h>
#include <chrono>
using namespace std;
typedef struct Fibnode
{
    int mark;
    int degree;
    Fibnode *left;
    Fibnode *right;
    Fibnode *child;
    Fibnode *parent;
    int key;
}Fibnode;
Fibnode* a[1000];
typedef struct 
{
    int n;
    Fibnode *min;
}Fib_Heap;
Fibnode *CreateFibnode(int key)//建结点
{
    auto node=new Fibnode;
    node->mark=0;
    node->degree=0;
    node->left=node;
    node->right=node;
    node->child=NULL;
    node->parent=NULL;
    node->key=key;    
    return node;

}
Fib_Heap* Createheap()//建堆
{
    auto heap=new Fib_Heap;
    heap->n=0;
    heap->min=NULL;
}
int INSERT(Fib_Heap* heap,int z)//插入结点 根链表设计为双向循环链表
{
    auto y=heap->min;
    auto x=CreateFibnode(z);
    x->degree=0;
    x->parent=NULL;
    x->child=NULL;
    x->mark=0;
    if(y==NULL)
    {
        heap->min=x;
    }
    else
    {
        y->left->right=x;
        x->left=y->left;
        x->right=y;
        y->left=x;
    }
    heap->n++;
    if(z< heap->min->key) heap->min=x;
    a[z]=x;
    return(heap->n);
}
int MINIMUM(Fib_Heap* heap)//返回最小值
{
    return(heap->min->key);
}
int log(int n)//为了求A数组要多少元素
{
    float i = 1;
    int cnt = 0;
    while (i*1.5< n)
    {
        i *= 1.5;
        ++cnt;
    }
    return cnt+30;
}
void FIB_HEAP_LINK(Fib_Heap* heap,Fibnode* y,Fibnode* x)//将y插到x孩子中
{
    y->left->right=y->right;
    y->right->left=y->left;
    y->right=y;
    y->left=y;
    if(x->degree==0)
        x->child=y;
    else
    {
        x->child->left->right=y;
        y->left=x->child->left;
        y->right=x->child;
        x->child->left=y;
    }
    x->degree++;
    y->parent=x;
    y->mark=0;
}
void CONSOLIDATE(Fib_Heap* heap)//合并
{   
    auto u=heap->min;
    int k=u->key;
    int j;
    for(j=1;;j++)
    {
        u=u->right;
        if(u->key==k) break;
    }
    int m = heap->n;
    auto logm=log(m);
    auto A=(Fibnode**)malloc(sizeof(Fibnode*)*logm);
    for(int i=0;i<logm;i++) A[i]=NULL;
    auto w=heap->min;
    int flag=1;
    for(int i=0;i<j;i++)
    {
        auto x=w;
        w=x->right;
        auto d=x->degree;
        while(A[d]!=NULL)
        {
            auto y=A[d];
            if(x->key>y->key)
            {
                auto z=x;
                x=y;
                y=z;
            }
            FIB_HEAP_LINK(heap, y,x);
            A[d]=NULL;
            d++;
        }
        A[d]=x;
    }
    heap->min=NULL;
    for(int i=0;i<logm;i++)
    {
        if(A[i]!=NULL)
        {
            if(heap->min==NULL)
            {
                heap->min=A[i];
                heap->min->left=heap->min;
                heap->min->right=heap->min;
            }
            else
            {
                heap->min->left->right=A[i];
                A[i]->left=heap->min->left;
                A[i]->right=heap->min;
                heap->min->left=A[i];
            } 
            if(A[i]->key<heap->min->key)
            heap->min=A[i];
        }
    }
}
Fib_Heap* UNION(Fib_Heap* h1,Fib_Heap* h2)//根链表连在一起
{
    auto H=Createheap();
    H->min=h1->min;
    H->min->right->left=h2->min->left;
    h2->min->left->right=H->min->right;
    H->min->right=h2->min;
    h2->min->left= H->min;
    if(h1->min==NULL||h2->min!=NULL&&h2->min->key<h1->min->key)
    H->min=h2->min;
    H->n=h1->n+h2->n;
    return H;
}
void CUT(Fib_Heap* heap,Fibnode* x,Fibnode* y)
{
    if(y->degree==1)
    {
        y->degree--;
        y->child=NULL;
        x->parent=NULL;
    }
    else
    {
        y->degree--;
        if(y->child==x)y->child=x->left;
        x->parent=NULL;
        x->left->right=x->right;
        x->right->left=x->left;
        x->left=x;
        x->right=x;
    }
    x->mark=0;
    heap->min->left->right=x;
    x->left=heap->min->left;
    x->right=heap->min;
    heap->min->left=x;
}

void CASCADING_CUT(Fib_Heap* heap,Fibnode* y)
{
    auto z=y->parent;
    if(z!=NULL)
    {
        if(y->mark==0)
        y->mark=1;
    
    else 
    {
        CUT(heap,y,z);
        CASCADING_CUT(heap,z);
    }
    }
}
int DECREASE_KEY(Fib_Heap* heap,int x,int k)//降低节点的KEY
{
    if(k>x){cout<<"newkey is greater than currentkey"<<endl;exit(0);}
    auto y=a[x];
    y->key=k;
    auto z=y->parent;
    if(z!=NULL&&y->key<z->key)
    {
        CUT(heap,y,z);
        CASCADING_CUT(heap,z);
    }
    if(y->key<heap->min->key) heap->min=y;
    return(heap->min->key);
}

int extractMin(Fib_Heap* heap)//抽取最小结点
{
    auto z=heap->min;
    int k=z->key;
    if(z!=NULL)
    {
        auto x=z->child;
        for(int i=0;i<z->degree;i++)
        {
            auto w=x->right;
            x->parent=NULL;
            heap->min->left->right=x;
            x->left=heap->min->left;
            x->right=heap->min;
            heap->min->left=x;
            x=w;
        }
        heap->min->left->right= heap->min->right;
        heap->min->right->left= heap->min->left;//删除min结点
        if(z==z->right)
            heap->min=NULL;
        else
        {
            heap->min=z->right;
            CONSOLIDATE(heap);
        }
        heap->n--;
    }
    return(k);
}
int DELETE(Fib_Heap* heap,int y)//删除key为y的结点
{
    DECREASE_KEY(heap,y,-1000);
    extractMin(heap);
    return(heap->n);
}
int main()
{   ofstream outf("LAB3\\output\\result.txt");
    ofstream outf2("LAB3\\output\\time.txt");
    auto data=fopen("LAB3\\input\\2_1_input.txt","r"); 
    if(!data){cout<<"open file failed"<<endl; exit(0);}
    int n;
    auto H1=Createheap();//建堆
    auto H2=Createheap();
    auto H3=Createheap();
    auto H4=Createheap();
    auto H5=Createheap();
    for(int i=0;i<500;i++)//输入
    {
        fscanf(data,"%d",&n);
        if(i<50) INSERT(H1,n);
        else if(i<150)INSERT(H2,n);
        else if(i<300)INSERT(H3,n);
        else if(i<500)INSERT(H4,n);
    }
    auto t1 = std::chrono::steady_clock::now();
    outf<<"H1"<<endl;
    outf<<INSERT(H1,249)<<",";//结果
    outf<<INSERT(H1,830)<<",";
    outf<<MINIMUM(H1)<<",";
    outf<<DELETE(H1,127)<<",";
    outf<<DELETE(H1,141)<<",";
    outf<<MINIMUM(H1)<<",";
    outf<<DECREASE_KEY(H1,75,61)<<",";
    outf<<DECREASE_KEY(H1,198,169)<<","; 
    outf<<extractMin(H1)<<",";
    outf<<extractMin(H1)<<endl;
    auto t2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_span1 = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    outf2<<time_span1.count()<<"s"<<endl;
    outf<<"H2"<<endl;
    outf<<INSERT(H2,816)<<",";//结果
    outf<<MINIMUM(H2)<<",";
    outf<<INSERT(H2,345)<<",";
    outf<<extractMin(H2)<<",";
    outf<<DELETE(H2,504)<<",";
    outf<<DELETE(H2,203)<<",";
    outf<<DECREASE_KEY(H2,296,87)<<",";
    outf<<DECREASE_KEY(H2,278,258)<<","; 
    outf<<MINIMUM(H2)<<",";
    outf<<extractMin(H2)<<endl;
    auto t3 = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_span2 = std::chrono::duration_cast<std::chrono::duration<double>>(t3 - t2);
    outf2<<time_span2.count()<<"s"<<endl;
    outf<<"H3"<<endl;
    outf<<extractMin(H3)<<",";//结果
    outf<<MINIMUM(H3)<<",";
    outf<<INSERT(H3,262)<<",";
    outf<<extractMin(H3)<<",";
    outf<<INSERT(H3,832)<<",";
    outf<<MINIMUM(H3)<<",";
    outf<<DELETE(H3,134)<<",";
    outf<<DELETE(H3,177)<<","; 
    outf<<DECREASE_KEY(H3,617,360)<<",";
    outf<<DECREASE_KEY(H3,889,353)<<endl;
    auto t4 = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_span3 = std::chrono::duration_cast<std::chrono::duration<double>>(t4 - t3);
    outf2<<time_span3.count()<<"s"<<endl;
    outf<<"H4"<<endl;
    outf<<MINIMUM(H4)<<",";//结果
    outf<<DELETE(H4,708)<<",";
    outf<<INSERT(H4,281)<<",";
    outf<<INSERT(H4,347)<<",";
    outf<<MINIMUM(H4)<<",";
    outf<<DELETE(H4,415)<<",";
    outf<<extractMin(H4)<<",";
    outf<<DECREASE_KEY(H4,620,354)<<","; 
    outf<<DECREASE_KEY(H4,410,80)<<",";
    outf<<extractMin(H4)<<endl;
    auto t5 = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_span4 = std::chrono::duration_cast<std::chrono::duration<double>>(t5 - t4);
    outf2<<time_span4.count()<<"s"<<endl;
    H5=UNION(UNION(UNION(H1,H2),H3),H4);
    outf<<"H5"<<endl;
    outf<<extractMin(H5)<<",";//结果
    outf<<MINIMUM(H5)<<",";
    outf<<DELETE(H5,800)<<",";
    outf<<INSERT(H5,267)<<",";
    outf<<INSERT(H5,351)<<",";
    outf<<extractMin(H5)<<",";
    outf<<DECREASE_KEY(H5,478,444)<<",";
    outf<<DECREASE_KEY(H5,559,456)<<","; 
    outf<<MINIMUM(H5)<<",";
    outf<<DELETE(H5,929)<<endl;
    auto t6 = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_span5 = std::chrono::duration_cast<std::chrono::duration<double>>(t6 - t5);
    outf2<<time_span5.count()<<"s"<<endl;

    system("pause");
    return(0);
}


