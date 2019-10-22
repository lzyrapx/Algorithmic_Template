/*
 * @Author: zhaoyang.liang
 * @Github: https://github.com/LzyRapx
 * @Date: 2019-06-13 00:02:05
 */
// 大步小步法（Baby-Step-Giant-Step，简称BSGS）
// https://www.lydsy.com/JudgeOnline/problem.php?id=2242
// 给定y,z,p，计算满足 y^x ≡ z ( mod p)的最小非负整数x., p 为素数
// 复杂度：O(sqrt(p))

#include <iostream>
#include <cstdio>
#include <map>
#include <cmath>

using namespace std;
typedef long long ll;
ll qpower(ll a, ll b,ll mod)
{
    ll ans = 1;
    while(b > 0) {
        if(b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }
    return ans;
}
map<ll,ll>mp;
void BSGS(ll y, ll z,ll p)
{
  if(z >= p) {
  	std::cout << "cannot find x!" << '\n';
    return;
  }
  y %= p;
  z %= p;
  if(y == 0 && z == 0) {
    std::cout << "1" << '\n';
    return;
  }
  if(y == 0 && z != 0) {
    std::cout << "cannot find x!" << '\n';
    return;
  }
  mp.clear();
  ll tmp = 1;
  ll power = qpower(y, p - 2, p);
  ll k = ceil((sqrt(p)));
  mp[z] = k + 1;
  for(int i = 1; i < k; i++) {
    tmp = tmp * power % p;
    ll t = tmp * z % p;
    if(!mp[t]) mp[t] = i;
  }
  tmp = 1;
  power = qpower(y,k,p);
  for(int i = 0; i < k; i++, tmp = tmp * power % p)
  {
    if(mp[tmp])
    {
      if(mp[tmp] == k + 1) std::cout << i * k << '\n';
      else std::cout << i * k + mp[tmp] << '\n';
      return;
    }
  }
  std::cout << "cannot find x!" << '\n';
}