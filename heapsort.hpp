#ifndef HEAPSORT_HPP
#define HEAPSORT_HPP

#include<vector>

using namespace std;

class HeapSort
{
    int heapSize;  // No. of elements

    // pointer to array to hold heap
    int *heap;

public:
    HeapSort(int hSize);  // Constructor

    // inserts into heap
    void insert(int key);

    // displays current items in heap
    void display();

    // returns index of item with given key
    int search(int key);

    // fixes the heap
    void heapify(int index);
};

#endif