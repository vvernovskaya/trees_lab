#include <iostream>
#include <chrono>
#include <vector>
#include <random>
#include "RBTree.h"
#include <set>
#include <iomanip>
#include <fstream>

//include tree headers

using std::vector;

double get_time() {
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()/1e6;
}

int32_t rand_num(int min, int max) {
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    static std::default_random_engine e(seed);
    std::uniform_int_distribution<int> d(min, max);
    return d(e);
}

template<typename CurrTree>
class Profiler {
private:
    vector<double> times_insert;
    vector<double> times_find;
    vector<double> times_erase;

    vector<int32_t> tree_sizes;

    CurrTree test_tree;

public:
    Profiler() {
        initialize_sizes();
    }

    void initialize_sizes() {
        int32_t n = 1;
        while (n < 100) {
            tree_sizes.push_back(n);
            n += 10;
        }
        while (n < 3000) {
            tree_sizes.push_back(n);
            n += 100;
        }
        while (n < 30000) {
            tree_sizes.push_back(n);
            n += 300;
        }
    }

    void test_insert() {
       for (int i_sz = 0; i_sz < tree_sizes.size(); i_sz++) {
           while (test_tree.size() < tree_sizes[i_sz]) {
               std::cout << "Choosing random number..." << '\n';
               std::cout << "-- Seeking tree_size = " << tree_sizes[i_sz] << '\n';
               std::cout << "---- Before inserting test_tree size = " << test_tree.size() << '\n';
               test_tree.insert(rand_num(-100000, 100000));
               std::cout << "---- After inserting test_tree size = " << test_tree.size() << '\n';
               std::cout << " Chose a random number." << '\n';
           }
           std::cout << "Working on element " << tree_sizes[i_sz] << " out of " << tree_sizes[tree_sizes.size()-1] << '\n';
           test_insert_local();
       }
    }
    void test_erase() {
        return;
    }
    void test_find() {
        return;
    }

    void test_insert_local() {
        double avg_time_per_size = 0;
        for (int i = 0; i < 100; i++) {
            double avg_time_per_num = 0;
            int32_t curr_num = rand_num(-100000, 100000);
            std::cout << "---- Chose number " << curr_num << ". Starting averaging..." << '\n';

            for (int j = 0; j < 300; j++) {
                double time_start = get_time();
                test_tree.insert(curr_num);
                double time_finish = get_time();

                avg_time_per_num += time_finish - time_start;
                test_tree.erase(curr_num);
            }
            avg_time_per_num = double( (double) avg_time_per_num / 300);
            avg_time_per_size += avg_time_per_num;
            std::cout << "---- Finished averaging" << '\n';
        }
        avg_time_per_size = double( (double) avg_time_per_size / 100);
        times_insert.push_back(avg_time_per_size);
    }

    void print_insert_table() {
        std::cout << "-- Started making a CSV... ";
        std::ofstream f;
        f.open("output_data_2.csv");
        for (int i = 0; i < tree_sizes.size(); i++) {
            f << tree_sizes[i] << ",";
            f << std::setprecision(3) << times_insert[i] << '\n';
        }
        std::cout << "finished CSV" << '\n';
    }
};

int main() {
    Profiler<std::set<int32_t>> prof;
    prof.test_insert();
    prof.print_insert_table();
    return 0;
}

