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


void RABIN_KARP_MATCHER(vector<char> T,vector<char> P,int d,int q)
{
    auto n=T.size()-1;
    auto m=P.size()-1;
    int h=pow(double(d),double(m-1));
    h=h%q;
    int p=0;
    int t=0;
    for(int i=1;i<=m;i++)
    {
        p=(d*p+(int)P[i])%q;
        t=(d*t+(int)T[i])%q;
    } 
    int j;int k=0;
    for(int s=0;s<=n-m;s++)
    {
        if(p==t)
        {
            k++;
            for( j=1;j<=m;j++)
            {
                if(P[j]!=T[s+j]) break;
            }
            if(j>m) cout<<"Pattern occurs with shift"<<s+1<<endl;
        }
        if(s<n-m)
        {
            t=(d*(t-(int)T[s+1]*h)+(int)T[s+m+1])%q;
            if(t<0) t=t+q;
        }
    }
    cout<<"伪命中次数"<<k<<endl;
}
int main()
{   
    auto data=fopen("./input/4_2_input.txt","r");
    ofstream outf("./output/result.txt");
    ofstream outf2("./output/time.txt");
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
        RABIN_KARP_MATCHER(T,P,2,13);
        //RABIN_KARP_MATCHER(T,P,2,1009);
        //RABIN_KARP_MATCHER(T,P,10,13);
        //RABIN_KARP_MATCHER(T,P,10,1009);
        T.clear();
        P.clear();
    }
    system("pause");
    return(0);
}