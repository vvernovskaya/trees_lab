# trees_lab

Here are the results for testing trees with the profiler. First, it fills the tree with random elements up to a certain size of a tree. Then the three functions (insert(), erase() and find()) are tested separately.
<br />
Let's start with checking how the profiler works on std::set. Here are the plots with the true units. Each point is averaged on 1000 equal numbers and 2000 different ones.
![picture](plots/set/set_lin.png)
Prof that the relation is logarithmic in different scales
![picture](plots/set/set_log.png)
Let's go ahead and test Sasha's red-black tree. Each point is averaged on 2000 equal numbers and 4000 different ones (it took for std::set longer to do the same operations, which would take way more time to make more iterations there)
![picture](plots/RBTree/rbtree_lin.png)
And tree sizes to logarithmical.
![picture](plots/RBTree/rbtree_log.png)
Same with Arkadiy's AVL-tree.
![picture](plots/AVLTree/avl_lin.png)
![picture](plots/AVLTree/avl_log.png)