#include <iostream>
#include <queue>

using namespace std;

// Definición de la estructura del nodo AVL
struct Node {
    int data;
    Node* left;
    Node* right;
    int height;

    Node(int value) : data(value), left(nullptr), right(nullptr), height(1) {}
};

class AVL {
private:
    Node *root;

    int height(Node *node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    int balanceFactor(Node *node) {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    Node *rightRotate(Node *y) {
        Node *x = y->left;
        Node *T2 = x->right;
        // Realiza la rotación
        x->right = y;
        y->left = T2;
        // Actualiza las alturas
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }

    Node *leftRotate(Node *x) {
        Node *y = x->right;
        Node *T2 = y->left;
        // Realiza la rotación
        y->left = x;
        x->right = T2;
        // Actualiza las alturas
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    Node *insert(Node *node, int value) {
        // Realiza la inserción normal de un árbol binario
        if (node == nullptr)
            return new Node(value);
        if (value < node->data)
            node->left = insert(node->left, value);
        else if (value > node->data)
            node->right = insert(node->right, value);
        else // No se permiten duplicados
            return node;
        // Actualiza la altura del nodo actual
        node->height = 1 + max(height(node->left), height(node->right));
        // Obtiene el factor de balance y realiza rotaciones si es necesario
        int balance = balanceFactor(node);
        // Casos de desequilibrio
        // Izquierda Izquierda
        if (balance > 1 && value < node->left->data)
            return rightRotate(node);
        // Derecha Derecha
        if (balance < -1 && value > node->right->data)
            return leftRotate(node);
        // Izquierda Derecha
        if (balance > 1 && value > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        // Derecha Izquierda
        if (balance < -1 && value < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    Node *minValueNode(Node *node) {
        Node *current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    Node *deleteNode(Node *root, int value) {
        // Realiza la eliminación normal de un árbol binario
        if (root == nullptr)
            return root;
        if (value < root->data)
            root->left = deleteNode(root->left, value);
        else if (value > root->data)
            root->right = deleteNode(root->right, value);
        else {
            // Nodo con uno o ningún hijo
            if (root->left == nullptr || root->right == nullptr) {
                Node *temp = (root->left != nullptr) ? root->left : root->right;
                // No hay hijo
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else  // Un hijo
                    *root = *temp;
                delete temp;
            } else {
                // Nodo con dos hijos, obtener el sucesor inorden (menor en el subárbol derecho)
                Node *temp = minValueNode(root->right);
                // Copiar el sucesor inorden al nodo actual
                root->data = temp->data;
                // Eliminar el sucesor inorden
                root->right = deleteNode(root->right, temp->data);
            }
        }
        // Si el árbol tenía solo un nodo, entonces retornar
        if (root == nullptr)
            return root;
        // Actualizar la altura del nodo actual
        root->height = 1 + max(height(root->left), height(root->right));
        // Obtener el factor de balance y realizar rotaciones si es necesario
        int balance = balanceFactor(root);
        // Casos de desequilibrio
        // Izquierda Izquierda
        if (balance > 1 && balanceFactor(root->left) >= 0)
            return rightRotate(root);
        // Derecha Derecha
        if (balance < -1 && balanceFactor(root->right) <= 0)
            return leftRotate(root);
        // Izquierda Derecha
        if (balance > 1 && balanceFactor(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        // Derecha Izquierda
        if (balance < -1 && balanceFactor(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        return root;
    }

    Node *search(Node *root, int value) {
        if (root == nullptr || root->data == value)
            return root;
        if (value < root->data)
            return search(root->left, value);
        return search(root->right, value);
    }

    void printInorder(Node *node) {
        if (node != nullptr) {
            printInorder(node->left);
            cout << node->data << " ";
            printInorder(node->right);
        }
    }

    void printPreorder(Node *node) {
        if (node != nullptr) {
            cout << node->data << " ";
            printPreorder(node->left);
            printPreorder(node->right);
        }
    }

    void printPostorder(Node *node) {
        if (node != nullptr) {
            printPostorder(node->left);
            printPostorder(node->right);
            cout << node->data << " ";
        }
    }

    void printLevelOrder() {
        if (root == nullptr)
            return;
        queue<Node *> q;
        q.push(root);
        while (!q.empty()) {
            Node *tempNode = q.front();
            q.pop();
            cout << tempNode->data << " ";
            if (tempNode->left != nullptr)
                q.push(tempNode->left);
            if (tempNode->right != nullptr)
                q.push(tempNode->right);
        }
    }

public:
    AVL() : root(nullptr) {}

    void insert(int value) {
        root = insert(root, value);
    }

    void remove(int value) {
        root = deleteNode(root, value);
    }

    Node* find(int value) {
        return search(root, value);
    }

    void traverseInorder() {
        cout << "Inorder Traversal: ";
        printInorder(root);
        cout << endl;
    }

    void traversePreorder() {
        cout << "Preorder Traversal: ";
        printPreorder(root);
        cout << endl;
    }

    void traversePostorder() {
        cout << "Postorder Traversal: ";
        printPostorder(root);
        cout << endl;
    }

    void printTree() {
        cout << "Level Order Traversal: ";
        printLevelOrder();
        cout << endl;
    }
};
