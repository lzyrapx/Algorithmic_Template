typedef complex<double> Complex;

const double PI = acos(-1.0);

void radar(Complex *y, int len) {
  for (int i = 1, j = len / 2; i < len - 1; i++) {
    if (i < j) swap(y[i], y[j]);
    int k = len / 2;
    while (j >= k) {
      j -= k;
      k /= 2;
    }
    if (j < k) j += k;
  }
}

void fft(Complex *y, int len, int op) {
  radar(y, len);
  for (int h = 2; h <= len; h <<= 1) {
    double ang = op * 2 * PI / h;
    Complex wn(cos(ang), sin(ang));
    for (int j = 0; j < len; j += h) {
      Complex w(1, 0);
      for (int k = j; k < j + h / 2; k++) {
        Complex u = y[k];
        Complex t = w * y[k + h / 2];
        y[k] = u + t;
        y[k + h / 2] = u - t;
        w = w * wn;
      }
    }
  }
  if (op == -1)
    for (int i = 0; i < len; i++) y[i] /= len;
}

const int N = 200005, M = 313;

Complex A[N << 1], B[N << 1];

int f[N], a[N];

void cdq(int l, int r) {
  if (l == r) return;
  int mid = (l + r) >> 1;
  cdq(l, mid);
  int len = 1;
  while (len <= r - l + 1) len <<= 1;
  for (int i = 0; i < len; i++) {
    A[i] = Complex(l + i <= mid ? f[l + i] : 0, 0);
    B[i] = Complex(l + i + 1 <= r ? a[i + 1] : 0, 0);
  }
  fft(A, len, 1);
  fft(B, len, 1);
  for (int i = 0; i < len; i++) A[i] *= B[i];
  fft(A, len, -1);
  for (int i = mid + 1; i <= r; i++) {
    f[i] += fmod(A[i - l - 1].real(), M) + 0.5;
    if (f[i] >= M) f[i] -= M;
  }
  cdq(mid + 1, r);
}

int main() {
  int n;
  double clock_t = clock();
  ios_base::sync_with_stdio(0);
  while (~scanf("%d", &n) && n) {
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      a[i] %= M;
    }
    memset(f, 0, sizeof(f));
    f[0] = 1;
    cdq(0, n);
    printf("%d\n", f[n]);
  }
#ifdef LOCAL
    printf("\nTime cost %.3fs\n",1.0 * (clock() - colck_t);
#endif
    return 0;
}