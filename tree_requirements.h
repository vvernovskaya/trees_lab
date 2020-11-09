#ifndef TREES_LAB_TREE_REQUIREMENTS_H
#define TREES_LAB_TREE_REQUIREMENTS_H


template <class T>   // T must be Node* in the tree header file
class Tree_Obligatory {
protected:
    virtual void insert() = 0;
    virtual T find() = 0;
    virtual void erase() = 0;
    virtual T end() = 0;
    virtual int size() = 0;
};

#endif //TREES_LAB_TREE_REQUIREMENTS_H
