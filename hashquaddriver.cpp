#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <time.h>
#include "hashquad.hpp"

using namespace std;

int main(int argc, char const *argv[]) {

    // ensures correct number of command line arguments
    if(argc != 3) {
        cout << "Incorrect number of arguments." << endl;
        return -1;
    }

    HashTable hashBrown = HashTable(40009);

    // create an int array of length 10,000 to hold the 10,000 elements from the data file
    int testData[10000];

    // also declare 2 float arrays of length 100 to record the time measurements
    float insertTime[100];
    float searchTime[100];
    int insertCollisions[100];
    int searchCollisions[100];

    // read in the entire test data into the array of integers
    // file to read
    ifstream in_file;

    // opening file + failsafe
    in_file.open(argv[1]);
    if(in_file.fail()) {
        cout << "Failed to open the file." << endl;
        return -1;
    }

    // holder for newValue from file + numberOfElements
    string line, holder;

    // reads through whole file, adding value to array and printing whole array each time around
    int index = 0;
    while(getline(in_file, line)) {

        stringstream s(line);

        // runs until end of line
        while(getline(s, holder, ',')) {
            testData[index] = stoi(holder); // take the file info, turn into an int, and put it into the array
            index++;
        }
    }

    // setting up random stuff
    srand (time(NULL)); // initializes the random seed

    cout << "Experiment Starting..." << endl;

    // inserting 10,000 elements, 200 at a time -> 10,000 / 200 = 50 times
    int insertIndexStart = 0;
    int insertIndexEnd = 99;
    for(int i = 0; i < 100; i++) {
            // cout << "Experiment Loop (" << i << ")" << endl;
        // Step 2. Insert: measure the total amount of time it takes to insert the first 100 records, 
        // divide total time by 100 to get avg insert time, record avg in insert[0]
        
        // on first iteration goes 0 - 99

        auto start = chrono::steady_clock::now(); // gets current time
        for(int j = insertIndexStart; j <= insertIndexEnd; j++) // adding 100 elements to array first loop 0-99 then 100-199 then 200-299 etc...
            hashBrown.insert(testData[j]);
        auto end = chrono::steady_clock::now(); // gets current time

        insertTime[i] =         searchTime[i] = chrono::duration<float, std::micro>(end-start).count() / 100; // calculates avg time passed and puts into array
            //cout << "insertTime [" << i << "]: " << insertTime[i] << endl; 

        insertCollisions[i] = hashBrown.getNumOfCollision(); // inserts number of collisions that happened during insertion
        hashBrown.setNumOfCollision(0);  // resets num of collisions so we can see how many caused by search

        // Step 3. Search: generate a set of 100 pseudo-random numbers in interval [0, 99]. Use these values
        // as indices into your test data array. 
        int randIndex[100];
        for(int j = 0; j < 100; j++) {
            randIndex[j] = rand() % insertIndexEnd + 0; // generates random num between (0) and insertIndexEnd (99)
        }
        
        start = chrono::steady_clock::now(); // gets current time
        // always searching for only 100 items
        for(int j = 0; j < 100; j++) 
            hashBrown.searchItem(testData[randIndex[j]]); // starts by searching for value at 1st random generated index, then next and so on
        end = chrono::steady_clock::now(); // gets current time

        searchTime[i] = chrono::duration<float, std::micro>(end-start).count() / 100; // calculates avg time passed and puts into array
            //cout << "searchTime [" << i << "]: " << searchTime[i] << endl; 

        // Search structure for each of the 100 elements
        // measure the total time it takes to perform the 100 searches. Divide total time by 100 for avg. Record avg in search[0]
        
        // updating indexes for data to input
        insertIndexStart += 100;
        insertIndexEnd += 100;

        searchCollisions[i] = hashBrown.getNumOfCollision(); // inserts number of collisions that happened during search
        hashBrown.setNumOfCollision(0);  // resets num of collisions so we can see how many caused by next insertion

    }
    // continue repeating until end of data file


    // record this data to external file for plotting later on
    // preparing file for writing to
    ofstream outputFile;
    outputFile.open(argv[2]);
    // ensures valid file for writing
    if(outputFile.fail()) {
        cout << "Failed to open the file for writing." << endl;
        return -1;
    }

    // adds time data to external files (1st col insertTime, 2nd col searchTime, 3rd col insertCollisions)
    for(int i = 0; i < 100; i++) {
            outputFile << insertTime[i] << "," << searchTime[i] << "," << insertCollisions[i] << "," << searchCollisions[i] << endl;
    }

    // done writing to file
    outputFile.close();

    cout << "Program complete" << endl;

    return 0;
    
}