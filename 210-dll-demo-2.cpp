//Lab 22| COMSC 210 | Ismael Hadi
#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    // constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void push_back(int value) {
        Node* newNode = new Node(value);
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(int value) {
        Node* newNode = new Node(value);
        if (!head)  // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }

    void delete_val(int value) {
        if (!head) return; // Empty list

        Node* temp = head;
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; // Value not found

        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Deleting the head
        }

        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Deleting the tail
        }

        delete temp;
    }

    //this function takes a position as an input and deletes the node at that position. It includes several edge cases as is expected for deletion in a dll
    void delete_pos(int pos) {
        int index = 0;
        //empty list case
        if (!head) return;
        //1 element case
        if (pos == 0) {
            if (head->next == nullptr) {
                delete head;
                head = nullptr;
                tail = nullptr;
                return;
            }
            Node* successor = head->next;
            successor->prev = nullptr;
            delete head;
            head = successor;
            return;
        }
        Node* current = head;
        
        while (index != pos && current->next != nullptr) {
            current = current->next;
            index++;
        }
        //if index is out of range
        if (index != pos) {
            return;
        }
        if (current->next == nullptr) {
            Node* prede = tail->prev;
            prede->next = nullptr;
            delete tail;
            tail = prede;
            return;
        }
        Node* succ = current->next;
        Node* pred = current->prev;
        delete current;
        pred->next = succ;
        succ->prev = pred;
    }

    //this function deletes the head of the list
    void pop_front() {
        //empty list case
        if (!head) 
            return;
        //1 element list case
        if (!head->next) {
            delete head;
            head = nullptr;
            tail = nullptr;
            return;
        }
        Node* successor = head->next;
        successor->prev = nullptr;
        delete head;
        head = successor;
    }

    //this function deletes the tail of the list
    void pop_back() {
        //empty list case
        if (!head) 
            return;
        //one element list case
        if (!tail->prev) {
            delete tail;
            head = nullptr;
            tail = nullptr;
            return;
        }
        Node* prede = tail->prev;
        prede->next = nullptr;
        delete tail;
        tail = prede;
    }

    void print() {
        Node* current = head;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Driver program
int main() {
    srand(time(0));
    DoublyLinkedList list;
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;

    for (int i = 0; i < size; ++i)
        list.push_back(rand() % (MAX_NR-MIN_NR+1) + MIN_NR);

    cout << "List forward: ";
    list.print();

    cout << "Deleting head node: ";
    list.pop_front();
    list.print();

    cout << "Deleting tail node: ";
    list.pop_back();
    list.print();

    size -=2
    cout << "Deleting an element at a random position in the list";
    list.delete_pos(rand() % (MAX_LS-MIN_LS+1) + MIN_LS);
    
    cout << "List backward: ";
    list.print_reverse();

    cout << "Deleting list, then trying to print.\n";
    list.~DoublyLinkedList();
    cout << "List forward: ";
    list.print();

    return 0;
}
