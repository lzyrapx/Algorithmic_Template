/*
 * @Author: zhaoyang.liang
 * @Github: https://github.com/LzyRapx
 * @Date: 2019-06-13 00:02:05
 */

#include <cstdio>
#include <iostream>
using namespace std;

int Next[20];
void get_nextval(char T[], int Next[]) {
  int j, k;
  j = 0;
  Next[0] = -1;
  k = -1;
  while (T[j + 1] != '\0') {
    if (k == -1 || T[j] == T[k]) {
      ++j, ++k;
      if (T[j] != T[k])
        Next[j] = k;
      else
        Next[j] = Next[k];
    } else
      k = Next[k];
  }
}

int Index_KMP(char S[], char T[], int pos) {
  int i, j;
  i = pos - 1;
  j = 0;
  while (S[i] != '\0' && T[j] != '\0') {
    if (j == -1 || S[i] == T[j])
      i++, j++;
    else
      j = Next[j];
  }
  if (T[j] == '\0')
    return (i - j);
  else
    return 0;
}

int main() {
  int m;
  char S[20] = "abcdfadabddfa";
  char T[20] = "bc";
  get_nextval(T, Next);
  m = Index_KMP(S, T, 1);
  printf("%d\n", m);
  getchar();
  return 0;
}
