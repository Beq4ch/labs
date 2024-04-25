// Lab6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }

};

class Tree {
private:
    int size;
    Node* root;

    void printHelper(Node* node) {
        if (node != nullptr) {
            printHelper(node->left);
            cout << node->data << " ";
            printHelper(node->right);
        }
    }
public:

    Tree() {
        size = 0;
        root = nullptr;
    }

    ~Tree() {
        clear();
    }

    void add(int value) {
        Node* newNode = new Node(value);

        if (!root) {
            root = newNode;
            size++;
            return;
        }

        Node* curr = root;
        while (true) {
            if (value < curr->data) {
                if (!curr->left) {
                    curr->left = newNode;
                    size++;
                    break;
                }
                else {
                    curr = curr->left;
                }
            }
            else if (value > curr->data) {
                if (!curr->right) {
                    curr->right = newNode;
                    size++;
                    break;
                }
                else {
                    curr = curr->right;
                }
            }
            else {
                delete newNode;
                break;
            }
        }
    }

    bool contains(int value) {
        Node* curr = root;
        while (curr) {
            if (value < curr->data) {
                curr = curr->left;
            }
            else if (value > curr->data) {
                curr = curr->right;
            }
            else {
                return true;
            }
        }
        return false;
    }

    int count() {
        return size;
    }

    void clearNode(Node* node) {
        if (!node) return;
        clearNode(node->left);
        clearNode(node->right);
        delete node;
    }

    void clear() {
        clearNode(root);
        root = nullptr;
        size = 0;
    }

    void print() {
        printHelper(root);
        cout << endl;
    }
};

int main()
{
    Tree t;

    string choice;
    int data;

    while (true) {
        cin >> choice;
        if (choice == "add") {
            cin >> data;
            t.add(data);
        }
        else if (choice == "print") {
            t.print();
        }
        else if (choice == "clear") {
            t.clear();
        }
        else if (choice == "count") {
            t.count();
        }
        else if (choice == "stop") {
            break;
        }
        else {
            break;
        }
    }
}