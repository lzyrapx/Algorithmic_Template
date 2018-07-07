#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
typedef long long ll;
int x, y, q;
void ex_Eulid(int a, int b) {
  if (b == 0) {
    x = 1;
    y = 0;
    q = a;
  } else {
    ex_Eulid(b, a % b);
    double temp = x;
    x = y;
    y = temp - a / b * y;
  }
}
//一定存在整数x,y，使得ax+by=gcd(a,b)
ll exgcd(ll a, ll b, ll &x, ll &y)  // 返回a,b的最大公约数
{
  if (!a && !b) return -1;
  if (!b) return x = 1, y = 0, a;
  ll d = exgcd(b, a % b, y, x);
  return y -= a / b * x, d;
}
int main() {
  int a, b;
  cin >> a >> b;
  if (a < b) swap(a, b);
  ex_Eulid(a, b);
  printf("(%d)*%d+(%d)*%d = %d\n", x, a, y, b, q);
  return 0;
}
