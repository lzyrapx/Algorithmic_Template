// https://loj.ac/problem/103
// res表示 B 在 A 中的出现次数。
// fail就是next数组
int kmp(char *a, char *b)  // 在 a 中寻找 b
{
  // 求出字符串长度
  int na = strlen(a + 1), nb = strlen(b + 1);
  static int fail[MAXN + 1];

  fail[1] = 0;
  for (int i = 2; i <= nb; i++) {
    // 取上一位置的 fail 位置之后的字符，判断是否和该位相同
    int j = fail[i - 1];
    // 不断地向前找 fail 位置，直到找到 0 位置或可以匹配当前字符
    while (j != 0 && b[j + 1] != b[i]) j = fail[j];

    // 如果能匹配，设置当前位置的 fail 位置
    if (b[j + 1] == b[i])
      fail[i] = j + 1;
    else
      fail[i] = 0;  // 找不到匹配位置
  }

  int res = 0;  // 匹配次数
  for (int i = 1, j = 0; i <= na; i++) {
    // 取上一位置的 fail 位置之后的字符，判断是否和要匹配的字符相同
    while (j != 0 && b[j + 1] != a[i]) j = fail[j];

    // 这一位可以匹配上
    if (b[j + 1] == a[i]) j++;

    // 匹配成功
    if (j == nb) {
      res++;
      j = fail[j];  // 为了能匹配重叠串
                    // j = 0; // 如果不允许重叠匹配
    }
  }

  return res;
}