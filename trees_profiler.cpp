#include <iostream>
#include <chrono>
#include <vector>
#include <random>
#include <RBTree.h>

//include tree headers

double get_time() {
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()/1e6;
}

int32_t rand_num(int min, int max) {
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    static std::default_random_engine e(seed);
    std::uniform_int_distribution<int> d(min, max);
    return d(e);
}

template<class CurrTree>
class Profiler {
    pair<vector<int32_t>, vector<double>> table_insert;
    pair<vector<int32_t>, vector<double>> table_find;
    pair<vector<int32_t>, vector<double>> table_erase;

    vector<double> times_insert;
    vector<double> times_find;
    vector<double> times_erase;

    vector<int32_t> tree_sizes;

    CurrTree<int32_t> test_tree;

    Profiler() {
        initialize_sizes();
    }

    void initialize_sizes() {
        int32_t i = 1;
        while (i < 100) {
            tree_sizes.push_back(i);
            i += 10;
        }
        while (i < 3000) {
            tree_sizes.push_back(i);
            i += 100;
        }
        while (i < 15000) {
            tree_sizes.push_back(i);
            i+= 300;
        }
    }

    void test_insert() {
       for (int i_sz = 0; i_sz < tree_sizes.size(); i_sz++) {
           while (test_tree.size() < tree_sizes[i]) {
               break;
           }
       }
    }
    void test_erase() {
        return;
    }
    void test_find() {
        return;
    }

    void test_insert_local() {
        vector<double> curr_size_insert_times(20);
        for (int i = 0; i < 20; i++) {
            int32_t curr_num = rand_num(-10000, 10000);
            vector<double> curr_num_insert_times(10);
            for (int j = 0; j < 10; j++) {
                time_start = get_time();
                test_tree.insert(curr_num);
                time_finish = get_time();

                curr_num_insert_times.push_back(time_finish - time_start);
                test_tree.eraze(curr_num);
            }
            double avg = 0;
            for (int k = 0; k < 10; k++) {
                avg += curr_num_insert_times[i];
            }
            avg = double( (double) avg / n);
            curr_size_insert_times.push_back(avg);
        }
        double avg = 0;
        for (int k = 0; k < 20; k++) {
            avg += curr_size_insert_times[i];
        }
        avg = double( (double) avg / n);
        times_insert.push_back(avg);
    }
};

