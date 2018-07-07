
/*
  [1,n]与a互素个数   O(sqrt n)
  先对a分解质因数
  然后用容斥原理
*/

int fac[50];
int solve(int n, int a) {
  int i, j, up, t, cnt = 0, sum = 0, flag;
  for (i = 2; i * i <= a; i++)
    if (a % i == 0) {
      fac[cnt++] = i;
      while (a % i == 0) a /= i;
    }
  if (a > 1) fac[cnt++] = a;
  up = 1 << cnt;
  for (i = 1; i < up; i++) {  //容斥原理，二进制枚举
    flag = 0, t = 1;
    for (j = 0; j < cnt; j++) {
      if (i & (1 << j)) {
        flag ^= 1;
        t *= fac[j];
      }
    }
    sum += flag ? n / t : -(n / t);
  }
  return n - sum;
}
