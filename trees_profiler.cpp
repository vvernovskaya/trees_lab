#include <iostream>
#include <chrono>
#include <vector>
#include <random>
#include "RBTree.h"
#include <set>
#include <string>
#include <iomanip>
#include <fstream>

const int NUM_NUM = 2000;
const int NUM_TEST_ONE = 5000;
const int RAND_RANGE = 1000000;

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

    void call_test() {
       for (int i_sz = 0; i_sz < tree_sizes.size(); i_sz++) {
           while (test_tree.size() < tree_sizes[i_sz]) {
               std::cout << "Choosing random number..." << '\n';
               std::cout << "-- Seeking tree_size = " << tree_sizes[i_sz] << '\n';
               std::cout << "---- Before inserting test_tree size = " << test_tree.size() << '\n';
               test_tree.insert(rand_num(-RAND_RANGE, RAND_RANGE));
               std::cout << "---- After inserting test_tree size = " << test_tree.size() << '\n';
               std::cout << "Chose a random number." << '\n';
           }
           std::cout << "Working on element " << tree_sizes[i_sz] << " out of " << tree_sizes[tree_sizes.size()-1] << '\n';
           test_local();
       }
    }

    void test_local() {
        double avg_time_per_size_insert = 0;
        double avg_time_per_size_find = 0;
        double avg_time_per_size_erase = 0;

        for (int i = 0; i < NUM_NUM; i++) {
            double avg_time_per_num_insert = 0;
            double avg_time_per_num_find = 0;
            double avg_time_per_num_erase = 0;

            int32_t curr_num = rand_num(-RAND_RANGE, RAND_RANGE);
            std::cout << "---- Chose number " << curr_num << ". Starting averaging..." << '\n';

            for (int k = 0; k < NUM_TEST_ONE; k++) {
                double time_start_find = get_time();
                bool find = (test_tree.find(curr_num) == test_tree.end());
                double time_finish_find = get_time();

                avg_time_per_num_find += time_finish_find - time_start_find;
            }
            avg_time_per_num_find = double( (double) avg_time_per_num_find / NUM_TEST_ONE);

            for (int j = 0; j < NUM_TEST_ONE; j++) {
                double time_start_insert = get_time();
                test_tree.insert(curr_num);
                double time_finish_insert = get_time();
                avg_time_per_num_insert += time_finish_insert - time_start_insert;

                double time_start_erase = get_time();
                test_tree.erase(curr_num);
                double time_finish_erase = get_time();
                avg_time_per_num_erase += time_finish_erase - time_start_erase;
            }

            avg_time_per_num_insert = double( (double) avg_time_per_num_insert / NUM_TEST_ONE);
            avg_time_per_num_erase = double( (double) avg_time_per_num_erase / NUM_TEST_ONE);

            avg_time_per_size_insert += avg_time_per_num_insert;
            avg_time_per_size_erase += avg_time_per_num_erase;

            std::cout << "---- Finished averaging" << '\n';
        }
        avg_time_per_size_insert = double( (double) avg_time_per_size_insert / NUM_NUM);
        avg_time_per_size_find = double( (double) avg_time_per_size_find / NUM_NUM);
        avg_time_per_size_erase = double( (double) avg_time_per_size_erase / NUM_NUM);

        times_insert.push_back(avg_time_per_size_insert);
        times_find.push_back(avg_time_per_size_find);
        times_erase.push_back(avg_time_per_size_erase);
    }

    void make_table(vector<double> times, std::string file_name) {
        std::cout << "-- Started making a CSV... ";
        std::ofstream f;
        f.open(file_name);
        for (int i = 0; i < tree_sizes.size(); i++) {
            f << tree_sizes[i] << ",";
            f << std::setprecision(6) << times[i] << '\n';
        }
        std::cout << "finished CSV" << '\n';
    }

    void test_insert() {
        call_test();
        make_table(times_insert, "output_times_insert.csv");
    }

    void test_find() {
        call_test();
        make_table(times_find, "output_times_find.csv");
    }

    void test_erase() {
        call_test();
        make_table(times_erase, "output_times_erase.csv");
    }

    void test_all() {
        call_test();
        make_table(times_insert, "output_times_insert.csv");
        make_table(times_find, "output_times_find.csv");
        make_table(times_erase, "output_times_erase.csv");
    }
};

int main() {
    Profiler<std::set<int32_t>> prof;
    prof.test_all();
    return 0;
}

