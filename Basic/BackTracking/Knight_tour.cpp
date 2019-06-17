#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

#define N 8

typedef struct chess_moves {
  int x,y;
}chess_moves;

void printTour(int tour[N][N]) {
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      std::cout << tour[i][j] << '\t';
    }
    std::cout << '\n';
  }
}
bool check(chess_moves next_move, int tour[N][N]) {
  int i = next_move.x;
  int j = next_move.y;
  if((i >= 0 && i < N) && (j >= 0 && j < N) && (tour[i][j] == 0)) {
    return true;
  }
  return false;
}
bool dfs(int tour[N][N], chess_moves dir[], chess_moves cur_move, int move_count) {
  chess_moves next_move;
  if(move_count == N * N - 1) {
    return true;
  }
  for(int i = 0; i < N; i++) {
    next_move.x = cur_move.x + dir[i].x;
    next_move.y = cur_move.y + dir[i].y;
    if(check(next_move, tour)) {
      tour[next_move.x][next_move.y] = move_count + 1;
      if(dfs(tour, dir, next_move, move_count+1) == true) {
        return true;
      }
      else {
        tour[next_move.x][next_move.y] = 0;
      }
    }
  }
  return false;
}
void kightTour() {
  int tour[N][N];
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      tour[i][j] = 0;
    }
  }
  chess_moves dir[8] = {
    {2,1},{1,2},{-1,2},{-2,1},
    {-2,-1},{-1,-2},{1,-2},{2,-1}
  };
  chess_moves cur_move = {0,0};
  if(!dfs(tour, dir, cur_move, 0)) {
    std::cout << "No solutions" << '\n';
  }
  else {
    std::cout << "exist a solutions" << '\n';
    printTour(tour);
  }
}
int main(int argc, char const *argv[]) {
  kightTour();
  std::cout << '\n';
  return 0;
}
