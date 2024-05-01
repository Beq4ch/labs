#include <iostream>
using namespace std;

enum Order { Prefix, Infix, Postfix, LevelsUpLeft, LevelsUpRight, LevelsDownLeft, LevelsDownRight };

class Tree {
private:
    struct Node {
        int data;
        Node* left;
        Node* right;
        Node(int value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root;
    int size;

    void clearNode(Node* node) {
        if (node != nullptr) {
            clearNode(node->left);
            clearNode(node->right);
            delete node;
        }
    }

    int countNodes(Node* node) const {
        if (node == nullptr) return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    void fillArray(Node* node, int*& array, int& index, Order order) {
        if (node == nullptr) return;
        if (order == Prefix) array[index++] = node->data;
        fillArray(node->left, array, index, order);
        if (order == Infix) array[index++] = node->data;
        fillArray(node->right, array, index, order);
        if (order == Postfix) array[index++] = node->data;
    }

    Node* findNode(Node* node, int value) {
        while (node != nullptr && node->data != value) {
            if (value < node->data) node = node->left;
            else node = node->right;
        }
        return node;
    }

    void rotateLeft(Node*& node) {
        Node* rightChild = node->right;
        node->right = rightChild->left;
        rightChild->left = node;
        node = rightChild;
    }

    void rotateRight(Node*& node) {
        Node* leftChild = node->left;
        node->left = leftChild->right;
        leftChild->right = node;
        node = leftChild;
    }

public:
    Tree() : root(nullptr), size(0) {}

    ~Tree() {
        clearNode(root);
    }

    void add(int value) {
        Node* newNode = new Node(value);
        if (!root) {
            root = newNode;
        }
        else {
            Node* current = root;
            Node* parent = nullptr;
            while (current) {
                parent = current;
                if (value < current->data) current = current->left;
                else if (value > current->data) current = current->right;
                else return; // No duplicate values
            }
            if (value < parent->data) parent->left = newNode;
            else parent->right = newNode;
        }
        size++;
    }

    int* ToArray(Order order) {
        int nodeCount = countNodes(root);
        int* array = new int[nodeCount];
        int index = 0;
        fillArray(root, array, index, order);
        return array;
    }

    int* ToArray() {
        return ToArray(Infix);
    }

    void ToLeft(int value) {
        Node* target = findNode(root, value);
        if (target && target->right) rotateLeft(target->right);
    }

    void ToRight(int value) {
        Node* target = findNode(root, value);
        if (target && target->left) rotateRight(target->left);
    }
};

int main() {
    Tree t;
    t.add(8);
    t.add(3);
    t.add(10);
    t.add(1);
    t.add(6);
    t.add(14);
    t.add(4);
    t.add(7);
    t.add(13);

    int* array = t.ToArray(Infix);
    cout << "Infix order: ";
    for (int i = 0; i < 9; i++) {
        cout << array[i] << " ";
    }
    cout << endl;

    delete[] array; // Clear memory

    t.ToLeft(3);
    t.ToRight(10);

    array = t.ToArray(Infix);
    cout << "After rotations: ";
    for (int i = 0; i < 9; i++) {
        cout << array[i] << " ";
    }
    cout << endl;

    delete[] array; // Clear memory

    return 0;
}
