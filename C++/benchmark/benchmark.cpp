#include <chrono>
#include <random>
#include <vector>
#include <array>
#include <algorithm>

#include "../include/bst.hpp"
#include "../src/bst.cpp"
#include "../include/iterator.hpp"

#define FACTOR 10
#define TREE_NUMBERS 4
#define TEST_ITERATIONS 100
std::random_device rd;

void populate_tree(bst<int, int> &tree, std::size_t size);
unsigned long long clear_test(bst<int, int> &tree, std::size_t size);
unsigned long long balance_test(bst<int, int> &tree, std::size_t size);

int main()
{
    std::array<bst<int, int>, TREE_NUMBERS> trees{};

    for (std::size_t i{}, j{10}; i < trees.size(); ++i, j *= FACTOR)
    {
        std::cout << "Tree with " << j << " nodes was balanced in ";
        std::cout << balance_test(trees.at(i), j) << " microseconds \n";
    }

    std::cout << "\n";

    for (std::size_t i{}, j{10}; i < trees.size(); ++i, j *= FACTOR)
    {
        std::cout << "Tree with " << j << " nodes was cleaned in ";
        std::cout << clear_test(trees.at(i), j) << " microseconds \n";
    }

    std::cout << std::endl;
}

unsigned long long clear_test(bst<int, int> &tree, std::size_t size)
{
    long counter{};
    for (std::size_t i{}; i < TEST_ITERATIONS; ++i)
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
    long counter{};
    for (std::size_t i{}; i < TEST_ITERATIONS; ++i)
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

    for (std::size_t i{}; i < size; ++i)
    {
        values.push_back({i, i});
    }

    std::shuffle(values.begin(), values.end(), rd);

    for (auto &value : values)
    {
        tree.insert(value);
    }
}