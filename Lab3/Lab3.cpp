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
    Node* lastAccessNode;
    int lastAccessIndex;
    int size;

    Node* getNode(int index) {
        if (index >= size) index %= size;
        if (lastAccessNode != nullptr && lastAccessIndex <= index) {
            for (int i = lastAccessIndex; i < index; ++i) {
                lastAccessNode = lastAccessNode->next;
            }
            lastAccessIndex = index;
            return lastAccessNode;
        }
        else {
            Node* current = tail;
            for (int i = 0; i <= index; ++i) {
                current = current->next;
            }
            lastAccessNode = current;
            lastAccessIndex = index;
            return current;
        }
    }

public:
    List() {
        tail = lastAccessNode = nullptr;
        size = lastAccessIndex = 0;
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
        if (size == 0) {
            add(value);
            return;
        }

        Node* newNode = new Node(value);

        if (index == 0) {
            newNode->next = tail->next;
            tail->next = newNode;
        }
        else {
            Node* prevNode = getNode(index - 1);
            newNode->next = prevNode->next;
            prevNode->next = newNode;
            if (prevNode == tail) {
                tail = newNode;
            }
        }

        size++;
    }

    void removeAt(int index) {
        if (size == 0) return;

        if (index == 0) {
            Node* toDelete = tail->next;
            if (size == 1) {
                tail = nullptr;
            }
            else {
                tail->next = toDelete->next;
            }
            delete toDelete;
        }
        else {
            Node* prevNode = getNode(index - 1);
            Node* toDelete = prevNode->next;
            prevNode->next = toDelete->next;
            if (toDelete == tail) {
                tail = prevNode;
            }
            delete toDelete;
        }
        size--;
    }


    void insertBeforeNegative() {
        if (size == 0) return;

        Node* current = (lastAccessNode != nullptr && lastAccessNode->data < 0) ? lastAccessNode : tail->next;
        Node* prev = tail;
        int currentIndex = (lastAccessNode != nullptr && lastAccessNode->data < 0) ? lastAccessIndex : 0;

        do {
            if (current->data < 0) {
                Node* newNode = new Node(1);
                newNode->next = current;
                prev->next = newNode;
                if (current == tail->next) {
                    tail->next = newNode;
                }
                size++;
                lastAccessNode = newNode;
                lastAccessIndex = currentIndex;
            }
            prev = current;
            current = current->next;
            currentIndex++;
        } while (current != tail->next);
    }

    void removeNegative() {
        if (size == 0) return;

        Node* current = (lastAccessNode != nullptr) ? lastAccessNode : tail->next;
        Node* prev = (lastAccessNode != nullptr) ? getNode(lastAccessIndex - 1) : tail;
        int currentIndex = (lastAccessNode != nullptr) ? lastAccessIndex : 0;

        do {
            if (current->data < 0) {
                Node* toDelete = current;
                prev->next = current->next;
                if (current == tail) {
                    tail = prev;
                }
                delete toDelete;
                current = prev->next;
                size--;
                if (size == 0) break;
            }
            else {
                prev = current;
                current = current->next;
            }
            currentIndex++;
            if (currentIndex >= size) currentIndex = 0;
        } while (current != tail);

        lastAccessNode = nullptr; // Сбрасываем, так как список изменился
        lastAccessIndex = 0;
    }


    int count(int value) {
        int count = 0;
        Node* current = tail;
        do {
            if (current->data == value) {
                count++;
            }
            current = current->next;
        } while (current != tail);
        return count;
    }

    int count() {
        return size;
    }

    int elementAt(int index) {
        if (size == 0) return 0;
        Node* current = getNode(index);
        return current->data;
    }

    void clear() {
        if (size == 0) return;

        Node* current = tail->next;
        while (current != tail) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        delete tail;
        tail = nullptr;
        lastAccessNode = nullptr;
        size = 0;
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

