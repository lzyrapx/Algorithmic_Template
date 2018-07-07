#include <bits/stdc++.h>
using namespace std;
const int maxn = 1234;

// https://www.luogu.org/problemnew/show/P3389

const double eps = 1e-7;
int n;
double a[maxn][maxn];
bool Gauss() {
  int r;
  double f;
  for (int i = 0; i < n; i++) {
    r = i;
    for (int j = i + 1; j < n; j++) {
      if (fabs(a[j][i]) > fabs(a[r][i])) r = j;
    }
    if (fabs(a[r][i]) < eps) return false;
    if (r != i) {
      for (int j = 0; j <= n; j++) swap(a[r][j], a[i][j]);
    }
    for (int k = i + 1; k < n; k++) {
      f = a[k][i] / a[i][i];
      for (int j = i; j <= n; j++) {
        a[k][j] -= f * a[i][j];
      }
    }
  }
  for (int i = n - 1; i >= 0; --i) {
    for (int j = i + 1; j < n; ++j) a[i][n] -= a[j][n] * a[i][j];
    a[i][n] /= a[i][i];
  }
  return true;
}
int main(int argc, char const *argv[]) {
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j <= n; j++) {
      int x;
      std::cin >> x;
      a[i][j] = x;
    }
  }
  if (Gauss() == 0)
    std::cout << "No Solution" << '\n';
  else {
    for (int i = 0; i < n; i++) {
      printf("%.2lf\n", a[i][n]);
    }
  }
  return 0;
}
