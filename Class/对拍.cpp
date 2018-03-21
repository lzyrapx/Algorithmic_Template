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
