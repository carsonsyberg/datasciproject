#ifndef BUBBLESORT_HPP
#define BUBBLESORT_HPP

#include<vector>

using namespace std;

class BubbleSort
{
    int listSize;  // No. of elements

    // vector list to hold elements
    vector<int> list;

public:
    BubbleSort();  // Constructor

    // inserts into vector
    void insert(int key);

    // displays current items in vector
    void display();

    // returns index of item with given key
    int search(int key);

    // sorts the list with bubble sort algorithm
    void sort();
};

#endif