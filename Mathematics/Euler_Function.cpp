#include <iostream>
using namespace std;
int phi[1000];     

/*
返回[1,n]中和n互素的个数
*/
void getPhi(int n)
{
	int i, j, pNum = 0 ;
	memset(phi, 0, sizeof(phi)) ;
	phi[1] = 1 ;
	for(i = 2; i < n; i++)
	{
		if(!phi[i])
		{
			for(j = i; j < n; j += i)
			{
				if(!phi[j])
					phi[j] = j;
				phi[j] = phi[j] / i * (i - 1);
			}
		}
	}
}

int euler(int n)  
{
	int ret = n;
	int i;
	for(i = 2 ; i * i <= n ; i ++)
	{
		if(n % i == 0)
		{
			ret = ret - ret / i;
			while(n % i == 0)
			{
				n /= i;
			}
		}
	}
	if(n > 1)
	{
		ret = ret - ret / n;
	}
    return ret;
}
/*
容斥：
返回：[1,x]中与p互素的个数。
*/
std::vector<int> divsior[1000010];
// divsior[p][j] represent the j_th divsior of p is divsior[p][j]
void init()
{
	for(int i=2;i<=1e6;i++) {
    if(divsior[i].empty()) {
      for(int j=i;j<=1e6;j+=i) {
        divsior[j].push_back(i);
      }
    }
  }
}
//return : [1，x]中与 p互质的数的个数
ll query(ll x,ll p)
{
  ll ans = 0;
  for(int i = 0;i < (1 << divsior[p].size());i++) {
    int cnt = 0;
    int v = 1;
    for(int j = 0;j < (int)divsior[p].size();j++) {
      if((1<<j) & i) {
        cnt++;
        v *= divsior[p][j];
      }
    }
    if(cnt&1) {
      ans -= (x / v);
    }
    else ans += (x / v);
  }
  // std::cout << "ans=" << ans << '\n';
  return ans;
}
