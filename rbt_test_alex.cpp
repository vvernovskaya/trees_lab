//
// Created by User on 11/7/2020.
//

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "RBTree.h"

int main() {
    std::cout << "before  tree\n";
    RBTree<int> my_tree_int;
    std::cout << my_tree_int.size() << "\n";

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

    if (my_tree_double.end() == nullptr){
        std::cout << "end\n";
    }

    _CrtDumpMemoryLeaks();


    return 0;
}
