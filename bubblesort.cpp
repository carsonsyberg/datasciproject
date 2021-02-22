#include "bubblesort.hpp"
#include <iostream>
#include <string>

using namespace std;

/*
 * Purpose: Constructer for empty bubble sort array
 * @param none
 * @return none
 */
BubbleSort::BubbleSort() {
    
    listSize = 0; // just need to initialize listSize to 0
    // vector list empty
}

void BubbleSort::insert(int key) {
    
    list.push_back(key); // puts the key into the vectir
    listSize++; // increases size of list

}

void BubbleSort::display() {

    cout << "Displaying List" << endl;

    // loop through whole list and display each item
    for(int i = 0; i < listSize; i++) {
        cout << list[i] << " ";
    }

    cout << endl;
}

int BubbleSort::search(int key) {

    // loop through whole list and search for item
    for(int i = 0; i < listSize; i++) {
        if(list[i] == key)
            return i;
    }

    return -1; // returns -1 if never found a match
}

void BubbleSort::sort() {

    // swap items if left one greater than right one, do for each item
    // repeat until no swaps occur

    int numSwaps = 1;
    while(numSwaps != 0) {

        numSwaps = 0; // if any sorting occurs, this number will not be 0 by the end of the iteration

        // loop through whole list and swap if necessary
        for(int i = 0; i < listSize; i++) {
            // if left greater than right, need to swap them
            // ensures does not compare last element to anything
            if(i != listSize - 1 && list[i] > list[i + 1]) {
                int holder = list[i]; 
                list[i] = list[i+1]; // puts smaller value to the left
                list[i+1] = holder; // and larger value to the right
                numSwaps++; // increment numSwaps
            }
        }

    }

}

