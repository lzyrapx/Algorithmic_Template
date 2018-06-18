#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6 + 10;
const int maxLen = 18, maxm = 1 << maxLen | 1;
const ll maxv = 1e10 + 6; // 1e14, 1e15
const long double pi = acos(-1.0); // double maybe is not enough
ll mod, nlim, sp, msk;

// 这个板子精度好像不行 ==!

ll qpower(ll x, ll p) { // x ^ p % mod
	ll ret = 1;
	while (p) {
		if (p & 1) (ret *= x) %=mod;
		(x *= x) %=mod;
		p >>= 1;
	}
	return ret;
}
struct cp {
  long double r, i;
  cp() {}
  cp(long double r, long double i) : r(r), i(i) {}
  cp operator + (cp const &t) const { return cp(r + t.r, i + t.i); }
  cp operator - (cp const &t) const { return cp(r - t.r, i - t.i); }
  cp operator * (cp const &t) const { return cp(r * t.r - i * t.i, r * t.i + i * t.r); }
  cp conj() const { return cp(r, -i); }
} w[maxm], wInv[maxm];
void init() {
  for(int i = 0, ilim = 1 << maxLen; i < ilim; ++i) {
      int j = i, k = ilim >> 1; // 2 pi / ilim
      for( ; !(j & 1) && !(k & 1); j >>= 1, k >>= 1);
      w[i] = cp((long double)cos(pi / k * j), (long double)sin(pi / k * j));
      wInv[i] = w[i].conj();
  }
  nlim = std::min(maxv / (mod - 1) / (mod - 1), maxn - 1LL);
  for(sp = 1; 1 << (sp << 1) < mod; ++sp);
  msk = (1 << sp) - 1;
}

void FFT(int n, cp a[], int flag) {
  static int bitLen = 0, bitRev[maxm] = {};
  if(n != (1 << bitLen)) {
      for(bitLen = 0; 1 << bitLen < n; ++bitLen);
      for(int i = 1; i < n; ++i)
          bitRev[i] = (bitRev[i >> 1] >> 1) | ((i & 1) << (bitLen - 1));
  }
  for(int i = 0; i < n; i ++) {
    if(i < bitRev[i]) {
      std::swap(a[i], a[bitRev[i]]);
    }
  }
  for(int i = 1, d = 1; d < n; ++i, d <<= 1)
      for(int j = 0; j < n; j += d << 1)
          for(int k = 0; k < d; ++k) {
              cp &AL = a[j + k], &AH = a[j + k + d];
              cp TP = w[k << (maxLen - i)] * AH;
              AH = AL - TP, AL = AL + TP;
          }
  if(flag != -1)
      return;
  std::reverse(a + 1, a + n);
  for(int i = 0; i < n; ++i) {
      a[i].r /= n;
      a[i].i /= n;
  }
}

void polyMul(int a[], int aLen, int b[], int bLen, int c[]) // a 和 b 的卷积 c
{ // c not in {a, b}
  // std::cout << "mod = " << mod << '\n';
  static cp A[maxm], B[maxm], C[maxm], D[maxm];
  int len, cLen = aLen + bLen - 1; // optional: parameter
  for(len = 1; len < aLen + bLen - 1; len <<= 1);
  if(std::min(aLen, bLen) <= nlim)
  {
      for(int i = 0; i < len; i++) {
          A[i] = cp(i < aLen ? a[i] : 0, i < bLen ? b[i] : 0);
      }
      FFT(len, A, 1);
      cp tr(0, -0.25);
      for(int i = 0, j; i < len; i++) {
        j = (len - i) & (len - 1), B[i] = (A[i] * A[i] - (A[j] * A[j]).conj()) * tr;
      }
      FFT(len, B, -1);
      for(int i = 0; i < cLen; ++i) c[i] = (ll)(B[i].r + 0.5) % mod;
      return;
  } // if min(aLen, bLen) * mod <= maxv
  for(int i = 0; i < len; ++i) {
      A[i] = i < aLen ? cp(a[i] & msk, a[i] >> sp) : cp(0.0, 0.0);
      B[i] = i < bLen ? cp(b[i] & msk, b[i] >> sp) : cp(0.0, 0.0);
  }
  FFT(len, A, 1);
  FFT(len, B, 1);
  cp trL(0.5, 0.0), trH(0.0, -0.5), tr(0.0, 1.0);
  for(int i = 0, j; i < len; i++) {
      j = (len - i) & (len - 1);
      cp AL = (A[i] + A[j].conj()) * trL;
      cp AH = (A[i] - A[j].conj()) * trH;
      cp BL = (B[i] + B[j].conj()) * trL;
      cp BH = (B[i] - B[j].conj()) * trH;
      C[i] = AL * (BL + BH * tr);
      D[i] = AH * (BL + BH * tr);
  }
  FFT(len, C, -1);
  FFT(len, D, -1);
  for(int i = 0; i < cLen; ++i)
  {
      int v11 = (ll)(C[i].r + 0.5) % mod, v12 = (ll)(C[i].i + 0.5) % mod;
      int v21 = (ll)(D[i].r + 0.5) % mod, v22 = (ll)(D[i].i + 0.5) % mod;
      c[i] = (((((ll)v22 << sp) + v12 + v21) << sp) + v11) % mod;
  }
}

int c[maxm], tmp[maxm];
// y should clear to 0
void polyInv(int x[], int y[], int deg) { // 多项式 x 求逆后的结果是 y
  if (deg == 1) {
    y[0] = qpower(x[0], mod - 2);
    return;
  }
  polyInv(x, y, (deg + 1) >> 1);

  copy(x, x + deg, tmp);
  int p = ((deg + 1) >> 1) + deg - 1;
  polyMul(y, (deg + 1) >> 1, tmp, deg, c);

  for (int i = 0; i < p; i += 1) c[i] = (- c[i] + mod) %mod;
  (c[0] += 2) %=mod;

  polyMul(y, (deg + 1) >> 1, c, deg, tmp);
  copy(tmp, tmp + deg, y);
}

int a[maxn],b[maxn];
int ans[maxn];
ll n,m;
int main()
{
  std::cin >> n >> m >> mod;
  for(int i = 0; i <= n; i++) {
    std::cin >> a[i];
  }
  for(int i = 0; i <= m; i++) {
    std::cin >> b[i];
  }
  init();
  polyMul(a,n+1,b,m+1,ans);

  for(int i = 0; i <=  n + m; i++) {
    std::cout << ans[i] << " ";
  }
  std::cout << '\n';
  return 0;
}
