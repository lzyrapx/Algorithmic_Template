
/*   gauss_elimination  O(n^3)
   return 1,有解，return 0,无解。。
   n个方程n个变元
   要求系数矩阵可逆
   A[][]是增广矩阵,即A[i][n]是第i个方程右边的常数bi
   运行结束后A[i][n]是第i个未知数的值    
 */

double A[N][N];

int gauss(int n) {
  int i, j, k, r;
  for (i = 0; i < n; i++) {
    //选一行与r与第i行交换，提高数据值的稳定性
    r = i;
    for (j = i + 1; j < n; j++)
      if (fabs(A[j][i]) > fabs(A[r][i])) r = j;
    if (r != i)
      for (j = 0; j <= n; j++) swap(A[r][j], A[i][j]);
    // i行与i+1~n行消元
    /*  for(k=i+1;k<n;k++){   //从小到大消元，中间变量f会有损失
          double f=A[k][i]/A[i][i];
          for(j=i;j<=n;j++)A[k][j]-=f*A[i][j];
      }*/
    for (j = n; j >= i; j--) {  //从大到小消元，精度更高
      for (k = i + 1; k < n; k++) A[k][j] -= A[k][i] / A[i][i] * A[i][j];
    }
  }
  //判断方程时候有解
  for (i = 0; i < n; i++)
    if (sign(A[i][i]) == 0) return 0;
  //回代过程
  for (i = n - 1; i >= 0; i--) {
    for (j = i + 1; j < n; j++) A[i][n] -= A[j][n] * A[i][j];
    A[i][n] /= A[i][i];
  }
}

/*   整数矩阵   O( n^3 )
  高斯消元法解方程组(Gauss-Jordan elimination).(-2表示有浮点数解，但无整数解，
  -1表示无解，0表示唯一解，大于0表示无穷解，并返回自由变元的个数)
  有equ个方程，var个变元。增广矩阵行数为equ,分别为0到equ-1,列数为var+1,分别为0到var.
  */

int a[N][N];     //增广矩阵
int x[N];        //解集
bool free_x[N];  //标记是否是不确定的变元
int n, m, k;

