#include <queue>
#include <cstdio>
#include <set>
#include <string>
#include <stack>
#include <cmath>
#include <climits>
#include <map>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#define LL long long
#define ULL unsigned long long
using namespace std;
const int MAXN = 100010;
//以下为倍增算法求后缀数组
int wa[MAXN], wb[MAXN], wv[MAXN], Ws[MAXN];

// 由于末尾填了0，所以如果r[a]==r[b]（实际是y[a]==y[b]），
// 说明待合并的两个长为j的字符串，前面那个一定不包含末尾0，
// 因而后面这个的起始位置至多在0的位置，不会再靠后了，因而不会产生数组越界。
int cmp(int *r, int a, int b, int l) {
  return r[a] == r[b] && r[a + l] == r[b + l];
}

/*
    Da倍增算法实现
    输入：字符串数组r,后缀数组SA初始化，长度n
    m代表字符串中字符的取值范围，是基数排序的基数范围，字母可以直接取128
    如果原序列本身都是整数的话，则m可以取比最大的整数大1的值。
    输出：无
*/
/**< 传入参数：str,sa,len+1,ASCII_MAX+1 */
void da(const char *r, int *sa, int n, int m)  // Doubling Algorithm
{
  int i, j, p, *x = wa, *y = wb, *t;

  // 前四个for先对字符串首字符进行一次基数排序，得到排序后的SA
  for (i = 0; i < m; i++) Ws[i] = 0;
  for (i = 0; i < n; i++) Ws[x[i] = r[i]]++;
  for (i = 1; i < m; i++) Ws[i] += Ws[i - 1];
  for (i = n - 1; i >= 0; i--) sa[--Ws[x[i]]] = i;
  // 下面for循环主要实现了倍增算法的内容，j从长度1开始一直递增
  // 每次倍数增加，也是每次带合并的字符串的长度值。p是每次rank时
  // 所不需要的数量，当p和n相同时说明已经排序结束了。m是基数排序
  // 所需要的取值range。
  for (j = 1, p = 1; p < n; j *= 2, m = p) {
    // 下面两个for是对第二个关键字进行排序
    for (p = 0, i = n - j; i < n; i++)
      y[p++] = i;  //当长度为j时，n-j开始的后缀串都没有第二个关键字
                   //那么这些字符串的第二个关键字都是补齐的最小字符，按照第二关键字排序后
    // 这些字符串都将排在最前面。
    for (i = 0; i < n; i++)
      if (sa[i] >= j)
        y[p++] =
            sa[i] -
            j;  // 这里将有第二关键字的后缀进行排序y[]里存放的是按第二关键字排序的字符串下标
    for (i = 0; i < n; i++) wv[i] = x[y[i]];
    // 下面四行便是对后缀的第一关键字进行基数排序
    for (i = 0; i < m; i++) Ws[i] = 0;
    for (i = 0; i < n; i++) Ws[wv[i]]++;
    for (i = 1; i < m; i++) Ws[i] += Ws[i - 1];
    for (i = n - 1; i >= 0; i--) sa[--Ws[wv[i]]] = y[i];
    // 下面就是计算合并之后的rank值了，用x[]存储计算出的各字符串rank的值
    // 要注意的是但计算rank的时候必须让相同的字符串有相同的rank，要不然p==n之后就结束了。
    for (t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; i++)
      x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
  }
  return;
}
int sa[MAXN], Rank[MAXN], height[MAXN];
//求height数组
/**< str,sa,len */
void calheight(const char *r, int *sa, int n) {
  int i, j, k = 0;
  for (i = 1; i <= n; i++) Rank[sa[i]] = i;
  for (i = 0; i < n; height[Rank[i++]] = k)
    for (k ? k-- : 0, j = sa[Rank[i] - 1]; r[i + k] == r[j + k]; k++)
      ;
  // Unified
  for (int i = n; i >= 1; --i) ++sa[i], Rank[i] = Rank[i - 1];
}

char str[MAXN];
int main() {
  while (scanf("%s", str) != EOF) {
    int len = strlen(str);
    da(str, sa, len + 1, 130);
    calheight(str, sa, len);
    puts("--------------All Suffix--------------");
    for (int i = 1; i <= len; ++i) {
      printf("%d:\t", i);
      for (int j = i - 1; j < len; ++j) printf("%c", str[j]);
      puts("");
    }
    puts("");
    puts("-------------After sort---------------");
    for (int i = 1; i <= len; ++i) {
      printf("sa[%2d ] = %2d\t", i, sa[i]);
      for (int j = sa[i] - 1; j < len; ++j) printf("%c", str[j]);
      puts("");
    }
    puts("");
    puts("---------------Height-----------------");
    for (int i = 1; i <= len; ++i) printf("height[%2d ]=%2d \n", i, height[i]);
    puts("");
    puts("----------------Rank------------------");
    for (int i = 1; i <= len; ++i) printf("Rank[%2d ] = %2d\n", i, Rank[i]);
    puts("------------------END-----------------");
  }
  return 0;
}