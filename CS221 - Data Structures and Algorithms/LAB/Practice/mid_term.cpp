#include <iostream>
using namespace std;

class Node {
    public:
        int data;
        Node *next;


        Node(int value) {
            data = value;
            next = NULL;
        }
};

class LinkedListStack {
    public:
        Node *top;
        int stackSize;

        LinkedListStack() {
            top = NULL;
            stackSize = -1;
        }

        void push(int val) {
            
            
                Node *newNode = new Node(val); // Create a new node;
                newNode->next = top; // Link the newNode to the top node; such that the newNode contains the address to the top next in its next compartment.
                top = newNode;
                stackSize++;
            
        }   
        

        bool isEmpty() {
            return stackSize == -1;
        }

        int pop() {
            if (isEmpty()) {
                cout << "Stack is empty! Cannot pop anything!" << endl;
            }
            else {
                Node *temp = top;
                int poppedValue = top->data;
                top = top->next;
                delete temp;
                stackSize--;
                return poppedValue; 
            }
        }

        void peek() {
            cout << "Element at the top: " << top->data << endl;
        }

        void Display() {
            // Node *ptr = top;
            // for (Node *ptr; ptr != NULL; ptr = ptr->next) {
            //     cout << ptr->data << " ";
            // }
            Node *temp = top;
            while (temp != NULL) {
                cout << temp->data << " ";
                temp = temp->next;
            }
        }
};

int main() {

    LinkedListStack s1;
    if (s1.isEmpty()) {
        cout << "Stack is empty!" << endl;
    }

    s1.push(21);
    s1.push(98);
    s1.push(185);
    s1.push(16);


    s1.Display();

    cout << endl;

    int popped = s1.pop();
    cout << "Popped value: " << popped;

    cout << endl;
    
    s1.Display();

    return 0;
}