//
void Debug(int equ, int var) {
  int i, j;
  for (i = 0; i < equ; i++) {
    for (j = 0; j < var + 1; j++) {
      cout << a[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}
//

inline int gcd(int a, int b) {
  int t;
  while (b != 0) {
    t = b;
    b = a % b;
    a = t;
  }
  return a;
}
inline int lcm(int a, int b) {
  return a / gcd(a, b) * b;  //先除后乘防溢出
}

// 高斯消元法解方程组(Gauss-Jordan elimination).(-2表示有浮点数解，但无整数解，
//-1表示无解，0表示唯一解，大于0表示无穷解，并返回自由变元的个数)
//有equ个方程，var个变元。增广矩阵行数为equ,分别为0到equ-1,列数为var+1,分别为0到var.
int Gauss(int equ, int var) {
  int i, j, k;
  int max_r;  // 当前这列绝对值最大的行.
  int col;    //当前处理的列
  int ta, tb;
  int LCM;
  int temp;
  int free_x_num;
  int free_index;

  for (int i = 0; i <= var; i++) {
    x[i] = 0;
    free_x[i] = true;
  }

  //转换为阶梯阵.
  col = 0;                                         // 当前处理的列
  for (k = 0; k < equ && col < var; k++, col++) {  // 枚举当前处理的行.
                                                   // 找到该col列元素绝对值最大的那行与第k行交换.(为了在除法时减小误差)
    max_r = k;
    for (i = k + 1; i < equ; i++) {
      if (abs(a[i][col]) > abs(a[max_r][col])) max_r = i;
    }
    if (max_r != k) {  // 与第k行交换.
      for (j = k; j < var + 1; j++) swap(a[k][j], a[max_r][j]);
    }
    if (a[k][col] == 0) {  // 说明该col列第k行以下全是0了，则处理当前行的下一列.
      k--;
      continue;
    }
    for (i = k + 1; i < equ;
         i++)  //  i=0高斯约当消元,才能在多解的情况下判断变元是否确定
    {  // 枚举要删去的行.
      if (a[i][col] != 0 && i != k) {
        LCM = lcm(abs(a[i][col]), abs(a[k][col]));
        ta = LCM / abs(a[i][col]);
        tb = LCM / abs(a[k][col]);
        if (a[i][col] * a[k][col] < 0) tb = -tb;  //异号的情况是相加
        for (j = 0; j < var + 1; j++) {
          a[i][j] = a[i][j] * ta - a[k][j] * tb;
        }
      }
    }
  }

  //  Debug(equ,var);

  // 1. 无解的情况: 化简的增广阵中存在(0, 0, ..., a)这样的行(a != 0).
  for (i = k; i < equ; i++) {
    if (a[i][col] != 0) return -1;
  }
  // 对于无穷解来说，如果要判断哪些是自由变元，那么初等行变换中的交换就会影响，则要记录交换.
  // 2. 无穷解的情况: 在var * (var + 1)的增广阵中出现(0, 0, ...,
  // 0)这样的行，即说明没有形成严格的上三角阵.
  // 且出现的行数即为自由变元的个数.
  if (k < var) return 1;
  {
    // 首先，自由变元有var - k个，即不确定的变元至少有var - k个.
    for (i = k - 1; i >= 0; i--) {
      // 第i行一定不会是(0, 0, ..., 0)的情况，因为这样的行是在第k行到第equ行.
      // 同样，第i行一定不会是(0, 0, ..., a), a != 0的情况，这样的无解的.
      free_x_num =
          0;  // 用于判断该行中的不确定的变元的个数，如果超过1个，则无法求解，它们仍然为不确定的变元.
      for (j = 0; j < var; j++) {
        if (a[i][j] != 0 && free_x[j]) free_x_num++, free_index = j;
      }
      if (free_x_num > 1) continue;  // 无法求解出确定的变元.
      // 说明就只有一个不确定的变元free_index，那么可以求解出该变元，且该变元是确定的.
      temp = a[i][var];
      for (j = 0; j < var; j++) {
        if (a[i][j] != 0 && j != free_index) temp -= a[i][j] * x[j];
      }
      x[free_index] = temp / a[i][free_index];  // 求出该变元.
      free_x[free_index] = 0;                   // 该变元是确定的.
    }
    return var - k;  // 自由变元有var - k个.
  }
  // 3. 唯一解的情况: 在var * (var + 1)的增广阵中形成严格的上三角阵.
  // 计算出Xn-1, Xn-2 ... X0.
  for (i = var - 1; i >= 0; i--) {
    temp = a[i][var];
    for (j = i + 1; j < var; j++) {
      if (a[i][j] != 0) temp -= a[i][j] * x[j];
    }
    if (temp % a[i][i] != 0) return -2;  // 说明有浮点数解，但无整数解.
    x[i] = temp / a[i][i];
  }
  return 0;
}

/*  异或矩阵  O( n^3 )
   高斯-约当消元
   如果无解return -1，如果有唯一解，返回变化个数
   如果方程有多个解，则二进制枚举自由变元O(2^n)，返回最小变化个数！，
   n个方程n个变元
   A[][]增广矩阵
   B[]结果矩阵
   is_free[]在有多解的情况下,判断元素解是否唯一 */

int A[N][N], B[N], is_free[N], num[N];

void getA(int n) { /*  得到增广矩阵A[][]   */ }

int gauss(int n) {
  int i, j, k, cnt, row, ok, ret, up, cnt_free;
  for (i = row = 0; i < n; i++) {
    if (!A[row][i]) {
      for (j = row + 1; j < n; j++) {
        if (A[j][i]) {
          for (k = i; k <= n; k++) swap(A[row][k], A[j][k]);
          break;
        }
      }
    }
    if (A[row][i] != 1) continue;  //保证为严格的阶梯矩阵
    for (j = 0; j < n; j++) {      //从0开始,高斯约当消元
      if (j != row && A[j][i]) {
        for (k = i; k <= n; k++) A[j][k] ^= A[row][k];
      }
    }
    row++;
  }
  for (i = n - 1; i >= row; i--)
    if (A[i][n]) return -1;  //无解
  if (row == n) {            //唯一解
    for (i = ret = 0; i < n; i++)
      if (A[i][n]) ret++;
    return ret;
  }
  mem(is_free, 0);
  for (i = k = j = 0; i < n; i++, j++) {
    while (!A[i][j] && j < n) {
      is_free[j] = 1;  //判断元素是否解唯一
      num[k++] = j++;
    }
  }
  ret = INF;
  cnt_free = n - row;  //自由变元个数
  up = 1 << cnt_free;
  for (k = 0; k < up; k++) {  //枚举最小的变换个数
    for (i = 0; i < cnt_free; i++) B[num[i]] = (k & (1 << i)) ? 1 : 0;
    for (i = n - 1; i >= 0; i--) {
      if (is_free[i]) continue;
      B[i] = 0;
      for (j = row; j < n; j++) B[i] ^= B[j] * A[i][j];
      B[i] ^= A[i][n];
    }
    for (i = cnt = 0; i < n; i++)
      if (B[i]) cnt++;
    ret = Min(ret, cnt);
  }
  return ret;  //返回最小的变换个数
}
