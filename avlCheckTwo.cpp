#include <iostream>
#include <fstream>

using namespace std;

struct AvlNode {
  int element;
  AvlNode* left;
  AvlNode* right;
  int height;

  AvlNode(const int& ele, AvlNode* lt, AvlNode* rt, int h = 0) {
    element = ele;
    left = lt;
    right = rt;
    height = h;
  }
};

int getHeight(AvlNode* node) {
  if (node == nullptr) {
    return 0;
  } else {
    return 1 + max(getHeight(node->left), getHeight(node->right));
  }
}

bool isAVL(AvlNode* node) {
  if (node == nullptr) {
    return true;
  }

  int leftHeight = getHeight(node->left);
  int rightHeight = getHeight(node->right);

  int balanceFactor = abs(leftHeight - rightHeight);
  if (balanceFactor > 1) {
    return false;
  }

  return isAVL(node->left) && isAVL(node->right);
}

void insert(AvlNode*& root, int element) {
  if (root == nullptr) {
    root = new AvlNode(element, nullptr, nullptr);
    return;
  }

  if (element < root->element) {
    insert(root->left, element);
  } else if (element > root->element) {
    insert(root->right, element);
  }
}

void printTree(AvlNode* root) {
  if (root == nullptr) {
    return;
  }

  printTree(root->left);
  cout << root->element << " ";
  printTree(root->right);
}

int main() {
  ifstream inputFile("input.txt");
  AvlNode* root = nullptr;

  string command;
  int element;
  while (inputFile >> command) {
    if (command == "insert") {
      inputFile >> element;
      insert(root, element);
    } else if (command == "print") {
      printTree(root);
      cout << endl;
    }
  }

  bool isAVLTree = isAVL(root);

  cout << "Is AVL tree: " << isAVLTree << endl;

  return 0;
}