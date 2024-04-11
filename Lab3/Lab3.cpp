// LabTest.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

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
        if (index < currentIndex) {
            currentIndex = 0;
            currentNode = nullptr;
        }
        if (currentNode == nullptr) {
            currentNode = tail->next;
        }

        while (currentIndex < index) {
            currentNode = currentNode->next;
            currentIndex++;
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
        currentIndex = 0;
        currentNode = nullptr;
    }

    void insert(int index, int value) {
        index %= size + 1;
        if (size == 0) { index = 0; }
        if (index == size) {
            add(value);
            return;
        }
        Node* newNode = new Node(value);
        if (index == 0) {
            if (size == 0) {
                tail = newNode;
                newNode->next = newNode;
            }
            else {
                newNode->next = tail->next;
                tail->next = newNode;
            }
        }
        else {
            Node* previous = getNode(index - 1);
            newNode->next = previous->next;
            previous->next = newNode;
            if (index == 0 && size != 0) {
                tail = newNode;
            }
        }
        size++;
        currentIndex = index;
        currentNode = newNode;
    }

    void removeAt(int index) {
        if (tail == nullptr) return;

        index = index % size;

        if (size == 1) {
            delete tail;
            currentNode = nullptr;
            currentIndex = 0;
            tail = nullptr;
            size = 0;
            return;
        }

        Node* temp = nullptr;

        if (index == 0) {
            temp = tail->next;
            if (currentNode == temp) {
                currentNode = temp->next;
                currentIndex++;
            }
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
        if (tail == nullptr) return -1;
        index = index % size;

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
        Node* prev = tail;
        int index = 0;

        do {
            if (curr->data < 0) {
                Node* newNode = new Node(1);
                if (curr == tail->next) {
                    newNode->next = tail->next;
                    tail->next = newNode;
                }
                else {
                    newNode->next = curr;
                    prev->next = newNode;
                }
                size++;
                if (index == currentIndex) {
                    currentNode = newNode;
                }
                else if (index < currentIndex) {
                    currentIndex++;
                }
            }
            prev = curr;
            curr = curr->next;
            index++;
        } while (curr != tail->next);
    }

    void removeNegative() {
        if (size == 0) return;

        Node* curr = tail->next;
        Node* prev = tail;
        int index = 0;

        while (curr != tail) {
            if (curr->data < 0) {
                if (curr == currentNode) {
                    currentNode = prev;
                    currentIndex = index - 1;
                }
                else if (index < currentIndex) {
                    currentIndex--;
                }
                prev->next = curr->next;
                delete curr;
                curr = prev->next;
                size--;
            }
            else {
                prev = curr;
                curr = curr->next;
            }
            index++;
        }

        if (tail->data < 0) {
            if (currentNode == tail) {
                currentNode = prev;
                currentIndex = index - 1;
            }
            prev->next = tail->next;
            delete tail;
            tail = prev;
            size--;
        }
        if (size == 0) {
            tail = nullptr;
            currentNode = nullptr;
            currentIndex = 0;
        }
    }

    int count(int value) {
        int k = 0;
        if (tail == nullptr) return k;
        Node* curr = tail->next;
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
            cin >> index;
            cin >> data;
            list.insert(index, data);
        }
        else if (choice == "removeAt") {
            cin >> index;
            list.removeAt(index);
        }
        else if (choice == "elementAt") {
            cin >> index;
            cout << list.elementAt(index) << endl;
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

