// 求两个数相乘超过long long取摸的快速运算O(1)  
inline ll mul_mod(ll a, ll b, ll mod) {
  assert(0 <= a && a < mod);
  assert(0 <= b && b < mod);
  if (mod < int(1e9)) return a * b % mod;
  ll k = (ll)((long double)a * b / mod);
  ll ans = a * b - k * mod;
  ans %= mod;
  if (ans < 0) ans += mod;
  return ans;
}
