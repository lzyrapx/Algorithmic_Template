
/*   
  bernoulli方程
  Sn(m)=1^n+2^n+...+(m-1)^n
  => Sn(m)=1/(m+1)(0~m)ΣC(m+1,k)Bk(m^(n+1-k))
  其中:B0=1 , (0,m)ΣC(m+1,k)Bk=0     
 */

ll B[N][2], C[N][N], f[N][2];
int n, m;  // n为幂大小

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

void getC(int n) {
  int i, j;
  n++;
  for (i = 0; i <= n; i++) C[i][0] = C[i][i] = 1;
  for (i = 2; i <= n; i++) {
    for (j = 1; j < n; j++) {
      C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
  }
}

void bernoulli(int n)  //得到B数组
{
  int i, m;
  ll s[2], b[2], l, g;
  B[0][0] = 1;
  B[0][1] = 1;
  for (m = 1; m <= n; m++) {
    s[0] = 1, s[1] = 1;
    for (i = 1; i < m; i++) {
      b[0] = C[m + 1][i] * B[i][0];
      b[1] = B[i][1];
      l = lcm(s[1], b[1]);
      s[0] = l / s[1] * s[0] + l / b[1] * b[0];
      s[1] = l;
    }
    s[0] = -s[0];
    if (s[0]) {
      g = gcd(s[0], s[1] * C[m + 1][m]);
      B[m][0] = s[0] / g;
      B[m][1] = s[1] * C[m + 1][m] / g;
    } else
      B[m][0] = 0, B[m][1] = 1;
  }
}
