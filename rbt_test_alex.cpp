//
// Created by User on 11/7/2020.
//
#include "RBTree.h"

int main() {
    RBTree my_tree;

    my_tree.insert(1);
    my_tree.insert(2);
    my_tree.find(1);
    my_tree.erase(1);
    my_tree.find(1);
    return 0;
}
