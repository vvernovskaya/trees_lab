//
// Created by User on 11/7/2020.
//
#include "RBTree.h"

int main() {
    RBTree<int> my_tree_int;

    my_tree_int.insert(1);
    my_tree_int.insert(2);
    my_tree_int.find(1);
    my_tree_int.erase(1);
    my_tree_int.find(1);
    std::cout << my_tree_int.size() << "\n";

    RBTree<double> my_tree_double;

    my_tree_double.insert(3.2);
    my_tree_double.insert(4.3);
    my_tree_double.insert(0.4);
    std::cout << my_tree_double.size();
    return 0;
}
