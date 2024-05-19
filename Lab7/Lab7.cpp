#include <iostream>
using namespace std;

enum Order { Prefix, Infix, Postfix };

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

    void storeBSTNodes(Node* root, Node** nodes, int& index) {
        if (root == nullptr) return;
        storeBSTNodes(root->left, nodes, index);
        nodes[index++] = root;
        storeBSTNodes(root->right, nodes, index);
    }

    Node* buildTreeUtil(Node** nodes, int start, int end) {
        if (start > end) return nullptr;
        int mid = (start + end) / 2;
        Node* node = nodes[mid];
        node->left = buildTreeUtil(nodes, start, mid - 1);
        node->right = buildTreeUtil(nodes, mid + 1, end);
        return node;
    }

    Node* balanceBST(Node* root) {
        int nodeCount = countNodes(root);
        Node** nodes = new Node * [nodeCount];
        int index = 0;
        storeBSTNodes(root, nodes, index);
        Node* balancedRoot = buildTreeUtil(nodes, 0, nodeCount - 1);
        delete[] nodes;
        return balancedRoot;
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
        if (target && target->right) rotateLeft(target);
    }

    void ToRight(int value) {
        Node* target = findNode(root, value);
        if (target && target->left) rotateRight(target);
    }

    void Balance() {
        root = balanceBST(root);
    }

    int count() {
        return size;
    }

    void clear() {
        clearNode(root);
        root = nullptr;
        size = 0;
    }
};

int main() {
    Tree t;
    string choice;
    int data;

    while (true) {
        cin >> choice;
        if (choice == "add") {
            cin >> data;
            t.add(data);
        }
        else if (choice == "clear") {
            t.clear();
        }
        else if (choice == "count") {
            cout << t.count() << endl;
        }
        else if (choice == "toleft") {
            cin >> data;
            t.ToLeft(data);
        }
        else if (choice == "toright") {
            cin >> data;
            t.ToRight(data);
        }
        else if (choice == "balance") {
            t.Balance();
        }
        else if (choice == "toarray") {
            string order;
            cin >> order;
            int* array = nullptr;
            int size = t.count();
            if (order == "infix") {
                array = t.ToArray(Infix);
            } else if (order == "prefix") {
                array = t.ToArray(Prefix);
            } else if (order == "postfix") {
                array = t.ToArray(Postfix);
            }
            if (array != nullptr) {
                for (int i = 0; i < size; i++) {
                    cout << array[i] << " ";
                }
                cout << endl;
                delete[] array; // Clear memory
            }
        }
        else if (choice == "stop") {
            break;
        }
        else {
            break;
        }
    }

    return 0;
}
