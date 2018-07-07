#include <iostream>
#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;
const int maxa = 500000;
const int cha = 26;
int n, m, k;
struct Tire {
  int next[maxa][cha], fail[maxa], end[maxa];
  int root, L;
  int newnode() {
    for (int i = 0; i < cha; i++) {
      next[L][i] = -1;
    }
    end[L++] = 0;
    return L - 1;
  }
  void init() {
    L = 0;
    root = newnode();
  }
  void insert(char buf[]) {
    int len = strlen(buf);
    int now = root;
    for (int i = 0; i < len; i++) {
      if (next[now][buf[i] - 'a'] == -1) next[now][buf[i] - 'a'] = newnode();
      now = next[now][buf[i] - 'a'];
      // printf("%d ", now);
    }  // puts("");
    end[now]++;
  }
  void build() {
    queue<int> Q;
    fail[root] = root;
    for (int i = 0; i < cha; i++) {
      if (next[root][i] == -1)
        next[root][i] = root;
      else {
        fail[next[root][i]] = root;
        Q.push(next[root][i]);
      }
    }
    while (!Q.empty()) {
      int now = Q.front();
      Q.pop();
      // end[now] |= end[fail[now]];
      for (int i = 0; i < cha; i++) {
        if (next[now][i] == -1)
          next[now][i] = next[fail[now]][i];
        else {
          fail[next[now][i]] = next[fail[now]][i];
          Q.push(next[now][i]);
          // printf("**%d %d\n",next[now][i],next[fail[now]][}
        }
      }
    }
  }
  int solve(char *s) {
    int ans = 0, k = 0;
    for (int i = 0; s[i]; i++) {
      int t = s[i] - 'a';
      k = next[k][t];
      int j = k;
      while (j) {
        ans += end[j];
        // if(end[j]) printf("%d ",j);
        end[j] = 0;
        j = fail[j];
      }  // puts("");
    }
    return ans;
  }
};
char buf[1000005];
Tire ac;
int main() {
  int t, n;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    ac.init();
    // memset(ac.end, 0, sizeof(ac.end));
    for (int i = 0; i < n; i++) {
      scanf("%s", buf);
      ac.insert(buf);
    }
    ac.build();
    scanf("%s", buf);
    printf("%d\n", ac.solve(buf));
  }
  return 0;
}

/*
1
5
abcdefg
bcdefg
cdef
de
e
ssaabcdefg
*/