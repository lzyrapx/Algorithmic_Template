#include<iostream>
#include<windows.h>
using namespace std;
int main()
{
    int t=1;
    while(1)
    {
    	t--;
     //   system("data.exe > data.txt");  
    //    system("biaoda.exe < data.txt > biaoda.txt");  
     //   system("test.exe < data.txt > test.txt");  
        if(system("fc test.txt biaoda.txt"))  break;  //对拍test.txt 和 biaoda.txt
    }
  
    return 0;
}

//------------------------------------------------------------------//
#include<bits/stdc++.h>
using namespace std;
#define maxn 1000010
char ans[maxn][55];
char ac[maxn][55];
char s[55];
int main() {
    int a=0,b=0;
    freopen("ac.txt","r",stdin);
    while(gets(s)) strcpy(ac[a++],s);
    freopen("ans.txt","r",stdin);
    while(gets(s)) strcpy(ans[b++],s);
    if(a!=b) printf("Error!\n");
    else {
        int wa=0;
        for(int i=0; i<a; i++) {
            if(strcmp(ans[i],ac[i])!=0) {
                printf("%d : %s / %s\n",i+1,ac[i],ans[i]);
                wa++;
            }
        }
        printf("wrong answer : %d\n",wa);
    }
    return 0;
}

//------------------------------------------------------------------//
#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
int main()
{
    system("g++ data.cpp -o data -O2");
    system("g++ std.cpp -o std -O2");
    system("g++ my.cpp -o test");
    clock_t st,ed;
    for (int i=1;i<=10;i++)
    {
        printf("%d\n",i);
        //Sleep(1000);
        system("data");
        system("std");
        st=clock();
        system("test");
        ed=clock();
        printf("Time used:%lfs\n",(double)(ed-st)/CLOCKS_PER_SEC);
        int k=system("fc std.out test.out");
        if (k) break;
        printf("AC\n");
    }
    return 0;
}
