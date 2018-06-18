// #include <bits/stdc++.h>
// bzoj3944

#include <cstdio>
#include <cstring>
#include <map>
using namespace std;
typedef long long ll;
const int maxn = 5000000;
const int mod = 1e9+7;

ll prime[maxn / 5];

ll phi[maxn];
ll mu[maxn];

// //计算[1, n]的phi值及mu值
void linear_init(int N)
{
  int tot = 0;
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
  // do something
  // for(int i = 2 ; i <= N; i++) {
  //   phi[i] += phi[i-1];
  //   mu[i] += mu[i-1];
  // }
}
std::map<int, ll> Mu,Phi;

ll calc_phi(ll n) //phi的前缀和
{
  if(n < maxn) return phi[n];
  // std::map<int, ll> ::iterator it;
  // if ((it = Phi.find(n)) != Phi.end()) return it->second;
  if(Phi.count(n))return Phi[n];
  ll ans = 0;
  ans = n * ( n + 1 ) >> 1;
  for(ll i = 2, last; i <= n; i = last + 1) {
    last = n / (n / i);
    ans -= (last - i + 1) * calc_phi(n / i);
  }
  return Phi[n] = ans;
}
ll calc_mu(ll n) // mu 的前缀和
{
  if(n < maxn) return mu[n];
  // std::map<int, ll> ::iterator it;
  // if ((it = Mu.find(n)) != Mu.end()) return it->second;
  if(Mu.count(n))return Mu[n];
  ll ans = 1;
  for(ll i = 2, last; i <= n; i = last + 1) {
    last = n / (n / i);
    ans -= (last - i + 1) * calc_mu(n / i);
  }
  return Mu[n] = ans;
}
int main(int argc, char const *argv[]) {
  linear_init(5000000-1);
  int t;
  //std::cin >> t;
  scanf("%d", &t);
  int n;
  while (t--) {
    //std::cin >> n;
    scanf("%d", &n);
    //std::cout << calc_phi(n) << " " << calc_mu(n) << '\n';
    printf("%lld %lld\n", calc_phi(n), calc_mu(n));
  }

  return 0;
}
