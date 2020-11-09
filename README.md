# trees_lab

First, let's check how the profiler works on std::set. Here are the plots with the true units. Each point is averaged on 1000 equal numbers and 2000 different ones.
![picture](set_lin.png)
Prof that the relation is logarithmic in different scales
![picture](set_log.png)
Let's go ahead and test Sasha's red-black tree. Each point is averaged on 2000 equal numbers and 4000 different ones (it took for std::set longer to do the same operations, which would take way more time to make more iterations there)
![picture](rbtree_lin.png)
And tree sizes to logarithmical.
![picture](rbtree_lin.png)