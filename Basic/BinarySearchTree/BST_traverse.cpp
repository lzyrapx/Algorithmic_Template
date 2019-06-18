#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
#include <stack>
#include <vector>
typedef long long ll;
using namespace std;

struct Node {
  int data;
  Node *left;
  Node *right;
};
Node* getNode(int data) {
  Node* tmp= new Node;
  tmp -> data = data;
  tmp -> left = nullptr;
  tmp -> right = nullptr;
  return tmp;
}
Node* insert_node(Node* root, int data) {
  if(root == nullptr) {
    return getNode(data);
  }
  if(root -> data > data) {
    root -> left = insert_node(root -> left, data);
  }
  else {
    root -> right = insert_node(root -> right, data);
  }
  return root;
}
// Inorder
void traverse(Node* root) {
  if(root == nullptr) {
    return ;
  }
  traverse(root -> left);
  std::cout << root -> data << ' ';
  traverse(root -> right);
}
// preorder
void pre_order(Node* root) {
  if(root == nullptr) {
    return;
  }
  std::cout << root -> data << ' ';
  pre_order(root -> left);
  pre_order(root -> right);
}
// level order
void level_order(Node* root) {
  queue<Node*>que;
  que.push(root);
  que.push(getNode(-1));
  while(!que.empty()) {
    Node* tmp = que.front();
    que.pop();
    if(!que.empty() && tmp -> data == -1) {
      std::cout << '\n';
      que.push(tmp);
    }
    else if(tmp -> data != -1) {
      std::cout << tmp -> data << ' ';
    }
    if(tmp -> left) {
      que.push(tmp -> left);
    }
    if(tmp -> right) {
      que.push(tmp -> right);
    }
  }
}
int main(int argc, char const *argv[]) {
  Node* root = nullptr;
  root = insert_node(root, 11);
  root = insert_node(root, 5);
  root = insert_node(root, 3);
  root = insert_node(root, 10);
  root = insert_node(root, 18);
  root = insert_node(root, 14);
  root = insert_node(root, 1);
  root = insert_node(root ,7);
  std::cout << "Inorder: ";
  traverse(root);
  std::cout << '\n';
  std::cout << "Preorder: ";
  pre_order(root);
  std::cout << '\n';
  std::cout << "Level order: \n ";
  level_order(root);
  std::cout << '\n';
  return 0;
}
