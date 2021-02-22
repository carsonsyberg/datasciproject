#include "dll.hpp"
#include <iostream>
#include <string>
using namespace std;

/*
 * Purpose: Constructer for empty double linked list
 * @param none
 * @return none
 */
DLL::DLL() {
    head = NULL;
}

/*
 * Purpose: Insert nodes to dll
 * @param int key
 * @return none
 */
void DLL::insert(int key) {
    // no matter what happens, need a new node created
    Node* newNode = new Node;
    newNode->key = key;
    newNode->next = nullptr;

    // No head exists yet
    if(head == nullptr) {
        newNode->prev = nullptr; // if head then prev is null
        head = newNode;
        return; // return after adding node
    }
    
    // The head already exists, so need to go to end of list
    Node* curr = head;
    while(curr != nullptr) {
        // checks each item of list until it finds the last one
        if(curr->next == nullptr) {
            // newNode will be the new last node
            curr->next = newNode; // now newNode is last in list
            newNode->prev = curr; // update prev pointer too
            return; // return after adding node
        }

        curr = curr->next;
    }
}

/*
 * Purpose: search for node with key value
 * @param int key
 * @return Node* nodeWithKey
 */
Node* DLL::search(int key) {

    // need to iterate through whole list and return upon finding key value
    Node* curr = head;
    while(curr != nullptr) {
        if(curr->key == key)
            return curr; // if it finds it, immediately returns with pointer to node that had key value
        curr = curr->next;
    }

    // if it gets out here, never found the value in the list
    return nullptr;
}

/*
 * Purpose: display entire dll
 * @param none
 * @return none
 */
void DLL::display() {
    // need to iterate through whole list and print each value
    if(head != nullptr) {
        cout << "Displaying List: ";

        Node* curr = head;
        // loops through list and prints keys
        while(curr != nullptr) {
            cout << curr->key << " ";
            curr = curr->next;
        }
        cout << endl;
    }
    else {
        cout << "List empty." << endl;
    }
}
