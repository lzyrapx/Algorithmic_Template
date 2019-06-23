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

/*
convert a left unbalanced BST to a balanced BST
*/
struct Node {
  int data;
  Node *left, *right;
};
void storeBSTNodes(Node* root, vector<Node*>&nodes) {
  if(root == nullptr) {
    return ;
  }
  storeBSTNodes(root -> left, nodes);
  nodes.push_back(root);
  storeBSTNodes(root -> right, nodes);
}
Node* build(vector<Node*>&nodes, int left, int right) {
  if(left > right) {
    return nullptr;
  }
  int mid = (left + right) >> 1;
  Node *root = nodes[mid];
  root -> left = build(nodes,left, mid - 1);
  root -> right = build(nodes, mid + 1, right);
  return root;
}
Node* buildTree(Node* root) {
  vector<Node*>nodes;
  storeBSTNodes(root, nodes);
  int n = nodes.size();
  Node* rt = build(nodes, 0, n - 1);
  return rt;
}
Node* create(int data) {
  Node* node = new Node;
  node -> data = data;
  node -> left = nullptr;
  node -> right = nullptr;
  return node;
}
// level order
void level_order(Node* root) {
  queue<Node*>que;
  que.push(root);
  que.push(create(-1));
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
  /* Constructed skewed binary tree is
				10
			/
			8
			/
			7
		/
		6
		/
		5 */
  Node* root = create(10);
  root -> left = create(8);
  root -> left -> left = create(7);
  root -> left -> left -> left = create(6);
  root -> left -> left -> left -> left = create(5);

  root = buildTree(root);
  std::cout << "Pre order: " << '\n';
  level_order(root);
  return 0;
}
