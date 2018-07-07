// n*logn
scanf("%d", &T);
for (int kase = 1; kase <= T; kase++) {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%d", &a[i]);

  b[1] = a[1];
  len = 1;
  for (int i = 2; i <= n; i++)
    if (a[i] > b[len])
      b[++len] = a[i];
    else {
      int pos = lower_bound(b + 1, b + 1 + len, a[i]) - b;
      b[pos] = a[i];
    }
  printf("%d\n", len);
}