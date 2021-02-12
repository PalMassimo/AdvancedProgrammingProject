# Advanced Programming Project

This repository contains the final project for the [Advanced Programming](https://github.com/asartori86/advanced_programming_2020) course 2020-2021 at [University of Trieste](https://units.it).

The final project consists of two parts:

- [a C++ project](#c-project)
     - [Overview](#overview)
     - [Functionalities](#functionalities)
     - [Benchmark](#benchmark)
- [a Python script](#python-script)

---

## C++ Project

### Overview

It is an implementation of a templated binary search tree, where each node has a key and a value.

<p align="center">
<img src="https://github.com/PalMassimo/AdvancedProgrammingProject/blob/main/Screenshots/Bst.png" alt="binary search tree"/>
</p>

To compile the project move to the `C++` folder and run `make` ,
which will create the executable files in the `src` and in `benchmark` folders. The first is the main project while the other is used to test the performance of the most relevant functionalities.

### Functionalities

It implements some functionalities that allow to search through and to modify its structure:

- **insert**

     Creates a new node in the correct position, according to his key. Starting from the root node it goes left or right depending if the target key is smaller or greater then the current node's key and then repeats the procedure until there are no further nodes. At that point it appends the new node and returns an iterator pointing to it and a boolean set to true. If the target key already exists it returns an iterator pointing to `nullptr` and false.

- **emplace**  
    Conceptually same as `insert` but it differs in the implementation. Instead of receiving a pair `{key, value}` it takes raw values.

- **begin**  
    Returns an iterator pointing to the node with the lowest key, which is the leftest node of the tree.

- **end**  
    Returns an iterator to the last past node, that is a `nullptr`.

- **find**   
    Given a key, it returns an iterator pointing to the searched node if exists, otherwise an iterator pointing to `nullptr`. To find the node it iterates through the tree.   

- **balance** 
     balance the tree

- **erase**  
     Given a key, it deletes a node from the tree. In order to maintain the bst structure it reshapes the tree, according to the position of the deleted node.

- **clear**  
     Iterating through the tree it calls `erase()` on every encountered node

- **subscripting operator**  
     Implements `find()` using the subscripting operator

- **put-to operator**  
     Iterating step by step through the tree it prints every key in an ascending order 

For some functions there are also the const version.

---

## Python Script

A python algorithm that given a dictionary it computes the reversed one, as follows:
<p align="center">
<img src="https://github.com/PalMassimo/AdvancedProgrammingProject/blob/main//Screenshots/Dictionary.png" alt="from dictionary to reversed"/>
</p>
  
  
First, to remove duplications, it puts the dictionary values in a set and then it construct the reverse dictionary by picking the keys from the set and for each one it finds the relative values by iterating in the original dictionary. 
