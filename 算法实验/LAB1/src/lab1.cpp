#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdio.h>
#include <chrono>
using namespace std;
#define maxnum 9223372036854775805
void MATRIX_CHAIN_ORDER(vector<int> b);   
void PRINT_OPTIMAL_PARENS(vector<vector<int> > a,int i,int j);
ofstream outFile("..\\output\\result.txt");
ofstream outFile2("..\\output\\time.txt");
int main() {
    ifstream data("..\\input\\1_1_input.txt"); //待读取文件的目录
    vector<int> a;
    string line;
    while (getline(data, line)) 
    {
        stringstream ss; //输入流
        ss << line; //向流中传值
        if (!ss.eof()) 
        {
            int temp;
            while (ss >> temp) //提取int数据
             a.push_back(temp); //保存到vector
        }
    }
    vector<int> b;int i=0;
    for(;i<a.size();i++)
    {
        int j=i+1;
        for(;j<=i+a[i]+1;j++)
        {
            b.push_back(a[j]);
        }
        MATRIX_CHAIN_ORDER(b);
        b.clear();
        i=j-1;
    }
    return 0;
}
void MATRIX_CHAIN_ORDER(vector<int> b)
{
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    int n=b.size()-1;
    vector<vector<long long> > m(n+1);//建立二维数组保存从Ai到j的最少乘法次数
    for(int i=1;i<=n;i++) 
    m[i].resize(n+1);

    vector<vector<int> > s(n+1);//建立二维数组保存从Ai到j的分割点
    for(int  i=1;i<=n;i++) 
    s[i].resize(n+1);
    
    int i;
    for(i=1;i<=n;i++)
    m[i][i]=0;
    for(int l=2;l<=n;l++)//起点
    {
        for( i=1;i<=n-l+1;i++)//长度
        {
            int j=i+l-1;//终点
            m[i][j]=maxnum;
            for(int k=i;k<j;k++)//分割点
            {
                long long p=(long long)b[i-1]*(long long)b[k]*(long long)b[j];//注意类型转化
                long long q=(long long)m[i][k]+(long long)m[k+1][j]+p;
                if(q<m[i][j])
                {
                    m[i][j]=q;
                    s[i][j]=k;
                }
            }
        }
    }     
    outFile<<m[1][n]<<endl;
    auto t2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - now);
    PRINT_OPTIMAL_PARENS(s,1,n);
    outFile<<endl;
    outFile2<<time_span.count()<<"s"<<endl;
    /*  if(m[1].size()==6)//打印
    {
        for(int x=5;x>=1;x--)
        {
            for(int k=5;k>=x;k--)
            cout<<m[x][k]<<" ";
            cout<<endl;
        }

    }
     if(m[1].size()==6)//打印
    {
        for(int x=4;x>=1;x--)
        {
            for(int k=5;k>=x+1;k--)
            cout<<s[x][k]<<" ";
            cout<<endl;
        }
    }*/
} 
void PRINT_OPTIMAL_PARENS(vector<vector<int> > a,int i,int j)//打印链乘过程
{
    if(i==j)
    outFile<<"A"<<i;
    else 
    {
        outFile<<"(";
        PRINT_OPTIMAL_PARENS( a, i,a[i][j]);
        PRINT_OPTIMAL_PARENS( a,a[i][j]+1,j);
        outFile<<")";
    }
}