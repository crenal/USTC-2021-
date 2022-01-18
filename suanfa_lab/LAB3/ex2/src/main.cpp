#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdio.h>
#include <set>
#include<stack> 
#include<stdlib.h>
#include <windows.h>
#include<string.h>
#include <windows.h>
#include <chrono>
using namespace std;
using namespace std;
#define size1 27
#define size2 81
#define size3 243
#define size4 729
#define maxl 9999
#define minl 9998
#define nul -1
typedef struct 
{
    int i;
    int p;//父节点
    int d;//最短距离
}node;//存放结果的结构
int** tend(int **a,int size)//将二维数组扩充
{
    auto m=new int*[size+1];
    for(int i=0;i<size+1;i++)m[i]=new int[size+1];
    for(int i=0;i<size+1;i++)
    for(int j=0;j<size+1;j++)
    {
        if(i==size) m[i][j]=0;
        else if(j==size) m[i][j]=maxl;
        else m[i][j]=a[i][j];
    }
    for(int i=0;i<size;i++) delete(a[i]);
    delete(a);
    return(m);
}
void INITIALIZE_SINGLE_SOURCE(node* result,int s,int size)//初始化，s是源点
{
    for(int i=0;i<size;i++)
    {
        result[i].d=maxl;
        result[i].p=nul;
    }
    result[s].d=0;
}
void relax(node *result,int **map,int u,int v)//松弛操作
{
    if(result[v].d>result[u].d+map[u][v])
    {
        result[v].d=result[u].d+map[u][v];
        result[v].p=u;
    }
}
int BELLMAN_FORD(node *result,int** map,int s,int size)//BELLMAN_FORD算法
{
     INITIALIZE_SINGLE_SOURCE(result,s,size);
     for(int i=1;i<size;i++)
     {
         for(int j=0;j<size;j++)
         {
             for(int k=0;k<size;k++)
             {
                 if(map[j][k]!=maxl)
                 {
                     relax(result,map,j,k);
                 }
             }
         }
     }
    for(int j=0;j<size;j++)
         {
             for(int k=0;k<size;k++)
             {
                 if(result[j].d>result[k].d+map[j][k])
                 return(0);
             }
         }
    return 1;
}
void change_var(int** m,node* r,int size)//变换边的权值
{
    for(int i=0;i<size;i++)
    for(int j=0;j<size;j++)
    {
        if(m[i][j]==maxl) m[i][j]=maxl;
        else m[i][j]=m[i][j]+r[i].d-r[j].d;
    }
}
int EXTRACT_MIN(vector<int> &Q,node* G)//DIJKSTRA用到的 在Q集合中取出最小权值元素
{
    int i,j=maxl,k;
    auto iter=Q.begin();
    vector<int>::iterator it;
    for(;iter!=Q.end();iter++)
    {
        i=*iter;
        if(G[i].d<=j)
        {
            j=G[i].d;
            k=i;
            it=iter;
        }
    }
    Q.erase(it);
    return(k);
}
void DIJKSTRA(node* G,int** map,int s,int size)
{
    INITIALIZE_SINGLE_SOURCE(G,s,size);
    set<int> S;
    vector<int> Q;
    for(int i=0;i<size;i++)
    {
        Q.push_back(i);
    }
    
    while(!Q.empty())
    {
        auto u=EXTRACT_MIN(Q,G); 
        S.insert(u);
        for(int j=0;j<size;j++)
        relax(G,map,u,j);
    }
}
void change_var2(node** m,node* r,int size)//变回边的权值
{
    for(int i=0;i<size;i++)
    for(int j=0;j<size;j++)
    {
        if(m[i][j].d==maxl)continue;
        m[i][j].d=m[i][j].d-r[i].d+r[j].d;
    }
}
node** JOHNSON(int **map,int size)
{
    auto m1=tend(map,size);
    auto result=(node*)malloc(sizeof(node)*(size+1));
    BELLMAN_FORD(result,m1,size,size+1);
    change_var(m1,result,size+1);
    auto a=new node*[size+1];//to be returned
    for(int i=0;i<size+1;i++)//to be returned
    a[i]=new node[size+1];//to be returned

    for(int i=0;i<size+1;i++)
    DIJKSTRA(a[i],m1,i,size+1);
    
    change_var2(a,result,size+1);
    return(a);
}
int main()
{
    int n;
    //数据预处理
    auto data1=fopen("../input/input11.txt","r");
    auto data2=fopen("../input/input12.txt","r");
    auto data3=fopen("../input/input21.txt","r");
    auto data4=fopen("../input/input22.txt","r");
    auto data5=fopen("../input/input31.txt","r");
    auto data6=fopen("../input/input32.txt","r");
    auto data7=fopen("../input/input41.txt","r");
    auto data8=fopen("../input/input42.txt","r");
    if (!data1) { cout << "open failed!"; system("pause"); exit(0); }
    int **map1;
    map1=new int*[size1];
    for(int i=0;i<size1;i++)map1[i]=new int[size1]; 
    for(int i=0;i<size1;i++)
        for(int j=0;j<size1;j++)
            {fscanf(data1,"%d",&n);fgetc(data1);if(i!=j&&n==0)n=maxl;map1[i][j]=n;}
    int **map2;
    map2=new int*[size1];
    for(int i=0;i<size1;i++)map2[i]=new int[size1];        
    for(int i=0;i<size1;i++)
        for(int j=0;j<size1;j++)
            {fscanf(data2,"%d",&n);fgetc(data2);if(i!=j&&n==0)n=maxl;map2[i][j]=n;}
    int **map3;
    map3=new int*[size2];
    for(int i=0;i<size2;i++)map3[i]=new int[size2];        
    for(int i=0;i<size2;i++)
        for(int j=0;j<size2;j++)
            {fscanf(data3,"%d",&n);fgetc(data3);if(i!=j&&n==0)n=maxl;map3[i][j]=n;}
    int **map4;
    map4=new int*[size2];
    for(int i=0;i<size2;i++)map4[i]=new int[size2];
    for(int i=0;i<size2;i++)
        for(int j=0;j<size2;j++)
            {fscanf(data4,"%d",&n);fgetc(data4);if(i!=j&&n==0)n=maxl;map4[i][j]=n;}
    int **map5;
    map5=new int*[size3];
    for(int i=0;i<size3;i++)map5[i]=new int[size3];
    for(int i=0;i<size3;i++)
        for(int j=0;j<size3;j++)
            {fscanf(data5,"%d",&n);fgetc(data5);if(i!=j&&n==0)n=maxl;map5[i][j]=n;}
    int **map6;
    map6=new int*[size3];
    for(int i=0;i<size3;i++)map6[i]=new int[size3];
    for(int i=0;i<size3;i++)
        for(int j=0;j<size3;j++)
            {fscanf(data6,"%d",&n);fgetc(data6);if(i!=j&&n==0)n=maxl;map6[i][j]=n;}
    int **map7;
    map7=new int*[size4];
    for(int i=0;i<size4;i++)map7[i]=new int[size4];
    for(int i=0;i<size4;i++)
        for(int j=0;j<size4;j++)
            {fscanf(data7,"%d",&n);fgetc(data7);if(i!=j&&n==0)n=maxl;map7[i][j]=n;}
    int **map8;
    map8=new int*[size4];
    for(int i=0;i<size4;i++)map8[i]=new int[size4];
    for(int i=0;i<size4;i++)
        for(int j=0;j<size4;j++)
            {fscanf(data8,"%d",&n);fgetc(data8);if(i!=j&&n==0)n=maxl;map8[i][j]=n;}
    
    ofstream outf1("../output/result11.txt");
    ofstream outf2("../output/result12.txt");
    ofstream outf3("../output/result21.txt");
    ofstream outf4("../output/result22.txt");
    ofstream outf5("../output/result31.txt");
    ofstream outf6("../output/result32.txt");
    ofstream outf7("../output/result41.txt");
    ofstream outf8("../output/result42.txt");
    auto t1 = std::chrono::steady_clock::now();
    auto A1=JOHNSON(map1,size1);
    auto t2 = std::chrono::steady_clock::now();
    auto A2=JOHNSON(map2,size1);
    auto t3 = std::chrono::steady_clock::now();
    auto A3=JOHNSON(map3,size2);
    auto t4 = std::chrono::steady_clock::now();
    auto A4=JOHNSON(map4,size2);
    auto t5 = std::chrono::steady_clock::now();
    auto A5=JOHNSON(map5,size3);
    auto t6 = std::chrono::steady_clock::now();
    auto A6=JOHNSON(map6,size3);
    auto t7 = std::chrono::steady_clock::now();
    auto A7=JOHNSON(map7,size4);
    auto t8 = std::chrono::steady_clock::now();
    auto A8=JOHNSON(map8,size4);
    auto t9 = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_span1 = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    std::chrono::duration<double> time_span2 = std::chrono::duration_cast<std::chrono::duration<double>>(t3 - t2);
    std::chrono::duration<double> time_span3 = std::chrono::duration_cast<std::chrono::duration<double>>(t4 - t3);
    std::chrono::duration<double> time_span4 = std::chrono::duration_cast<std::chrono::duration<double>>(t5 - t4);
    std::chrono::duration<double> time_span5 = std::chrono::duration_cast<std::chrono::duration<double>>(t6 - t5);
    std::chrono::duration<double> time_span6 = std::chrono::duration_cast<std::chrono::duration<double>>(t7 - t6);
    std::chrono::duration<double> time_span7 = std::chrono::duration_cast<std::chrono::duration<double>>(t8 - t7);
    std::chrono::duration<double> time_span8 = std::chrono::duration_cast<std::chrono::duration<double>>(t9 - t8);
    ofstream outftime("../output/time.txt");
    outftime<<time_span1.count()<<"s"<<endl;
    outftime<<time_span2.count()<<"s"<<endl;
    outftime<<time_span3.count()<<"s"<<endl;
    outftime<<time_span4.count()<<"s"<<endl;
    outftime<<time_span5.count()<<"s"<<endl;
    outftime<<time_span6.count()<<"s"<<endl;
    outftime<<time_span7.count()<<"s"<<endl;
    outftime<<time_span8.count()<<"s"<<endl;
    for(int i=0;i<size1;i++)
    {
        for(int j=0;j<size1;j++)
        {
            if(A1[i][j].d==maxl)outf1<<"X"<<" ";
            else outf1<<A1[i][j].d<<" ";
        }
        outf1<<endl;
    }
     for(int i=0;i<size1;i++)
    {
        for(int j=0;j<size1;j++)
        {
            if(A2[i][j].d==maxl)outf2<<"X"<<" ";
            else outf2<<A2[i][j].d<<" ";
        }
        outf2<<endl;
    }
     for(int i=0;i<size2;i++)
    {
        for(int j=0;j<size2;j++)
        {
            if(A3[i][j].d==maxl)outf3<<"X"<<" ";
            else outf3<<A3[i][j].d<<" ";
        }
        outf3<<endl;
    }
     for(int i=0;i<size2;i++)
    {
        for(int j=0;j<size2;j++)
        {
            if(A4[i][j].d==maxl)outf4<<"X"<<" ";
            else outf4<<A4[i][j].d<<" ";
        }
        outf4<<endl;
    }
     for(int i=0;i<size3;i++)
    {
        for(int j=0;j<size3;j++)
        {
            if(A5[i][j].d==maxl)outf5<<"X"<<" ";
            else outf5<<A5[i][j].d<<" ";
        }
        outf5<<endl;
    }
     for(int i=0;i<size3;i++)
    {
        for(int j=0;j<size3;j++)
        {
            if(A6[i][j].d==maxl)outf6<<"X"<<" ";
            else outf6<<A6[i][j].d<<" ";
        }
        outf6<<endl;
    }
     for(int i=0;i<size4;i++)
    {
        for(int j=0;j<size4;j++)
        {
            if(A7[i][j].d==maxl)outf7<<"X"<<" ";
            else outf7<<A7[i][j].d<<" ";
        }
        outf7<<endl;
    }
    for(int i=0;i<size4;i++)
    {
        for(int j=0;j<size4;j++)
        {
            if(A8[i][j].d==maxl)outf8<<"X"<<" ";
            else outf8<<A8[i][j].d<<" ";
        }
        outf8<<endl;
    }
    system("pause");
    return(0);
}