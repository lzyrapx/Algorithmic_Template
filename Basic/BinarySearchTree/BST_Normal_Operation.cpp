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
  string data;
  Node *left;
  Node *right;
};
Node* getNode(string data) {
  Node* tmp= new Node;
  tmp -> data = data;
  tmp -> left = nullptr;
  tmp -> right = nullptr;
  return tmp;
}
// level order
void level_order(Node* root) {
  queue<Node*>que;
  que.push(root);
  que.push(getNode("root"));
  while(!que.empty()) {
    Node* tmp = que.front();
    que.pop();
    if(!que.empty() && tmp -> data == "root") {
      std::cout << '\n';
      que.push(tmp);
    }
    else if(tmp -> data != "root") {
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
Node* insert_node(Node* root, string data) {
  // std::cout << "r = " << root << '\n';
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
string find_help(Node* root, string k) {
  if(root == nullptr) {
    return "not exist";
  }
  else if(root -> data > k) {
    return find_help(root -> left, k);
  }
  else if(root -> data == k) {
    return "exist";
  }
  else {
    return find_help(root -> right, k);
  }
}
string find(Node* root, string k) {
  return find_help(root, k);
}

Node* getmin(Node* root) {
  struct Node* cur = root;
  while(cur -> left != nullptr) {
    cur = cur -> left;
  }
  return cur;
}
Node* remove(Node* root, string value) {
  if(root == nullptr) return root;
  if(root -> data > value) {
    root -> left = remove(root -> left, value);
  }
  else if(value > root -> data) {
    root -> right = remove(root -> right, value);
  }
  else {
    // node with only one child or no child
    if(root -> left == nullptr) {
      Node* tmp = root -> right;
      free(root);
      return tmp;
    }
    else if(root -> right == nullptr) {
      Node *tmp = root -> left;
      free(root);
      return tmp;
    }
    // node with two children: Get the inorder successor (smallest
    // in the right subtree)
    Node* tmp = getmin(root -> right);
    // Copy the inorder successor's content to this node
    root -> data = tmp -> data;
    // Delete the inorder successor
    root -> right = remove(root->right, tmp -> data);
  }
  return root;
}
int main(int argc, char const *argv[]) {
  Node* root = nullptr;
  root = insert_node(root, "a");
  root = insert_node(root, "ab");
  root = insert_node(root, "abc");
  root = insert_node(root, "abcd");
  root = insert_node(root, "abcde");
  level_order(root);
  std::cout << '\n';
  root = remove(root,"a");
  std::cout << "after delete 'a' : " << '\n';
  level_order(root);
  std::cout << '\n';
  return 0;
}
