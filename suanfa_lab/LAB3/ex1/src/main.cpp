#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdio.h>
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
#define nul -1
typedef struct 
{
    int i;
    int p;//父节点
    int d;//最短距离
}node;//存放结果的结构
void INITIALIZE_SINGLE_SOURCE(node* result,int s,int size)
{
    for(int i=1;i<size;i++)
    {
        result[i].d=maxl;
        result[i].p=nul;
    }
    result[0].d=0;
}
void relax(node *result,int **map,int u,int v)
{
    if(result[v].d>result[u].d+map[u][v])
    {
        result[v].d=result[u].d+map[u][v];
        result[v].p=u;
    }
}
int BELLMAN_FORD(node *result,int** map,int s,int size)
{
     INITIALIZE_SINGLE_SOURCE(result,0,size);
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
int main()
{
    int n;
    auto data1=fopen("../input/input11.txt","r");
    auto data2=fopen("../input/input12.txt","r");
    auto data3=fopen("../input/input21.txt","r");
    auto data4=fopen("../input/input22.txt","r");
    auto data5=fopen("../input/input31.txt","r");
    auto data6=fopen("../input/input32.txt","r");
    auto data7=fopen("../input/input41.txt","r");
    auto data8=fopen("../input/input42.txt","r");
    if(!data1){cout<<"open failed!"; system("pause");exit(0);}
    node result11[size1];
    node result12[size1];
    node result21[size2];
    node result22[size2];
    node result31[size3];
    node result32[size3];
    node result41[size4];
    node result42[size4];   
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
    auto t1 = std::chrono::steady_clock::now();
    BELLMAN_FORD(result11,map1,0,size1);
    auto t2 = std::chrono::steady_clock::now();
    BELLMAN_FORD(result12,map2,0,size1);
    auto t3 = std::chrono::steady_clock::now();
    BELLMAN_FORD(result21,map3,0,size2);
    auto t4 = std::chrono::steady_clock::now();
    BELLMAN_FORD(result22,map4,0,size2);
    auto t5 = std::chrono::steady_clock::now();
    BELLMAN_FORD(result31,map5,0,size3);
    auto t6 = std::chrono::steady_clock::now();
    BELLMAN_FORD(result32,map6,0,size3);
    auto t7 = std::chrono::steady_clock::now();
    BELLMAN_FORD(result41,map7,0,size4);
    auto t8 = std::chrono::steady_clock::now();
    BELLMAN_FORD(result42,map8,0,size4);
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
    ofstream outf1("../output/result11.txt");
    if(!outf1){cout<<"outfile failed";}
    for(int i=1;i<size1;i++)
    {
        if(result11[i].d<maxl)
        {
            outf1<<0<<","<<i<<","<<result11[i].d<<";";
            stack<int> s;
            int j=i;
            while(j!=0)
            {
                s.push(j);
                j=result11[j].p;
            }
            s.push(0);
            while(!s.empty())
            {
                int y=s.top();
                s.pop();
                outf1<<y;
                if(y!=i)outf1<<",";
            }
            outf1<<endl;
        }
    }
    ofstream outf2("../output/result12.txt");
    if(!outf2){cout<<"outfile failed";}
    for(int i=1;i<size1;i++)
    {
        if(result12[i].d<maxl)
        {
            outf2<<0<<","<<i<<","<<result12[i].d<<";";
            stack<int> s;
            int j=i;
            while(j!=0)
            {
                s.push(j);
                j=result12[j].p;
            }
            s.push(0);
            while(!s.empty())
            {
                int y=s.top();
                s.pop();
                outf2<<y;
                if(y!=i)outf2<<",";
            }
            outf2<<endl;
        }
    }
    ofstream outf3("../output/result21.txt");
    if(!outf3){cout<<"outfile failed";}
    for(int i=1;i<size2;i++)
    {
        if(result21[i].d<8999)
        {
            outf3<<0<<","<<i<<","<<result21[i].d<<";";
            stack<int> s;
            int j=i;
            while(j!=0)
            {
                s.push(j);
                j=result21[j].p;
            }
            s.push(0);
            while(!s.empty())
            {
                int y=s.top();
                s.pop();
                outf3<<y;
                if(y!=i)outf3<<",";
            }
            outf3<<endl;
        }
    }
    ofstream outf4("../output/result22.txt");
    if(!outf4){cout<<"outfile failed";}
    for(int i=1;i<size2;i++)
    {
        if(result22[i].d<9999)
        {
            outf4<<0<<","<<i<<","<<result22[i].d<<";";
            stack<int> s;
            int j=i;
            while(j!=0)
            {
                s.push(j);
                j=result22[j].p;
            }
            s.push(0);
            while(!s.empty())
            {
                int y=s.top();
                s.pop();
                outf4<<y;
                if(y!=i)outf4<<",";
            }
            outf4<<endl;
        }
    }
    ofstream outf5("../output/result31.txt");
    if(!outf5){cout<<"outfile failed";}
    for(int i=1;i<size3;i++)
    {
        if(result31[i].d<9999)
        {
            outf5<<0<<","<<i<<","<<result31[i].d<<";";
            stack<int> s;
            int j=i;
            while(j!=0)
            {
                s.push(j);
                j=result31[j].p;
            }
            s.push(0);
            while(!s.empty())
            {
                int y=s.top();
                s.pop();
                outf5<<y;
                if(y!=i)outf5<<",";
            }
            outf5<<endl;
        }
    }
    ofstream outf6("../output/result32.txt");
    if(!outf6){cout<<"outfile failed";}
    for(int i=1;i<size3;i++)
    {
        if(result32[i].d<9999)
        {
            outf6<<0<<","<<i<<","<<result32[i].d<<";";
            stack<int> s;
            int j=i;
            while(j!=0)
            {
                s.push(j);
                j=result32[j].p;
            }
            s.push(0);
            while(!s.empty())
            {
                int y=s.top();
                s.pop();
                outf6<<y;
                if(y!=i)outf6<<",";
            }
            outf6<<endl;
        }
    }
    ofstream outf7("../output/result41.txt");
    if(!outf7){cout<<"outfile failed";}
    for(int i=1;i<size4;i++)
    {
        if(result41[i].d<9999)
        {
            outf7<<0<<","<<i<<","<<result41[i].d<<";";
            stack<int> s;
            int j=i;
            while(j!=0)
            {
                s.push(j);
                j=result41[j].p;
            }
            s.push(0);
            while(!s.empty())
            {
                int y=s.top();
                s.pop();
                outf7<<y;
                if(y!=i)outf7<<",";
            }
            outf7<<endl;
        }
    }
    ofstream outf8("../output/result42.txt");
    if(!outf8){cout<<"outfile failed"; system("pause");}
    for(int i=1;i<size4;i++)
    {
        if(result42[i].d<9999)
        {
            outf8<<0<<","<<i<<","<<result42[i].d<<";";
            stack<int> s;
            int j=i;
            while(j!=0)
            {
                s.push(j);
                j=result42[j].p;
            }
            s.push(0);
            while(!s.empty())
            {
                int y=s.top();
                s.pop();
                outf8<<y;
                if(y!=i)outf8<<",";
            }
            outf8<<endl;
        }
    }
    system("pause");
    return(0);
}
