// max(XorSum(a_l^r))

#include <bits/stdc++.h>

using namespace std;
const int MAX = 1e6 + 100;
int bas[35];
const int INF = 2147483645;
struct Trie {
  int nxt[MAX << 2][2];
  int l[MAX << 2];
  int cnt;
  int ansl, ansr, ansv;
  void init() {
    cnt = 0;
    memset(nxt[0], 0, sizeof(nxt[0]));
    memset(l, 0x3f3f3f3f, sizeof(l));
    ansv = 0;
  }
  int create() {
    cnt++;
    memset(nxt[cnt], 0, sizeof(nxt[cnt]));
    return cnt;
  }
  void insert(int id, int x) {
    int y = 0;
    for (int i = 30; i >= 0; i--) {
      int t = x & bas[i];
      t >>= i;
      if (!nxt[y][t]) {
        nxt[y][t] = create();
      }
      y = nxt[y][t];
    }
    l[y] = min(l[y], id);
  }
  void query(int id, int x) {
    int y = 0;
    int res = 0;
    for (int i = 30; i >= 0; i--) {
      int t = x & bas[i];
      t >>= i;
      if (nxt[y][!t]) {
        y = nxt[y][!t];
        res += bas[i];
      } else {
        y = nxt[y][t];
      }
    }
    if (res == ansv) {
      if (l[y] < ansl) {
        ansl = l[y];
        ansr = id;
      }
    } else if (res > ansv) {
      ansv = res;
      ansl = l[y];
      ansr = id;
    }
  }
  void print(int id) {
    printf("Case #%d:\n%d %d\n", id, ansl + 1, ansr); // 区间
    std::cout << "max xor sum = " << ansv << '\n';
  }
} trie;

void init() {
  bas[0] = 1;
  for (int i = 1; i <= 30; i++) {
    bas[i] = bas[i - 1] << 1;
  }
}

int main(int argc, char const *argv[]) {
  init();
  int n, Cas;
  scanf("%d", &Cas);
  for (int i = 1; i <= Cas; i++) {
    trie.init();
    trie.insert(0, 0);
    scanf("%d", &n);
    int sum = 0;
    for (int j = 1; j <= n; j++) {
      int ai;
      scanf("%d", &ai);
      sum ^= ai;
      trie.query(j, sum);
      trie.insert(j, sum);
    }
    trie.print(i);
  }
  return 0;
}
