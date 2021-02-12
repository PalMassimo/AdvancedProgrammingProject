#include <chrono>
#include <random>
#include <vector>
#include <algorithm>

#include "../include/bst.hpp"
#include "../src/bst.cpp"
#include "../include/iterator.hpp"

#define MAX_NODES 100000
#define TEST_ITERATIONS 100
std::random_device rd;

void populate_tree(bst<int, int> &tree, std::size_t size);
unsigned long long clear_test(bst<int, int> &tree, std::size_t size);
unsigned long long balance_test(bst<int, int> &tree, std::size_t size);


int main()
{


    bst<int, int> tree10{};
    bst<int, int> tree100{};
    bst<int, int> tree1000{};
    bst<int, int> tree10000{};
    bst<int, int> tree100000{};
    bst<int, int> tree1000000{};
    
    std::cout << balance_test(tree10, 10) << std::endl;
    std::cout << balance_test(tree100, 100) << std::endl;
    std::cout << balance_test(tree1000, 1000) << std::endl;
    std::cout << balance_test(tree10000, 10000) << std::endl;
    std::cout << balance_test(tree100000, 100000) << std::endl;

    std::cout << clear_test(tree10, 10) << std::endl;
    std::cout << clear_test(tree100, 100) << std::endl;
    std::cout << clear_test(tree1000, 1000) << std::endl;
    std::cout << clear_test(tree10000, 10000) << std::endl;
    std::cout << clear_test(tree100000, 100000) << std::endl;

}

unsigned long long clear_test(bst<int, int> &tree, std::size_t size)
{
    auto counter = 0;
    for (std::size_t i = 0; i < TEST_ITERATIONS; ++i)
    {
        populate_tree(tree, size);
        auto t0 = std::chrono::high_resolution_clock::now();
        tree.clear();
        auto t1 = std::chrono::high_resolution_clock::now();
        counter += std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();
    }
    return counter / TEST_ITERATIONS;
}

unsigned long long balance_test(bst<int, int> &tree, std::size_t size)
{
    auto counter = 0;
    for (std::size_t i = 0; i < TEST_ITERATIONS; ++i)
    {
        populate_tree(tree, size);
        auto t0 = std::chrono::high_resolution_clock::now();
        tree.balance();
        auto t1 = std::chrono::high_resolution_clock::now();
        counter += std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();
    }
    return counter / TEST_ITERATIONS;
}

void populate_tree(bst<int, int> &tree, std::size_t size)
{
    std::vector<std::pair<int, int>> values{};

    for (std::size_t i = 0; i < size; ++i)
    {
        values.push_back({i, i});
    }

    std::shuffle(values.begin(), values.end(), rd);

    for (auto &value : values)
    {
        tree.insert(value);
    }
}