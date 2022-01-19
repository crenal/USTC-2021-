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

ofstream outf("../output/result.txt");
ofstream outf2("../output/time.txt");
double RABIN_KARP_MATCHER(vector<char> T,vector<char> P,int d,int q)
{
    auto t1 = std::chrono::steady_clock::now();
    int y[2];
    auto n=T.size()-1;
    auto m=P.size()-1;
    int h = 1;
    for(int i=0; i<m-1;i++)
    {
        h=(h*d)%q;
    }
    int p=0;
    int t=0;
    for(int i=1;i<=m;i++)
    {
        p=(d*p+(int)P[i])%q; if(p<0)p+=q;
        t=(d*t+(int)T[i])%q; if(t<0)t+=q;
    } 
    int k=0;int num=0;
    for(int s=0;s<=n-m;s++)
    {
        if(p==t)
        {
            int j;
            for( j=1;j<=m;j++)
            {
                if(P[j]!=T[s+j]) {k++;break;}
            }
            if(j>m) y[num++]=s+1;
        }
        if(s<n-m)
        {
            t=(d*(t-T[s+1]*h)+T[s+m+1])%q;
            if(t<0) t=t+q;
        }
    }
    auto t2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    if(d==2&&q==13)outf<<num<<endl;
    outf<<k<<" ";
    if(d==10&&q==1009)outf<<endl<<y[0]<<" "<<y[1]<<endl<<endl;
    return(time_span.count());
}
int main()
{   
    auto data=fopen("../input/4_2_input.txt","r");
    if(!data){cout<<"open file failed!"<<endl;system("pause");exit(0);}
    vector<char> T;
    vector<char> P;
    int n=2*2*2*2*2*2*2;
    int m=2*2;
    char c;
    double t[4][5];
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
        //cout<<T[n]<<endl;
        t[0][j]=RABIN_KARP_MATCHER(T,P,2,13);
        t[1][j]=RABIN_KARP_MATCHER(T,P,2,1009);
        t[2][j]=RABIN_KARP_MATCHER(T,P,10,13);
        t[3][j]=RABIN_KARP_MATCHER(T,P,10,1009);
        T.clear();
        P.clear();
    }
    outf2<<"(2,13)"<<endl;
    for(int j=0;j<5;j++) outf2<<t[0][j]<<"s"<<" ";
    outf2<<endl;
    outf2<<"(2,1009)"<<endl;
    for(int j=0;j<5;j++) outf2<<t[1][j]<<"s"<<" ";
    outf2<<endl;
    outf2<<"(10,13)"<<endl;
    for(int j=0;j<5;j++) outf2<<t[2][j]<<"s"<<" ";
    outf2<<endl;
    outf2<<"(10,1009)"<<endl;
    for(int j=0;j<5;j++) outf2<<t[3][j]<<"s"<<" ";
    outf2<<endl;
    system("pause");
    return(0);
}