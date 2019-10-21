/*
 * @Author: zhaoyang.liang
 * @Github: https://github.com/LzyRapx
 * @Date: 2019-10-21 22:16:19
 */
#include <iostream>
#include <cstdio>
#include <vector>
#define MAXN 505
using namespace std;
typedef vector<int> vec;
typedef vector<vec> mat;

/*
给一个 n*n 的行列式 A 和模数 mod ，求 A 的秩模 mod
*/
int n;
int det_mod(mat A, int mod) {
  int n = A.size();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      A[i][j] %= mod;
    }
  }

  int ans = 1;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      while (A[j][i] != 0) {
        int t = A[i][i] / A[j][i];
        for (int k = 0; k < n; k++) {
          A[i][k] = A[i][k] - A[j][k] * t;
          swap(A[i][k], A[j][k]);
        }
        ans = -ans;
      }
      if (A[i][i] == 0) return 0;
    }
    ans = ans * A[i][i];
  }
  return (ans % mod + mod) % mod;
}
int main() {
  int mod;
  cin >> n >> mod;
  mat A(n, vec(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> A[i][j];
    }
  }
  printf("%d\n", det_mod(A, mod));
  return 0;
}