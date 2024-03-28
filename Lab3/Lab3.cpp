#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = nullptr;
    }
};

class List {
private:
    Node* tail;
    Node* currentNode;
    int size;
    int currentIndex;

    Node* getNode(int index) {
        if (index < 0) return nullptr;

        else if (index >= size) {
            index %= size;
        }

        if (index < currentIndex) {
            currentIndex = 0;
            currentNode = nullptr;
        }
        if (currentNode == nullptr) {
            currentNode = tail->next;
        }

        for (; currentIndex < index; currentIndex++) {
            currentNode = currentNode->next;
        }
        return currentNode;
    }

public:

    List() {
        tail = currentNode = nullptr;
        size = currentIndex = 0;
    }

    ~List() {
        clear();
    }

    void add(int value) {
        Node* newNode = new Node(value);
        if (tail == nullptr) {
            tail = newNode;
            tail->next = newNode;
        }
        else {
            newNode->next = tail->next;
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    void insert(int index, int value) {
        if (index < 0) {
            return;
        } 
        else if (index == size) {
            add(value);
            return;
        }
        Node* newNode = new Node(value);
        if (index == 0) {
            newNode->next = tail->next;
            tail->next = newNode;
        }
        else {
            Node* prev = getNode(index - 1);
            newNode->next = prev->next; 
            prev->next = newNode;
        }
        size++;
    }
    
    void removeAt(int index) {
        if (index < 0) {
            return;
        }

        if (size == 1) {
            delete tail;
            tail = nullptr;
            size = 0;
            return;
        }

        Node* temp = nullptr;

        if (index == 0) {
            temp = tail->next;
            tail->next = temp->next;
            delete temp;
            size--;
            return;
        }

        Node* prev = getNode(index - 1);
        temp = prev->next;
        prev->next = temp->next;
        if (temp == tail) {
            tail = prev;
        }
        delete temp;
        size--;
    }

    int elementAt(int index) {
        Node* node = getNode(index);
        if (node == nullptr) {
            return -1;
        }
        return node->data;
    }

    int count() {
        return size;
    }

    void insertBeforeNegative() {
        if (tail == nullptr) return;
        Node* curr = tail->next;
        for (int i = 0; i < size; i++) {
            if (curr->data < 0) {
                insert(i, 1);
            }
            curr = curr->next;
        }
    }

    void removeNegative() {
        if (tail == nullptr) return;

        Node* current = tail->next;
        Node* prev = tail;
        Node* temp = nullptr;

        while (current != tail) {
            if (current->data < 0) {
                prev->next = current->next;
                temp = current;
                current = current->next;
                delete temp;
                size--;
            }
            else {
                prev = current;
                current = current->next;
            }
        }

        if (tail->data < 0) {
            temp = tail;
            if (tail == tail->next) {
                tail = nullptr;
                currentNode = nullptr;
            }
            else {
                tail = prev;
                tail->next = temp->next;
            }
            delete temp;
            size--;
        }

        currentNode = nullptr;
        currentIndex = 0;
    }

    int count(int value) {
        if (tail == nullptr) return 0;
        Node* curr = tail->next;
        int k = 0;
        for (int i = 0; i < size; i++) {
            if (curr->data == value) {
                k++;
            }
            curr = curr->next;
        }
        return k;
    }

    void clear() {
        if (tail == nullptr) return;
        Node* curr = tail->next;
        Node* temp = nullptr;
        for (int i = 0; i < size; i++) {
            temp = curr;
            curr = curr->next;
            delete temp;
        }
        tail = nullptr;
        size = 0;
        currentNode = nullptr;
        currentIndex = 0;
    }
};


int main()
{

    List list;

    string choice;
    int data;
    int index;
    while (true) {
        cin >> choice;
        if (choice == "add") {
            cin >> data;
            list.add(data);
        }
        else if (choice == "insert") {
            cin >> data;
            cin >> index;
            list.insert(index, data);
        }
        else if (choice == "removeAt") {
            cin >> index;
            list.removeAt(index);
        }
        else if (choice == "count") {
            list.count();
        }
        else if (choice == "insertBeforeNegative") {
            list.insertBeforeNegative();
        }
        else if (choice == "removeNegative") {
            list.removeNegative();
        }
        else if (choice == "countData") { 
            cin >> data; 
            cout << list.count(data) << endl;
        }
        else if (choice == "clear") {
            list.clear();
        }
        else if (choice == "stop") {
            break;
        }
        else {
            break;
        }
    }
}
