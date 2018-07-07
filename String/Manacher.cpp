/*
  Manacher 求最长回文串 O(n)
  getstr预处理: abc -> $#a#b#c#
  len=strlen(s) , n=2*len+2
  p[i]为str[]第i个字符为中心的回文串长度+1
 */

char str[N << 1], s[N];
int p[N << 1];
int n, len;

void Manacher(char str[], int p[]) {
  int id, mx;
  id = 1, mx = 1;
  p[0] = p[1] = 1;
  int j;
  for (int i = 2; i < n; i++) {
    p[i] = 1;
    if (mx > i) {
      p[i] = min(p[(id << 1) - i], mx - i);
    }
    while (str[i + p[i]] == str[i - p[i]]) p[i]++;
    if (i + p[i] > mx) {
      id = i;
      mx = i + p[i];
    }
  }
}

void getstr() {
  str[0] = '$';
  str[n] = '#';
  str[n + 1] = '\0';
  for (int i = len * 2; i >= 1; --i) {
    if (i & 1)
      str[i] = '#';
    else
      str[i] = str[i / 2];
  }
}