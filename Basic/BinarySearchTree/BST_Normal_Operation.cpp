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
  if(root -> left == nullptr) {
    return root;
  }
  return getmin(root -> left);
}
Node* deletemin(Node* root) {
  if(root -> left == NULL) {
    return root -> right;
  }
  root -> left = deletemin(root -> left);
  return root;
}
Node* remove_help(Node* root, string k) {
  if(root == nullptr) {
    return nullptr;
  }
  if(root -> data > k) {
    root -> left = remove_help(root -> left, k);
  }
  else if(root -> data < k) {
    root -> right = remove_help(root -> right, k);
  }
  else {
    if(root -> left == nullptr) {
      return root -> right;
    }
    else if(root -> right == nullptr) {
      return root -> left;
    }
    else {
      Node* tmp = getmin(root -> right);
      root -> data = tmp -> data;
      root -> right = deletemin(root -> right);
    }
  }
}

string remove(Node* root, string k) {
  string tmp = find_help(root, k);
   std::cout << "tmp = " << tmp << '\n';
  if(tmp == "exist") {
    root = remove_help(root, root -> data);
  }
  return tmp;
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
  std::cout << find(root, "a") << '\n';
  std::cout << remove(root, "a") << '\n';
  level_order(root);
  std::cout << '\n';
  return 0;
}
