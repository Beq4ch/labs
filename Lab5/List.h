#pragma once
#include <string>
#include <iostream>
#include <windows.h>
#include <stdexcept>

template <typename T>
class List {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(T value) {
            data = value;
            prev = next = nullptr;
        }
    };

    Node* head;
    Node* tail;
    int size;
    Node* currentNode;
    int currentIndex;

    Node* getNode(int index) {
        // Оптимизация: если запрашиваемый индекс близок к последнему 
        // использованному, идём от currentNode
        if (currentNode != nullptr && abs(index - currentIndex) < size / 2) {
            Node* current = currentNode;
            if (index > currentIndex) {
                for (int i = currentIndex; i < index; i++) {
                    current = current->next;
                }
            }
            else {
                for (int i = currentIndex; i > index; i--) {
                    current = current->prev;
                }
            }
            currentNode = current;
            currentIndex = index;
            return current;
        }

        // В остальных случаях идём от начала или конца списка
        Node* current;
        if (index < size / 2) {
            current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
        }
        else {
            current = tail;
            for (int i = size - 1; i > index; i--) {
                current = current->prev;
            }
        }
        currentNode = current;
        currentIndex = index;
        return current;
    }

public:
    List() {
        head = tail = currentNode = nullptr;
        size = currentIndex = 0;
    }

    ~List() {
        clear();
    }

    void add(T data) {
        Node* newNode = new Node(data);
        if (head == nullptr) {
            head = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
        }
        tail = newNode;
        size++;
    }

    void insert(int index, T data) {
        if (index < 0 || index > size) {
            return;
        }

        if (index == size) {
            add(data);
            return;
        }

        Node* newNode = new Node(data);
        if (index == 0) {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        else {
            Node* curr = getNode(index);
            newNode->prev = curr->prev;
            newNode->next = curr;
            curr->prev = newNode;
            newNode->prev->next = newNode;
        }
        currentNode = newNode;
        currentIndex = index;
        size++;
    }

    void removeAt(int index) {
        if (index < 0 || index >= size) {
            return;
        }

        Node* temp = nullptr;
        if (index == 0) {
            temp = head;
            head = head->next;
            if (head) {
                head->prev = nullptr;
            }
            else {
                tail = nullptr;
            }
        }
        else if (index == size - 1) {
            temp = tail;
            tail = tail->prev;
            tail->next = nullptr;
        }
        else {
            temp = getNode(index);
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }

        if (temp == currentNode) {
            currentNode = temp->prev;
            currentIndex = max(0, index - 1);
        }
        else if (index < currentIndex) {
            currentIndex--;
        }

        delete temp;
        size--;
        if (size == 0) {
            head = tail = currentNode = nullptr;
            currentIndex = 0;
        }
    }

    T elementAt(int index) {
        if (index < 0 || index >= size) {
            throw ("");
        }

        if (index == currentIndex && currentNode != nullptr) {
            return currentNode->data;
        }

        return getNode(index)->data;
    }

    int count() {
        return size;
    }

    void clear() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
        size = 0;
    }
};