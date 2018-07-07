
/*
  factorial相关
  -求n!某个因子k的个数  n!=(k^m)*(m!)*a
  推导：
    n!=n*(n-1)*(n-2)*......3*2*1
      =(k*2k*3k.....*mk)*a      a是不含因子k的数的乘积，显然m=n/k;
      =(k^m)*(1*2*3...*m)*a
      =k^m*m!*a
*/

ll ncount(ll n, ll k) {
  ll cou = 0;
  while (n) cou += n /= k;
  return cou;
}