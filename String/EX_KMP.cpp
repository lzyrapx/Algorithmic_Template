// 扩展KMP的应用：

// 给出模板串S和串T，长度分别为Slen和Tlen，要求在线性时间内，对于每个S[i]（0<=i<Slen)，求出S[i..Slen-1]与T的
// 最长公共前缀长度，记为extend[i]（或者说，extend[i]为满足S[i..i+z-1]==T[0..z-1]的最大的z值）。

// 扩展KMP可以用来解决很多字符串问题，如求一个字符串的最长回文子串和最长重复子串。

// 在KMP和扩展KMP中，不管是A串还是B串，其匹配位置都是单调递增的，故总时间复杂度是线性的，都为O(lenA
// + lenB)（只是扩展KMP比KMP的常数更大一些）。

// C/C++ 模板
#include <iostream>
using namespace std;
const int N = 101010;
int next[N], extand[N];
void getnext(char *T) {  // next[i]: 以第i位置开始的子串 与 T的公共前缀
  int i, length = strlen(T);
  next[0] = length;
  for (i = 0; i < length - 1 && T[i] == T[i + 1]; i++)
    ;
  next[1] = i;
  int a = 1;
  for (int k = 2; k < length; k++) {
    int p = a + next[a] - 1, L = next[k - a];
    if ((k - 1) + L >= p) {
      int j = (p - k + 1) > 0 ? (p - k + 1) : 0;
      while (k + j < length && T[k + j] == T[j])
        j++;  // 枚举(p+1，length) 与(p-k+1,length) 区间比较
      next[k] = j, a = k;
    } else
      next[k] = L;
  }
}
void getextand(char *S, char *T) {
  memset(next, 0, sizeof(next));
  getnext(T);
  int Slen = strlen(S), Tlen = strlen(T), a = 0;
  int MinLen = Slen > Tlen ? Tlen : Slen;
  while (a < MinLen && S[a] == T[a]) a++;
  extand[0] = a, a = 0;
  for (int k = 1; k < Slen; k++) {
    int p = a + extand[a] - 1, L = next[k - a];
    if ((k - 1) + L >= p) {
      int j = (p - k + 1) > 0 ? (p - k + 1) : 0;
      while (k + j < Slen && j < Tlen && S[k + j] == T[j]) j++;
      extand[k] = j;
      a = k;
    } else
      extand[k] = L;
  }
}

int main() {
  char s[N], t[N];
  while (~scanf("%s %s", s, t)) {
    getextand(s, t);
    for (int i = 0; i < strlen(t); i++) printf("%d ", next[i]);
    puts("");
    for (int i = 0; i < strlen(s); i++) printf("%d ", extand[i]);
    puts("");
  }
}
/*
aaaabaaa aaaa
*/