#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
void func(char *s){s = (char*)malloc(10);}
int main()
{ 
char *p = NULL;
func(p); 
if(!p)printf("error\n");else printf("ok\n");
system("pause");
return 0;
}