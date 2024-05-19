#pragma once
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

    void fillArrayHelper(Node* node, int*& array, int& index) {
        if (node == nullptr) return;
        fillArrayHelper(node->left, array, index);
        array[index++] = node->data;
        fillArrayHelper(node->right, array, index);
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

    void removeHelper(Node*& node, int value) {
        if (!node) return;  // ���� �� ������

        if (value < node->data) {
            removeHelper(node->left, value);
        }
        else if (value > node->data) {
            removeHelper(node->right, value);
        }
        else {  // ������ ����, ������� ����� �������
            if (!node->left && !node->right) {  // ���� �������� ������
                delete node;
                node = nullptr;
                size--;
            }
            else if (node->left && !node->right) {  // ���� ����� ������ ������ �������
                Node* temp = node;
                node = node->left;
                delete temp;
                size--;
            }
            else if (!node->left && node->right) {  // ���� ����� ������ ������� �������
                Node* temp = node;
                node = node->right;
                delete temp;
                size--;
            }
            else {  // ���� ����� ���� �����
                Node* minNode = node->right;
                Node* parentOfMinNode = node;
                if (!minNode->left) {  // ����������� ���� ��������� ��������������� ������
                    node->data = minNode->data;
                    node->right = minNode->right;  // �������� ������ ��������� ������������ ���� � �������� ����
                    delete minNode;
                }
                else {
                    while (minNode->left) {  // ������� ����������� ���� � ������ ���������
                        parentOfMinNode = minNode;
                        minNode = minNode->left;
                    }
                    node->data = minNode->data;  // �������� ������ ���� �� ����������� �� ������� ���������
                    removeHelper(parentOfMinNode->left, minNode->data);  // ������� ����������� ����
                }
            }
        }
    }


    void remove(int value) {
        removeHelper(root, value);
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

    void fillArray(int* array, int& index) {
        fillArrayHelper(root, array, index);
    }
};