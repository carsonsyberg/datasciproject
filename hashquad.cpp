#include "hashquad.hpp"
#include <iostream>
#include <string>
using namespace std;

/*
 * Purpose: Constructer for empty hash table
 * @param none
 * @return none
 */
HashTable::HashTable(int bsize) {
    // to construct the table, just need an array of size bsize
    tableSize = bsize; 
    table = new int[tableSize];
}

/*
 * Purpose: Insert nodes to dll
 * @param int key
 * @return none
 */
bool HashTable::insert(int key) {
    // to insert, need to do hashFunction(key) to get index to put it at
    // then check if that index is empty, if not do quadratic probing til an empty one is found
    // wrap around to the front of the array if need be

    // first ensure an open spot exists
    bool foundOpen = false;
    for(int i = 0; i < tableSize; i++) {
        if(table[i] == 0) {
            foundOpen = true;
            break;
        }
    }

    // means no open spot so could not insert new item
    if(!foundOpen)
        return false;

    unsigned int index = hashFunction(key);
    // for now, empty array spots are 0

    // means array spot was empty, so we can put the value in and be done
    if(table[index] == 0) {
        table[index] = key;
        return true;
    }
    
    // else, need to quadratically probe until an open index is found
    numOfcolision = numOfcolision + 1;

    unsigned int quadIndex = index;
    int count = 1;
    while(table[quadIndex] != 0) {


        if(index + count*count < tableSize) // only do it regular if the new index won't be outside the bounds
            quadIndex = index + count*count; // new index is original + 1^2, original + 2^2, original + 3^2, ...
        else
            quadIndex = (index + count*count) % tableSize; // places it back around the front if index + count*count too large
        
        count = count + 1; // count increment does not change with wrap around
    }

    // upon breaking out of loop, table[quadIndex] == 0, and we can now insert our item
    table[quadIndex] = key;

    return true;
}

/*
 * Purpose: search for node with key value
 * @param int key
 * @return Node* nodeWithKey
 */
unsigned int HashTable::hashFunction(int key) {
    // only need to implement the modulo here
    return key % tableSize;
}

/*
 * Purpose: display entire hash table
 * @param none
 * @return none
 */
void HashTable::printTable() {

    cout << "Printing Table: ";

    // only print nonzero spots, since 0 represents empty spot
    for(int i = 0; i < tableSize; i++) {
        //if(table[i] != 0)
            cout << table[i] << " ";
    }

    cout << endl;
}

/*
 * Purpose: get number of collisions
 * @param none
 * @return number of collisions
 */
int HashTable::getNumOfCollision() {
    return numOfcolision;
}

/*
 * Purpose: set number of collisions
 * @param int number of collisions
 * @return none
 */
void HashTable::setNumOfCollision(int num) {
    numOfcolision = num;
}


/*
 * Purpose: get index of item
 * @param none
 * @return index that key is located at or -1 if no key found
 */
int HashTable::searchItem(int key) {
    // to search, need to do hashFunction(key) to get index to find it at
    // then check if that indexes' key matches, if not do quadratic probing til a match is found
    // wrap around to the front of the array if need be

    unsigned int index = hashFunction(key);
    // for now, empty array spots are 0

    // means array spot was empty, so our key is not in it
    if(table[index] == 0) {
        return -1;
    }

    // means found it without collision
    if(table[index] == key) {
        return index;
    }
    
    // else, need to quadratically probe until an match is found
    numOfcolision = numOfcolision + 1; // because there was a collision
    
    unsigned int quadIndex = index;
    int count = 1;
    while(table[quadIndex] != key) {
        
        // if we reach an empty array spot, then our key is not in this table
        if(table[quadIndex] == 0)
            return -1; 

        if(index + count*count < tableSize) // only do it regular if the new index won't be outside the bounds
            quadIndex = index + count*count; // new index is original + 1^2, original + 2^2, original + 3^2, ...
        else
            quadIndex = (index + count*count) % tableSize; // places it back around the front if index + count*count too large
        
        count = count + 1; // count increment does not change with wrap around
    }

    // upon breaking out of loop, table[quadIndex] == key, and we can now return our item
    return quadIndex;
}
