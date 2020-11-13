#include "tree_requirements.h"

// This is an example of how to implement tree_requirements into your tree

class Iterator : Tree_Iterator_Obligatory<Iterator> {
public:
    int a;

    Iterator(int a) {
        this->a = a;
    }

    bool operator== (Iterator& other) {
        return (this->a == other.a);
    }
};

int main() {
    return 0;
}
