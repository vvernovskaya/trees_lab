//
// Created by User on 11/7/2020.
//
#include<iostream>


// data structure that represents a node in the tree
struct Node {
    int data; // holds the key
    Node *parent; // pointer to the parent
    Node *left; // pointer to left child
    Node *right; // pointer to right child
    int color; // 1 -> Red, 0 -> Black
};


// class RBTree implements the operations in Red Black Tree
class RBTree {
private:
    Node* root;
    Node* TNULL;
    unsigned int tree_size = 0;

    // initializes the nodes with appropriate values
    // all the pointers are set to point to the null pointer
    void initializeNULLNode(Node* node, Node* parent) {
        node->data = 0;
        node->parent = parent;
        node->left = nullptr;
        node->right = nullptr;
        node->color = 0;
    }

    void preOrderHelper(Node* node) {
        if (node != TNULL) {
             preOrderHelper(node->left);
            preOrderHelper(node->right);
        }
    }

    void inOrderHelper(Node* node) {
        if (node != TNULL) {
            inOrderHelper(node->left);
             inOrderHelper(node->right);
        }
    }

    void postOrderHelper(Node* node) {
        if (node != TNULL) {
            postOrderHelper(node->left);
            postOrderHelper(node->right);
         }
    }

    Node* searchTreeHelper(Node* node, int key) {
       /* if (node == TNULL || key == node->data) {
            return node;
        }

        if (key < node->data) {
            return searchTreeHelper(node->left, key);
        }
        return searchTreeHelper(node->right, key);
        */

        Node* z = TNULL;
        Node* x, y;
        while (node != TNULL){
            if (node->data == key) {
                z = node;
            }

            if (node->data <= key) {
                node = node->right;
            } else {
                node = node->left;
            }
        }


        return z;
    }

    // fix the rb tree modified by the delete operation
    void fixDelete(Node* x) {
        Node* s;
        while (x != root && x->color == 0) {  //x is black
            if (x == x->parent->left) {  //x is left child
                s = x->parent->right;
                if (s->color == 1) {
                    // case 3.1
                    s->color = 0;
                    x->parent->color = 1;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }

                if (s->left->color == 0 && s->right->color == 0) {
                    // case 3.2
                    s->color = 1;
                    x = x->parent;
                } else {
                    if (s->right->color == 0) {
                        // case 3.3
                        s->left->color = 0;
                        s->color = 1;
                        rightRotate(s);
                        s = x->parent->right;
                    }

                    // case 3.4
                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->right->color = 0;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {              // x is right child
                s = x->parent->left;
                if (s->color == 1) {
                    // case 3.1
                    s->color = 0;
                    x->parent->color = 1;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }

                if (s->right->color == 0 && s->left->color == 0) {
                    // case 3.2
                    s->color = 1;
                    x = x->parent;
                } else {
                    if (s->left->color == 0) {
                        // case 3.3
                        s->right->color = 0;
                        s->color = 1;
                        leftRotate(s);
                        s = x->parent->left;
                    }

                    // case 3.4
                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->left->color = 0;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = 0;
    }


    void rbTransplant(Node* u, Node* v){
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left){
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    void deleteNodeHelper(Node* node, int key) {
        // find the node containing key
        Node* z = TNULL;
        Node* x;
        Node* y;
        while (node != TNULL){
            if (node->data == key) {
                z = node;
            }

            if (node->data <= key) {
                node = node->right;
            } else {
                node = node->left;
            }
        }

        if (z == TNULL) {
             return;
        }

        y = z;
        int y_original_color = y->color;
        if (z->left == TNULL) {
            x = z->right;
            rbTransplant(z, z->right);
        } else if (z->right == TNULL) {
            x = z->left;
            rbTransplant(z, z->left);
        } else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_original_color == 0){
            fixDelete(x);
        }
    }

    // fix the red-black tree
    void fixInsert(Node* k){
        Node* u;
        while (k->parent->color == 1) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left; // uncle
                if (u->color == 1) {
                    // case 3.1
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        // case 3.2.2
                        k = k->parent;
                        rightRotate(k);
                    }
                    // case 3.2.1
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    leftRotate(k->parent->parent);
                }
            } else {
                u = k->parent->parent->right; // uncle

                if (u->color == 1) {
                    // mirror case 3.1
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        // mirror case 3.2.2
                        k = k->parent;
                        leftRotate(k);
                    }
                    // mirror case 3.2.1
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color = 0;
    }


public:
    RBTree() {
        TNULL = new Node;
        TNULL->color = 0;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }

    ~RBTree(){
        delete root;
        delete TNULL;
    }

    unsigned int size(){
        return this->tree_size;
    }
    // Pre-Order traversal
    // Node->Left Subtree->Right Subtree
    void preorder() {
        preOrderHelper(this->root);
    }

    // In-Order traversal
    // Left Subtree -> Node -> Right Subtree
    void inorder() {
        inOrderHelper(this->root);
    }

    // Post-Order traversal
    // Left Subtree -> Right Subtree -> Node
    void postorder() {
        postOrderHelper(this->root);
    }

    // search the tree for the key k
    // and return the corresponding node
    Node* find(int k) {
        return searchTreeHelper(this->root, k);
    }

    // find the node with the minimum key
    Node* minimum(Node* node) {
        while (node->left != TNULL) {
            node = node->left;
        }
        return node;
    }

    // find the node with the maximum key
    Node* maximum(Node* node) {
        while (node->right != TNULL) {
            node = node->right;
        }
        return node;
    }


    // rotate left at node x
    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    // rotate right at node x
    void rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    // insert the key to the tree in its appropriate position
    // and fix the tree
    void insert(int key) {
        // Ordinary Binary Search Insertion
        this->tree_size++;
        Node* node = new Node;
        node->parent = nullptr;
        node->data = key;
        node->left = TNULL;
        node->right = TNULL;
        node->color = 1; // new node must be red

        Node* y = nullptr;
        Node* x = this->root;

        while (x != TNULL) {
            y = x;
            if (node->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        // y is parent of x
        node->parent = y;
        if (y == nullptr) {
            root = node;
        } else if (node->data < y->data) {
            y->left = node;
        } else {
            y->right = node;
        }

        // if new node is a root node, simply return
        if (node->parent == nullptr){
            node->color = 0;
            return;
        }

        // if the grandparent is null, simply return
        if (node->parent->parent == nullptr) {
            return;
        }

        // Fix the tree
        fixInsert(node);
    }


    // delete the node from the tree
    void erase(int data) {
        this->tree_size--;
        deleteNodeHelper(this->root, data);
    }


};

