#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <time.h>
#include "bubblesort.hpp"

using namespace std;

int main(int argc, char const *argv[]) {

    // ensures correct number of command line arguments
    if(argc != 3) {
        cout << "Incorrect number of arguments." << endl;
        return -1;
    }

    // create an int array of length 10,000 to hold the 10,000 elements from the data file
    int testData[10000];

    // only measuring sortTime
    float sortTime[100];

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

    cout << "Experiment Starting..." << endl;

    // inserting 10,000 elements, 200 at a time -> 10,000 / 200 = 50 times
    int insertIndexStart = 0;
    int insertIndexEnd = 99;
    for(int i = 0; i < 100; i++) {
        
        // insert / copy 1st 100 elements of testData array to tempArray (the array is part of the class)
        BubbleSort toBeSorted;
        
        for(int i = 0; i <= insertIndexEnd; i++) {
            toBeSorted.insert(testData[i]);
        }
        
        auto start = chrono::steady_clock::now(); // gets current time
        for(int j = insertIndexStart; j <= insertIndexEnd; j++) // adding 100 elements to array first loop 0-99 then 100-199 then 200-299 etc...
            toBeSorted.sort();
        auto end = chrono::steady_clock::now(); // gets current time

        sortTime[i] = chrono::duration<float, std::micro>(end-start).count() / 100; // calculates avg time passed and puts into array
        
        // updating indexes for data to input
        insertIndexStart += 100;
        insertIndexEnd += 100;

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

    // adds time data to external files (1st col insertTime, 2nd col searchTime)
    for(int i = 0; i < 100; i++) {
            outputFile << sortTime[i] << endl;
    }

    // done writing to file
    outputFile.close();

    return 0;
}