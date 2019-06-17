#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
#include <stack>
#include <vector>
typedef long long ll;
const ll mod = 1e9 + 7;
using namespace std;

const int N = 9;

bool check_row(int grid[N][N], int row, int num) {
  for(int col = 0; col < N; col ++) {
    if(grid[row][col] == num) return true;
  }
  return false;
}
bool check_col(int grid[N][N], int col, int num) {
  for(int row = 0; row < N; row ++) {
    if(grid[row][col] == num) return true;
  }
  return false;
}
bool check_square(int grid[N][N], int boxStartRow, int boxStartCol, int num) {
  for(int row = 0; row < 3; row++) {
    for(int col = 0; col < 3; col++) {
      if(grid[row + boxStartRow][col + boxStartCol] == num) return true;
    }
  }
  return false;
}
bool check(int grid[N][N], int row, int col, int num) {
  return !check_row(grid, row, num) && !check_col(grid,col,num) &&
         !check_square(grid, row - row % 3, col - col % 3, num);
}
void printGrid(int grid[N][N]) {
  for(int row = 0; row < N; row ++) {
    for(int col = 0; col < N; col ++) {
      printf("%2d", grid[row][col]);
    }
    printf("\n");
  }
}
bool FindUnassignedLocation(int grid[N][N], int& row, int& col) {
  for(row = 0; row < N; row ++) {
    for(col = 0; col < N; col ++) {
      if(grid[row][col] == 0) return true;
    }
  }
  return false;
}
bool dfs(int grid[N][N]) {
  int row, col;
  if(!FindUnassignedLocation(grid, row, col)) return true;
  for(int num = 1; num <= 9; num ++) {
    if(check(grid, row, col, num)) {
      grid[row][col] = num;
      if(dfs(grid)) return true;
      grid[row][col] = 0;
    }
  }
  return false;
}
int main(int argc, char const *argv[]) {
  int grid[N][N] = {{3, 0, 6, 5, 0, 8, 4, 0, 0},
                    {5, 2, 0, 0, 0, 0, 0, 0, 0},
                    {0, 8, 7, 0, 0, 0, 0, 3, 1},
                    {0, 0, 3, 0, 1, 0, 0, 8, 0},
                    {9, 0, 0, 8, 6, 3, 0, 0, 5},
                    {0, 5, 0, 0, 9, 0, 6, 0, 0},
                    {1, 3, 0, 0, 0, 0, 2, 5, 0},
                    {0, 0, 0, 0, 0, 0, 0, 7, 4},
                    {0, 0, 5, 2, 0, 6, 3, 0, 0}};
  if(dfs(grid)) {
    printGrid(grid);
  }
  else {
    std::cout << "No solutions." << '\n';
  }
  return 0;
}
