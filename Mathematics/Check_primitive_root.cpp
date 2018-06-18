
/*
g^d ≡ 1 (mod p) ，gcd(g,m) = 1
如果g是P的原根，那么g的（1…P-1）次幂 mod P的结果一定互不相同。

检查 g 是否是模 p 意义下的原根.

*/

ll qpower(ll x,ll n,ll m)
{
    long long res = 1;
    while(n > 0){
        if(n & 1) res = (res * x) % m;
        x = (x * x) % m;
        n >>= 1;
    }
    return res;
}
// bool check_primitive_root(ll g, ll p)
// {
//   ll n = p - 1;
//   std::vector<ll> divsior;
//   for(ll i = 2; i * i <= n; i++) {
//       if (n % i == 0) {
//         divsior.push_back(i);
//         while (n % i == 0) n /= i;
//       }
//   }
//   if(n > 1) divsior.push_back(n);
//
//   for(auto &a : divsior)
//   {
//     if(qpower(g, (p - 1) / a, p) == 1)  return false;
//   }
//   return true;
// }
bool check_primitive_root(ll g, ll p)
{
  if (qpower(g,(p-1)/5,p)==1) return false;
  return true;
}