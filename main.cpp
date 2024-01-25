#include <iostream>
#include "bst.h"
#include "avl.h"
using namespace std;

int main() {
  BST *tree = new BST();

  // Agrega elementos al árbol
  tree->insert(5);
  tree->insert(3);
  tree->insert(7);
  tree->insert(2);
  tree->insert(4);
  tree->insert(6);
  tree->insert(8);

  // Imprime el árbol
  cout << "BST elements: "<< endl;
  cout << "Root: ";
  tree->BSTroot();
  cout << "BSTree: ";
  tree->printBSTRoot();
  cout <<endl;
  // PreOrder
  cout << "PreOrder: ";
  tree->printPreorder(tree->getRoot());
  cout<<endl;
  // InOrder
  cout << "InOrder: ";
  tree->printInorder(tree->getRoot());
  cout << endl;
  // PostOrder
  cout << "PostOrder: ";
  tree->printPostorder(tree->getRoot());
  cout << endl;

  cout<<endl;
  AVL avlTree;
  Node*nodo_a = new Node(10);
  Node*nodo_b = new Node(20);
  Node*nodo_c = new Node(30);
  Node*nodo_d = new Node(15);
  Node*nodo_e = new Node(5);
  cout<<"AVL Tree: "<<endl;
  avlTree.insert(nodo_a->data);
  avlTree.insert(nodo_b->data);
  avlTree.insert(nodo_c->data);
  avlTree.insert(nodo_d->data);
  avlTree.insert(nodo_e->data);
  avlTree.printTree();
  cout<<"Buscando nodo_d"<<endl;
  Node* nbuscado=avlTree.find(nodo_d->data);
  if(nbuscado!=NULL){
    cout<<"Nodo encontrado: "<<nbuscado->data<<endl;
  }
  else{
    cout<<"Nodo no encontrado"<<endl;
  }
  cout<<"Eliminando nodo_d"<<endl;
  avlTree.remove(nodo_d->data);
  avlTree.printTree();
  
}
