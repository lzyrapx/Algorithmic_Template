/*
 * @Author: zhaoyang.liang
 * @Github: https://github.com/LzyRapx
 * @Date: 2019-10-22 23:57:17
 */

// https://loj.ac/problem/138

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

typedef long long ll;
#define maxn 100010
#define mod 1000000007

ll qpower(ll a, ll b)
{
    ll ans = 1;
    while(b > 0) {
        if(b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }
    return ans;
}
inline int mul(int a, int b) { return 1ll * a * b % mod; }
// head
int C[21][21];
int tr[21][21];
vector<int> mn(vector<int> p) {
  //差分，返回p(x) - p(x - 1)
  int n = p.size();
  if (n == 1) return vector<int>{1, 0};
  vector<int> fn(n - 1);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < i; j++) {
      int nr = mul(p[i], C[i][j]);
      if ((i - j) % 2 == 0) nr *= -1;
      fn[j] = (fn[j] + nr) % mod;
    }
  return fn;
}
int cal(vector<int> p, int c) {
  //计算c带入p的值
  int mt = 1, ans = 0;
  for (int j = 0; j < p.size(); j++) {
    ans = (ans + mul(p[j], mt)) % mod;
    mt = mul(mt, c);
  }
  return ans;
}
void init() {
  //计算组合数及前缀和系数
  for (int i = 0; i < 20; i++)
    for (int j = 0; j <= i; j++) {
      if (i == j || j == 0)
        C[i][j] = 1;
      else
        C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
    }

  for (int i = 0; i < 20; i++) {
    int bk = qpower(i + 1, mod - 2);
    tr[i][i + 1] = bk;
    vector<int> u(i + 2);
    u[i + 1] = bk;
    u = mn(u);
    for (int j = i - 1; j >= 0; j--)
      for (int q = 0; q <= j + 1; q++)
        tr[i][q] = (tr[i][q] - mul(u[j], tr[j][q])) % mod;
  }
}
const int mxs = 10;
struct res {
  int a[mxs + 1][mxs + 1];
  res() { memset(a, 0, sizeof(a)); }
  int cal(vector<int>& p, vector<int>& q) {
    int ans = 0;
    for (int j = 0; j < p.size(); j++)
      for (int k = 0; k < q.size(); k++)
        ans = (ans + mul(mul(p[j], q[k]), a[j][k])) % mod;
    return ans;
  }
};
res cal(int n, int a, int b, int c) {
  // 1 到 n
  if (n == 0) return res();
  int ux = a / c, uy = b / c;
  a %= c, b %= c;
  if (b < 0) uy--, b += c;
  res q1, q2, q3;
  if (a) q1 = cal((1ll * n * a + b) / c, c, -(b + 1), a);
  for (int j = 0; j <= mxs; j++) {
    for (int k = 0; k + j <= mxs; k++) {
      vector<int> p(j + 2);
      for (int r = 0; r <= j + 1; r++) p[r] = tr[j][r];
      vector<int> q(k);
      for (int l = 0; l < k; l++) {
        q[l] = C[k][l];
        if ((k - l) % 2 == 0) q[l] *= -1;
      }
      if (k == 0)
        q2.a[j][k] = cal(p, n);
      else {
        p[0] = (p[0] - cal(p, n)) % mod;
        for (int j = 0; j < p.size(); j++) p[j] = -p[j];
        q2.a[j][k] = q1.cal(q, p);
      }
    }
  }
  for (int j = 0; j <= mxs; j++)
    for (int k = 0; k + j <= mxs; k++) {
      int l0 = 1;
      for (int l = 0; l <= k; l++) {
        int l1 = 1;
        for (int m = 0; m <= k - l; m++) {
          int nans = mul(l0, l1);
          nans = mul(nans, C[k][l] * C[k - l][m]);
          nans = mul(nans, q2.a[j + l][k - l - m]);
          q3.a[j][k] = (q3.a[j][k] + nans) % mod;
          l1 = mul(l1, uy);
        }
        l0 = mul(l0, ux);
      }
    }
  return q3;
}

int brt(int n, int a, int b, int c, int k1, int k2) {
  ll ans = 0;
  for (int j = 1; j <= n; j++) {
    ll x = j, y = (1ll * a * j + b) / c;
    y %= mod;
    ans += qpower(x, k1) * qpower(y, k2);
    ans %= mod;
  }
  return ans;
}
int main() {
  init();
  int t;
  cin >> t;
  for (int i = 0; i < t; i++) {
    int n, a, b, c, k1, k2;
    cin >> n >> a >> b >> c >> k1 >> k2;
    //	int tr = brt(n, a, b, c, k1, k2);
    res ans = cal(n, a, b, c);
    int fn = ans.a[k1][k2];
    if (k1 == 0) fn += qpower(b / c, k2), fn %= mod;
    if (fn < 0) fn += mod;
    cout << fn << endl;
  }
  return 0;
}