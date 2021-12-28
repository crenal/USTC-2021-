#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdio.h>
#include <chrono>
using namespace std;
typedef struct node
{
    node *p;
    int rank;
}node;
node *makeset(node *n)
{
    n->p=n;
    n->rank=0;
    return n;
}
node *FIND_SET(node *x)
{
    if(x!=x->p)
        x->p=FIND_SET(x->p);
    return(x->p);
}
void LINK(node* x,node* y)
{
    if(x->rank>y->rank)
        y->p=x;
    else 
    {
        x->p=y;
        if(x->rank==y->rank)
        y->rank++;
    }
}
void UNION(node *x,node *y)
{
    LINK(FIND_SET(x),FIND_SET(y));
}
int main()
{
    ofstream outf("..\\output\\result.txt");
    ofstream outf2("..\\output\\time.txt");
    auto data=fopen("..\\input\\2_2_input.txt","r");    
    if(!data){cout<<"open file failed"<<endl; exit(0);}
    int result=0;//结果（群体数）
    auto t1 = std::chrono::steady_clock::now();
    //N=10
    int size;//人数
    int a[30][30]; 
    size=10;
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            fscanf(data,"%d",&a[i][j]);
    auto family1=(node **)malloc(sizeof(node*)*size);
    for(int i=0;i<size;i++)
        {
            family1[i]=(node *)malloc(sizeof(node));
            makeset(family1[i]);
        }
    for(int i=0;i<size;i++)
        for(int j=0;j<i;j++)
        {
            if(a[i][j]==1)
            UNION(family1[i],family1[j]);
        }
    for(int i=0;i<size;i++)
    {
        if(family1[i]->p== family1[i])
        result++;
    }
    outf<<"n=10 "<<result<<endl;
    outf2<<"n=10 ";
    result=0;
    auto t2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_span1 = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    outf2<<time_span1.count()<<"s"<<endl;
    //N=15
    size=15;
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            fscanf(data,"%d",&a[i][j]);
    auto family2=(node **)malloc(sizeof(node*)*size);
    for(int i=0;i<size;i++)
        {
            family2[i]=(node *)malloc(sizeof(node));
            makeset(family2[i]);
        }
    for(int i=0;i<size;i++)
        for(int j=0;j<i;j++)
        {
            if(a[i][j]==1)
            UNION(family2[i],family2[j]);
        }
    for(int i=0;i<size;i++)
    {
        if(family2[i]->p== family2[i])
        result++;
    }
    outf<<"n=15 "<<result<<endl;
    outf2<<"n=15 ";
    result=0;
    auto t3 = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_span2 = std::chrono::duration_cast<std::chrono::duration<double>>(t3 - t2);
    outf2<<time_span2.count()<<"s"<<endl;
    //N=20
    size=20;
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            fscanf(data,"%d",&a[i][j]);
    auto family3=(node **)malloc(sizeof(node*)*size);
    for(int i=0;i<size;i++)
        {
            family3[i]=(node *)malloc(sizeof(node));
            makeset(family3[i]);
        }
    for(int i=0;i<size;i++)
        for(int j=0;j<i;j++)
        {
            if(a[i][j]==1)
            UNION(family3[i],family3[j]);
        }
    for(int i=0;i<size;i++)
    {
        if(family3[i]->p== family3[i])
        result++;
    }
    outf<<"n=20 "<<result<<endl;
    outf2<<"n=20 ";
    result=0;
    auto t4 = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_span3 = std::chrono::duration_cast<std::chrono::duration<double>>(t4 - t3);
    outf2<<time_span3.count()<<"s"<<endl;
    //N=25  
    size=25;
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            fscanf(data,"%d",&a[i][j]);
    auto family4=(node **)malloc(sizeof(node*)*size);
    for(int i=0;i<size;i++)
        {
            family4[i]=(node *)malloc(sizeof(node));
            makeset(family4[i]);
        }
    for(int i=0;i<size;i++)
        for(int j=0;j<i;j++)
        {
            if(a[i][j]==1)
            UNION(family4[i],family4[j]);
        }
    for(int i=0;i<size;i++)
    {
        if(family4[i]->p== family4[i])
        result++;
    }
    outf<<"n=25 "<<result<<endl;
    outf2<<"n=25 ";
    result=0;
    auto t5 = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_span4 = std::chrono::duration_cast<std::chrono::duration<double>>(t5 - t4);
    outf2<<time_span4.count()<<"s"<<endl;
    //N=30  
    size=30;
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            fscanf(data,"%d",&a[i][j]);
    auto family5=(node **)malloc(sizeof(node*)*size);
    for(int i=0;i<size;i++)
        {
            family5[i]=(node *)malloc(sizeof(node));
            makeset(family5[i]);
        }
    for(int i=0;i<size;i++)
        for(int j=0;j<i;j++)
        {
            if(a[i][j]==1)
            UNION(family5[i],family5[j]);
        }
    for(int i=0;i<size;i++)
    {
        if(family5[i]->p== family5[i])
        result++;
    }
    outf<<"n=30 "<<result<<endl;
    outf2<<"n=30 ";
    result=0;
    auto t6 = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_span5 = std::chrono::duration_cast<std::chrono::duration<double>>(t6 - t5);
    outf2<<time_span5.count()<<"s"<<endl;
    return(0);
}

