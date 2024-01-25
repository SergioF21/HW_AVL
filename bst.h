#include <iostream>

using namespace std;

class BST{

private:

struct NodoBT{

  int data;

  NodoBT *right;
  NodoBT *left;

  NodoBT(int data){

    this->data = data;
    this->right = NULL;
    this->left = NULL;
  }
};

NodoBT *root; // puntero que apunta a nodo principal o raiz.

public:
BST()
{
  root = nullptr;

}
NodoBT* getRoot(){
  return root;
}
void insert(int data, NodoBT *&node){
  if(node == nullptr){
    node = new NodoBT(data);
  }
  if(data > node->data){ // NULL solo funciona para punteros
    insert(data, node->right);
  }
  if(data < node->data){
    insert(data, node->left);
  }
}

void insert(int data){
 insert(data, root);
}

void printBST(NodoBT *node){
  if(node != NULL){
    cout << node->data << " ";
  }
  else {
    return;
  }
  printBST(node->left);
  printBST(node->right);
}

void printBSTRoot(){
  printBST(root);
}

void BSTroot(){
  cout << root->data << endl;
}
void printInorder(NodoBT *node) {
    if (node != nullptr) {
        printInorder(node->left);
        cout << node->data << " ";
        printInorder(node->right);
    }
}

void printPreorder(NodoBT *node) {
    if (node != nullptr) {
        cout << node->data << " ";
        printPreorder(node->left);
        printPreorder(node->right);
    }
}

void printPostorder(NodoBT *node) {
    if (node != nullptr) {
        printPostorder(node->left);
        printPostorder(node->right);
        cout << node->data << " ";
    }
}

};

