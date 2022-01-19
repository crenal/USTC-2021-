#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdio.h>
#include<stack> 
#include<math.h>
#include<stdlib.h>
#include <windows.h>
#include<string.h>
#include <windows.h>
#include <chrono>
using namespace std;
int *COMPUTE_PREFIX_FUNCTION(vector<char> P)
{
   auto m=P.size();//P
   auto u=new int[m];//0..m-1
   u[1]=0;
   int k=0;
   for(int q=2;q<m;q++)
   {
       while(k>0&&P[k+1]!=P[q])
          k=u[k];
       if(P[k+1]==P[q])
          k++;
       u[q]=k;
   }
   return(u);
}
ofstream outf("../output/result.txt");
ofstream outf2("../output/time.txt");
void KMP_MATCHER(vector<char> T,vector<char> P)
{
    auto t1 = std::chrono::steady_clock::now();
    int a[2];int o=0;
    auto n=T.size();
    auto m=P.size();
    auto u=COMPUTE_PREFIX_FUNCTION(P);
    int q=0;
    int k=0;
    for(int i=1;i<n;i++)
    {
        while(q>0&&P[q+1]!=T[i])
           {
               q=u[q];
           }
        if(P[q+1]==T[i])
           q++;
        if(q==m-1)
        {
           k++;
           a[o++]=i-m+2; //下表从1开始 应+2
           q=u[q];
        }
    }
    outf<<k<<endl;
    for(int i=1;i<m;i++) outf<<u[i]<<" ";
    outf<<endl;
    for(int i=0;i<2;i++)outf<<a[i]<<" ";
    outf<<endl;
    outf<<endl;
    auto t2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

    outf2<<time_span.count()<<endl;
}
int main()
{
    auto data=fopen("../input/4_1_input.txt","r");
    if(!data){cout<<"open file failed!"<<endl;system("pause");exit(0);}
    vector<char> T;
    vector<char> P;

    int n=2*2*2*2*2*2*2;
    int m=2*2;
    char c;
    for(int j=0;j<5;j++)
    {
        T.push_back('0');//T[0]不用 
        P.push_back('0');
        m=m*2;
        n=n*2;
        for(int i=1;i<=m;i++){fscanf(data,"%c",&c); P.push_back(c);}
        fgetc(data);
        for(int i=1;i<=n;i++){fscanf(data,"%c",&c); T.push_back(c);}
        fgetc(data);
        KMP_MATCHER(T,P);
        T.clear();
        P.clear();
    }
   
    //for(int i=1;i<T.size();i++) cout<<T[i];
    system("pause");
    return(0);
}