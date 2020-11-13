#include <iostream>
#include "tree_requirements.h"

template<typename T> class AVL;

template <typename T> class AVL_Node{
    T value;
    unsigned char height = 1;
    AVL_Node<T>* left = nullptr;
    AVL_Node<T>* right = nullptr;

    AVL_Node(T val){
        value = val;
    }
    ~AVL_Node(){
        delete left;
        delete right;
    }

    friend  class AVL<T>;
};

template<typename  T> class AVL : public Tree_Obligatory<AVL_Node, T>{
    unsigned int sizetree = 0;
    AVL_Node<T>* head = nullptr;
private:
    unsigned char height(AVL_Node<T>* p)
    {
        return p?p->height:0;
    }

    int bfactor(AVL_Node<T>* p)
    {
        return height(p->right)-height(p->left);
    }

    void fixheight(AVL_Node<T>* p)
    {
        unsigned char hl = height(p->left);
        unsigned char hr = height(p->right);
        p->height = (hl>hr?hl:hr)+1;
    }

    AVL_Node<T>* rotateright(AVL_Node<T>* p) // правый поворот вокруг p
    {
        AVL_Node<T>* q = p->left;
        p->left = q->right;
        q->right = p;
        fixheight(p);
        fixheight(q);
        return q;
    }

    AVL_Node<T>* rotateleft(AVL_Node<T>* q) // левый поворот вокруг q
    {
        AVL_Node<T>* p = q->right;
        q->right = p->left;
        p->left = q;
        fixheight(q);
        fixheight(p);
        return p;
    }

    AVL_Node<T>* balance(AVL_Node<T>* p) // балансировка узла p
    {
        fixheight(p);
        if( bfactor(p)==2 )
        {
            if( bfactor(p->right) < 0 )
                p->right = rotateright(p->right);
            return rotateleft(p);
        }
        if( bfactor(p)==-2 )
        {
            if( bfactor(p->left) > 0  )
                p->left = rotateleft(p->left);
            return rotateright(p);
        }
        return p; // балансировка не нужна
    }

    AVL_Node<T>* insert(AVL_Node<T>* p, T value) // вставка ключа value в дерево с корнем p
    {
        if( !p ) {
            sizetree++;
            return new AVL_Node<T>(value);
        }
        if( value<p->value )
            p->left = insert(p->left,value);
        else
            p->right = insert(p->right,value);
        return balance(p);
    }

    AVL_Node<T>* findmin(AVL_Node<T>* p) // поиск узла с минимальным ключом в дереве p
    {
        return p->left?findmin(p->left):p;
    }

    AVL_Node<T>* erase_rmin(AVL_Node<T>* p) // удаление узла с минимальным ключом из дерева p
    {
        if( p->left==0 )
            return p->right;
        p->left = erase_rmin(p->left);
        return balance(p);
    }


    AVL_Node<T>* erase(AVL_Node<T>* p, T value)
    {
        if (!p)
            return p;

        if (value < p->value)
            p->left = erase(p->left, value);

        else if (value > p->value)
            p->right = erase(p->right, value);

        else {
            sizetree--;
            if (!p->right)
                return p->left;

            p = erase_rmin(p);
        }
        return balance(p);
    }


    void print(AVL_Node<T>* node)
    {
        if (!node)
            return;
        print(node->left);
        //std::cout << node->value << ' ';
        print(node->right);
    }

    void deletetree(AVL_Node<T>* p){
        if(!p->left){
            deletetree(p->left);
        }
        if(!p->right){
            deletetree(p->right);
        }
        delete p;
    }


public:

    ~AVL<T>(){
        deletetree(head);
    }

    void insert(T value)
    {
        //std::cout << "insert " << value<<'\n';
        if(!find(value))
            head = insert(head, value);
    }

    void erase(T value)
    {
        //std::cout << "erase " << value<<'\n';

        head = erase(head, value);
    }

    AVL_Node<T>* find(T value)
    {
        AVL_Node<T>* current = head;
        while(current and current->value != value){
            if(value < current->value)
                current = current->left;
            else
                current = current->right;

        }
        return current;

    }


    bool empty()
    {
        if(sizetree==0)
            return true;
        else
            return false;
    }

    void print()
    {
        print(head);
        std::cout << "\n";
    }
    
    unsigned int size(){
    	return sizetree;
    }
    
    AVL_Node<T>* end(){
    	return nullptr;
    }

};
