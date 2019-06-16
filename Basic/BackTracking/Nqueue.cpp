#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
using namespace std;

set<int>row_c,col_c,right_slant,left_slant;
void printBoard(vector<vector<int>>&board) {
  static int k = 1;
  cout << "Board " << k++ << ":\n";
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[i].size(); j++) {
      cout << board[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}
bool check(int row, int col) {
   if(row_c.find(row) != row_c.end()) return false;
   if(col_c.find(col) != col_c.end()) return false;
   if(left_slant.find(row - col) != left_slant.end()) return false;
   if(right_slant.find(row + col) != right_slant.end()) return false;
   return true;
}
void setBoard(vector<vector<int>>&board, int row, int col) {
  board[row][col] = 1;
  row_c.insert(row);
  col_c.insert(col);
  left_slant.insert(row - col);
  right_slant.insert(row + col);
}
void unsetBoard(vector<vector<int>>&board, int row, int col) {
  board[row][col] = 0;
  row_c.erase(row);
  col_c.erase(col);
  left_slant.erase(row - col);
  right_slant.erase(row + col);
}

void dfs(vector<std::vector<int>> &board, int row) {
  if(row == board.size()) {
    printBoard(board);
    return;
  }
  for(int i = 0; i < (int)board.size(); i++) {
    if(check(row, i)) {
      setBoard(board, row, i);
      dfs(board, row + 1);
      unsetBoard(board, row, i);
    }
  }
}
int main(int argc, char const *argv[]) {
  int n;
  // std::cin >>  n;
  n = 8;
  vector<vector<int>>board = std::vector<vector<int>>(n, vector<int>(n,0));
  dfs(board,0);
  return 0;
}
