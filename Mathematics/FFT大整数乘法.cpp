// FFT 大整数乘法
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 500005;
const double pi = acos(-1.0);

char s1[N], s2[N];
int len, res[N];

struct Complex {
  double r, i;
  Complex(double r = 0, double i = 0) : r(r), i(i){};
  Complex operator+(const Complex &rhs) {
    return Complex(r + rhs.r, i + rhs.i);
  }
  Complex operator-(const Complex &rhs) {
    return Complex(r - rhs.r, i - rhs.i);
  }
  Complex operator*(const Complex &rhs) {
    return Complex(r * rhs.r - i * rhs.i, i * rhs.r + r * rhs.i);
  }
} va[N], vb[N];

//雷德算法--倒位序
void rader(Complex F[],
           int len)  // len = 2^M,reverse F[i] with  F[j] j为i二进制反转
{
  int j = len >> 1;
  for (int i = 1; i < len - 1; ++i) {
    if (i < j) swap(F[i], F[j]);  // reverse
    int k = len >> 1;
    while (j >= k) {
      j -= k;
      k >>= 1;
    }
    if (j < k) j += k;
  }
}
// FFT实现
void FFT(Complex F[], int len, int t) {
  rader(F, len);
  for (int h = 2; h <= len; h <<= 1)  //分治后计算长度为h的DFT
  {
    Complex wn(cos(-t * 2 * pi / h),
               sin(-t * 2 * pi / h));  //单位复根e^(2*PI/m)用欧拉公式展开
    for (int j = 0; j < len; j += h) {
      Complex E(1, 0);  //旋转因子
      for (int k = j; k < j + h / 2; ++k) {
        Complex u = F[k];
        Complex v = E * F[k + h / 2];
        F[k] = u + v;  //蝴蝶合并操作
        F[k + h / 2] = u - v;
        E = E * wn;  //更新旋转因子
      }
    }
  }
  if (t == -1)  // IDFT
    for (int i = 0; i < len; ++i) F[i].r /= len;
}
//求卷积
void Conv(Complex a[], Complex b[], int len)  //求卷积
{
  FFT(a, len, 1);
  FFT(b, len, 1);
  for (int i = 0; i < len; ++i) a[i] = a[i] * b[i];
  FFT(a, len, -1);
}

void init(char *s1, char *s2) {
  int n1 = strlen(s1), n2 = strlen(s2);
  len = 1;
  while (len < 2 * n1 || len < 2 * n2) len <<= 1;
  int i;
  for (i = 0; i < n1; ++i) {
    va[i].r = s1[n1 - i - 1] - '0';
    va[i].i = 0;
  }
  while (i < len) {
    va[i].r = va[i].i = 0;
    ++i;
  }
  for (i = 0; i < n2; ++i) {
    vb[i].r = s2[n2 - i - 1] - '0';
    vb[i].i = 0;
  }
  while (i < len) {
    vb[i].r = vb[i].i = 0;
    ++i;
  }
}

void gao() {
  Conv(va, vb, len);
  memset(res, 0, sizeof res);
  for (int i = 0; i < len; ++i) {
    res[i] = va[i].r + 0.5;
  }
  for (int i = 0; i < len; ++i) {
    res[i + 1] += res[i] / 10;
    res[i] %= 10;
  }
  int high = 0;
  for (int i = len - 1; i >= 0; --i) {
    if (res[i]) {
      high = i;
      break;
    }
  }
  for (int i = high; i >= 0; --i) putchar('0' + res[i]);
  puts("");
}

int main() {
  while (scanf("%s %s", s1, s2) == 2) {
    init(s1, s2);
    gao();
  }
  return 0;
}
