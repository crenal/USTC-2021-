#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdio.h>
#include<set> 
#include<stdlib.h>
#include<string.h>
#include <windows.h>
#include <chrono>
using namespace std;

ofstream outFile2("..\\output\\time.txt");
void LCS_LENGTH(vector<char> x,vector<char> y);
set<string> LCS;string path1="..\\output\\result_";string path2=".txt";string path;
void PRINT_LCS(vector<vector<int> > b,string s,vector<char> x,int maxlength,int i,int j);
int k;
int main() 
{
    
    
    vector<char> a,b;
    FILE *data; 
    int i;
    data=fopen("..\\input\\input.txt","r"); 
    if(!data){cout<<"open failed"<<endl;system("pause");exit(0);}
    for(i=1;i<=5;i++)
    {
        int n;char s;
        fscanf (data,"%d",&n) ;
        for(int j=0;j<n;j++)
        {
             fscanf (data,"%c",&s);
             if(s!='\n')
             a.push_back(s);
             else
             {
                 fscanf (data,"%c",&s);
                 a.push_back(s);
             }
        }
        for(int j=0;j<n;j++)
        {
             fscanf (data,"%c",&s) ;
             if(s!='\n')
             b.push_back(s);
             else
             {
                 fscanf (data,"%c",&s);
                 b.push_back(s);
             }
        }
        char nn[2];
        itoa(n,nn,10);
        int l=strlen(nn);
        for(int h=0;h<l;h++)
        path1.push_back(*(nn+h));
        path=path1+path2;
        LCS_LENGTH(a,b);
        for(int h=0;h<l;h++)
        path1.pop_back();//处理输出文件的名字
        a.clear();
        b.clear();
    }
    return(0);
}
void LCS_LENGTH(vector<char> x,vector<char> y)
{
    ofstream outFile(path.c_str()); 
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    int m=x.size();
    int n=y.size();
    vector<vector<int> > b(m+1);
    for(int i=0;i<m+1;i++)
    b[i].resize(n+1);

    vector<vector<int> > c(m+1);
    for(int i=0;i<m+1;i++)
    c[i].resize(n+1);

    for(int i=1;i<=m;i++)
    c[i][0]=0;
    for(int i=0;i<=n;i++)
    c[0][i]=0;

    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(x[i-1]==y[j-1])//↖
            {
                c[i][j]=c[i-1][j-1]+1;
                b[i][j]=2;
            }
            else if(c[i-1][j]>c[i][j-1])//←
            {
                c[i][j]=c[i-1][j];
                b[i][j]=1;
            }
            else if(c[i-1][j]<c[i][j-1])//↑
            {
                c[i][j]=c[i][j-1];
                b[i][j]=3;
            }
            else//←或者↑
            {
                c[i][j]=c[i][j-1];
                b[i][j]=4;
            }
        }
    }
    string ss;//暂存字符串
    LCS.clear();//LCS集合初始化
    int maxlength=c[m][n];//最长
    PRINT_LCS(b,ss,x,maxlength,x.size(),y.size());
    k=LCS.size();
    outFile<<"最长公共子序列有"<<k<<"个"<<endl;
    outFile<<endl;
    set<string>::iterator it;
    for(it=LCS.begin ();it!=LCS.end ();it++)
    {
        outFile<<*it<<endl;
    }
    auto t2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - now);
    outFile2<<time_span.count()<<"s"<<endl;
}
string Reverse(string str)
{
	int low = 0;
	int high = str.length() - 1;
	while (low < high)
	{
		char temp = str[low];
		str[low] = str[high];
		str[high] = temp;
		++low;
		--high;
	}
	return str;
}
void PRINT_LCS(vector<vector<int> > b,string s,vector<char> x,int maxlength,int i,int j)
{
    if(i==0||j==0)
    {
        string sb= Reverse(s);
        LCS.insert(sb);
        return;
    }
    if(b[i][j]==1)
    {
        PRINT_LCS(b,s,x,maxlength,i-1,j);
    }
    else if (b[i][j]==2)
    {
        s.push_back(x[i-1]);
        PRINT_LCS(b,s,x,maxlength,i-1,j-1);
    }
    else if(b[i][j]==3)
    {
        PRINT_LCS(b,s,x,maxlength,i,j-1);
    }
    else
    {
        PRINT_LCS(b,s,x,maxlength,i-1,j);
        PRINT_LCS(b,s,x,maxlength,i,j-1);
    }
}