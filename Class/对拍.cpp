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
