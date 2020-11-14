//
// Created by User on 11/7/2020.
//
#include<iostream>
#include "tree_requirements.h"

template<typename T>

struct Node {
    T data; // holds the key
    Node *parent; // pointer to the parent
    Node *left; // pointer to left child
    Node *right; // pointer to right child
    bool color; // true -> Red, false -> Black

};

template<typename T>

class RBTree : public Tree_Obligatory<Node, T>{
private:
    Node<T>* root;
    Node<T>* TNULL;
    unsigned int tree_size = 0;

    void leftRotate(Node<T>* x) {
        Node<T>* y = x->right;
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

    void rightRotate(Node<T>* x) {
        Node<T>* y = x->left;
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

    void fixDelete(Node<T>* x) {
        Node<T>* s;
        while (x != root && x->color == 0) {  //x is black and not root
            if (x == x->parent->left) {  //x is left child
                s = x->parent->right;    // s is sibling
                if (s->color == 1) { // if sibling is red
                    // case 3.1
                    s->color = 0;
                    x->parent->color = 1;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }
                if (s->left->color == 0 && s->right->color == 0) { // sibling has black children
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
            } else {              // x is right child, similarly
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

    void fixInsert(Node<T>* k){
        Node<T>* u;
        while (k->parent->color == 1) { // parent is red
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

    void deleteAllTree(Node<T>* node){
        if (node == TNULL)
            return;
        deleteAllTree(node->left);
        deleteAllTree(node->right);
        if(node->left == TNULL && node->right == TNULL){
            delete node;
            return;
        }
    }


public:
    RBTree() {
        TNULL = new Node<T>;
        TNULL->color = 0;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }

    ~RBTree(){
        deleteAllTree(this->root);
        delete TNULL;
    }

    unsigned int size(){
        return this->tree_size;
    }

    Node<T>* find(T key) {
        Node<T>* node = this->root;
        Node<T>* z = TNULL;
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

    void insert(T key) {
        this->tree_size++;

        Node<T>* node = new Node<T>;
        node->parent = nullptr;
        node->data = key;
        node->left = TNULL;
        node->right = TNULL;
        node->color = 1; // new node must be red

        Node<T>* y = nullptr;
        Node<T>* x = this->root;

        //find place for new node
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

    void erase(T key) {
        this->tree_size--;

        Node<T> *z = find(key); // find the node
        if (z == TNULL) {
            return;
        }

        if (z->left == TNULL and z->right == TNULL){
            if (z == root){
                root = TNULL;
            }else{
                if(z->parent->left == z){
                    z->parent->left = TNULL;
                }else{
                    z->parent->right = TNULL;
                }
            }
            return;
        }

        Node<T> *y;
        Node<T> *x;

        if (z->left == TNULL or z->right == TNULL) { // z has one child
            y = z;
        } else {
            y = z->right;
            while (y->left != TNULL) y = y->left; // find free tree successor with a leaf
        }

        // x is the only child of y:
        if (y->left != TNULL)
            x = y->left;
        else
            x = y->right;

        // remove y
        x->parent = y->parent;
        if (y->parent)
            if (y == y->parent->left) // y is left child
                y->parent->left = x;
            else
                y->parent->right = x;
        else
            root = x;

        if (y != z) z->data = y->data;

        if (y->color == false)
            fixDelete(x);

    }

    Node<T>* end(){
        return nullptr;
    }

};

