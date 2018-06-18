/*
 贾志鹏线性筛：

 功能：预处理素数prime,欧拉函数phi，莫比乌斯函数mu。

 复杂度：O(n)

*/

//#include <bits/stdc++.h>
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
typedef long long ll;
const int maxn = 3000000;
const int mod = 1e9+7;

ll isprime[maxn];
ll prime[maxn];

ll phi[maxn];
ll mu[maxn];

void linear_init(int N)
{
  int tot = 0;
  memset(isprime,0,sizeof(isprime));
  memset(phi,-1,sizeof(phi));
  memset(mu,-1,sizeof(mu));
  phi[0] = mu[0] = 0;
  phi[1] = 1;
  mu[1] = 1;
  for(int i = 2; i < N; i++) {
    if(phi[i] < 0) {
      prime[tot++] = i;
      phi[i] = i - 1;
      mu[i] = -1;
    }
    for(int j = 0; j < tot && 1LL * i * prime[j] <= N; j++) {
      if(i % prime[j]) {
        phi[i * prime[j]] = phi[i] * (prime[j] - 1);
        mu[i * prime[j]] = - mu[i];
      }
      else {
        phi[i * prime[j]] = phi[i] * prime[j];
        mu[i * prime[j]] = 0;
        break;
      }
    }
  }
  //do something
}
int main(int argc, char const *argv[]) {
 linear_init(1000000);
 for(int i=0;i<=5;i++) {
   std::cout << prime[i]  <<" " << phi[i] <<" " << mu[i]<< '\n';
 }

  return 0;
}
