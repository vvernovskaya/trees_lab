#ifndef TREES_LAB_TREE_REQUIREMENTS_H
#define TREES_LAB_TREE_REQUIREMENTS_H


template <template<typename> class T, class M>   // T must be Node in the tree header file
class Tree_Obligatory {
protected:
    virtual void insert(M) = 0;
    virtual T<M>* find(M) = 0;
    virtual void erase(M) = 0;
    virtual T<M>* end() = 0;
    virtual unsigned int size() = 0;
};

#endif //TREES_LAB_TREE_REQUIREMENTS_H
