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

struct Node {
  int val;
  struct Node *left, *right;
};
struct Node* insert(int n) {
  Node *tmp = new Node;
  tmp -> val = n;
  tmp -> left = nullptr;
  tmp -> right =nullptr;
  return tmp;
}

void inorder(Node* root) {
  if(root != nullptr) {
    inorder(root -> left);
    std::cout << root -> val << ' ';
    inorder(root -> right);
  }
}
void postorder(Node* root) {
  if(root != nullptr) {
    postorder(root -> right);
    postorder(root -> left);
    std::cout << root -> val << ' ';
  }
}
void preorder(Node* root) {
  if(root != nullptr) {
    std::cout << root -> val << ' ';
    preorder(root -> left);
    preorder(root -> right);
  }
}
Node* build(Node* root, int n) {
  if(root == nullptr) {
    return insert(n);
  }
  else if(root -> val > n) {
    root -> left = build(root -> left, n);
  }
  else {
    root -> right = build(root -> right, n);
  }
  return root;
}
bool find(Node* root, int key) {
  if(root -> val > key && root -> left == nullptr) {
    return 0;
  }
  if(root -> val < key && root -> right == nullptr) {
    return 0;
  }
  if(root -> val == key) {
     return 1;
  }
  else if(root -> val > key) {
    find(root -> left, key);
  }
  else if(root -> val < key) {
    find(root -> right, key);
  }
  else {
    return 0;
  }
  return 0;
}
int countNodes(Node* root) {
  if(root == nullptr) {
    return 0;
  } else {
    return 1 + countNodes(root -> left) + countNodes(root -> right);
  }
}
int height(Node* root) {
  if(root == nullptr) {
    return 0;
  }
  return 1 + max(height(root -> left), height(root -> right));
}
int diameter(Node* root) {
  if(root == nullptr) {
    return 0;
  }
  return max(1 + height(root -> left) + height(root -> right),
         max(diameter(root -> left), diameter(root -> right)));
}
int main(int argc, char const *argv[]) {
  Node* root = nullptr;
  root = build(root ,5);
  // std::cout << root << '\n';
  build(root, 10);
  build(root, 20);
  build(root, 21);
  build(root, 14);
  build(root, 9);
  build(root, 3);
  build(root, 12);
  build(root, 21);
  // Inorder permutate from left -> root -> right
  cout << "The Inorder traversal of the tree is : ";
  inorder(root);
  cout << endl;
	// Postorder permutate from left -> right -> root
  cout << "The Postorder traversal of the tree is : ";
  postorder(root);
  cout << endl;
	// Preorder permutate from root -> left -> right
  cout << "The Preorder traversal of the tree is : ";
  preorder(root);
  cout << endl;
  // Count total number of nodes in the tree
  cout << "The number of nodes in the tree : ";
  cout << countNodes(root) << endl;
  cout << "The height of the tree is : ";
  cout << height(root) << endl;
  cout << "The diameter of the tree is : ";
  cout << diameter(root) << endl;
  return 0;
}
