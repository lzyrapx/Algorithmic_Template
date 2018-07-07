// 处理出一个字符串的所有回文子串。
const int N = 1e6 + 100;
char tmp[2 * N];
int r[2 * N];
int manacher(char *s) {
  int len = strlen(s);
  for (int i = 0; i < len; i++) {
    tmp[2 * i + 1] = '#';
    tmp[2 * i + 2] = s[i];
  }
  tmp[0] = '@';
  tmp[2 * len + 1] = '#';
  tmp[2 * len + 2] = '\0';
  len = 2 * len + 2;
  // printf("%s\n", tmp);
  int id, mx = 0, ret = 0;
  for (int i = 0; i < len; i++) {
    r[i] = i < mx ? Min(r[2 * id - i], mx - i) : 1;
    while (tmp[i + r[i]] == tmp[i - r[i]]) r[i]++;
    if (r[i] + i > mx) {
      mx = r[i] + i;
      id = i;
    }
    ret = Max(ret, r[i]);
  }
  // for (int i = 0; i < 2 * len + 1; i++) {
  //     printf("%d ", r[i]);
  // }
  return ret - 1;
}