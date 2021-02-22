#ifndef DLL_H
#define DLL_H
using namespace std;


struct Node{

    int key;
    Node* next;
    Node* prev;
};

class DLL
{
    public:
        DLL();
        void insert(int key);
        Node* search(int key);
        void display();
    private:
        Node* head; 
};

#endif // DLL_H
