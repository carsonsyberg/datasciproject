#include "heapsort.hpp"
#include <iostream>
#include <string>

using namespace std;

/*
 * Purpose: Constructer for empty heap sort array
 * @param int size of array
 * @return none
 */
HeapSort::HeapSort(int hSize) {
    
    heapSize = hSize; // initializes heap size
    heap = new int[heapSize]; // creates array for heap to point to

    for(int i = 0; i < heapSize; i++) {
        heap[i] = -1; // initializes all values to -1 to represent empty
    }
}

/*
 * Purpose: Insert item into heap array
 * @param int key
 * @return none
 */
void HeapSort::insert(int key) {
    
    // add to first empty slot
    int i = 0;
    while(heap[i] != -1) {
        i++;
    }

    heap[i] = key; // upon finding 1st empty spot, index i represents it
    // now need to heapify
    //heapify(i);
    // not heapifying because need to time sort after inserting 100...
}

/*
 * Purpose: Print all items in heap array
 * @param none
 * @return none
 */
void HeapSort::display() {

    cout << "Displaying Heap" << endl;

    // loop through whole list and display each item
    for(int i = 0; i < heapSize; i++) {
        cout << heap[i] << " ";
    }

    cout << endl;
}

/*
 * Purpose: Find the index of the array containing key
 * @param int key
 * @return int index with given key inside or -1 if no match found
 */
int HeapSort::search(int key) {

    // loop through whole heap and search for item
    for(int i = 0; i < heapSize; i++) {
        if(heap[i] == key)
            return i;
    }

    return -1; // returns -1 if never found a match
}

/*
 * Purpose: Ensures heap properties are maintained
 * @param int index
 * @return none
 */
void HeapSort::heapify(int index) {

    // check against its parent
        // for max heap, curr needs to be less than parent
        // for min heap, curr needs to be greater than parent
            // if not less or greater respectively, swap them and check again

    // max heap implemenetation
    int parentIndex = (index - 1) / 2;
    // continues to loop until our added element is less than its parent
    // or until our added element is the first element in the list
    while(index != 0 && heap[index] > heap[parentIndex]) {
        // if not broken out of loop, means curr element is greater than its parent
        // so need to swap them

        int holder = heap[parentIndex];
        heap[parentIndex] = heap[index];
        heap[index] = holder;

        // and update indexes accordingly
        holder = index;
        index = parentIndex;
        parentIndex = (holder - 1) / 2;
    }
    
}

