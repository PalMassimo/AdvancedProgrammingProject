# Advanced Programming Project
This repository contains the final project for the [Advanced Programming](https://github.com/asartori86/advanced_programming_2020) course 2020-2021 at [University of Trieste](https://units.it).

The final project consists of two parts:
- a C++ project
- a Python script

---

## C++ Project
It is an implementation of a template binary search tree with each node having a key and a value.

<img src="https://miro.medium.com/max/875/1*S9O9sNJQkfwFbtaji9e25w.png" alt="binary search tree" height="200" length="200" style="margin-right: auto; margin-left: auto; display: block;"/>

It implements the following functions:

- **insert**: create a new node in the correct position, according on his key

- **emplace**: create a new element into the container constructed in-place with the given args if there is no element with the key in the container

- **begin**: returns an iterator to the node with the lowest key

- **end**: returns an iterator to the last past node

- **find**: returns an iterator pointing the searched node

- **balance**: balance the tree

- **erase**: delete a node from the tree

- **clear**: clear the tree content

- **subscripting operator**: returns the value associated with the given key

- **put-to operator**: print the tree keys in an ascending order  

---

## Python Script
A python algorithm that given a dictionary it computes the reversed one, as follows: 

`dictionary  = {"a": [1, 2, 3], "b": [45, 6], "c": [2, 45]}`

`reverse_dictionary = {1: ["a"], 2: ["a", "c"], 3: ["a"], 6: ["b"], 45:["b", "c"]}`