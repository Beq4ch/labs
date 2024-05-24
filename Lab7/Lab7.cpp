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

    Node* rotateLeft(Node* node) {
        Node* newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;
        return newRoot;
    }

    Node* rotateRight(Node* node) {
        Node* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;
        return newRoot;
    }

    Node* balanceHelper(Node* node) {
        if (!node) return nullptr;

        node->left = balanceHelper(node->left);
        node->right = balanceHelper(node->right);

        int leftDepth = depth(node->left);
        int rightDepth = depth(node->right);

        if (leftDepth > rightDepth + 1) {
            if (depth(node->left->left) < depth(node->left->right)) {
                node->left = rotateLeft(node->left);
            }
            node = rotateRight(node);
        }
        else if (rightDepth > leftDepth + 1) {
            if (depth(node->right->right) < depth(node->right->left)) {
                node->right = rotateRight(node->right);
            }
            node = rotateLeft(node);
        }

        return node;
    }

    int depth(Node* node) {
        if (!node) return 0;
        int leftDepth = depth(node->left);
        int rightDepth = depth(node->right);
        return max(leftDepth, rightDepth) + 1;
    }

    Node* findNode(Node* node, int value) {
        if (!node || node->data == value) return node;
        if (value < node->data) return findNode(node->left, value);
        return findNode(node->right, value);
    }

public:

    enum Order { Prefix, Infix, Postfix };

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
        if (!node) return;  // Узел не найден

        if (value < node->data) {
            removeHelper(node->left, value);
        }
        else if (value > node->data) {
            removeHelper(node->right, value);
        }
        else {  // Найден узел, который нужно удалить
            if (!node->left && !node->right) {  // Узел является листом
                delete node;
                node = nullptr;
                size--;
            }
            else if (node->left && !node->right) {  // Узел имеет только левого ребенка
                Node* temp = node;
                node = node->left;
                delete temp;
                size--;
            }
            else if (!node->left && node->right) {  // Узел имеет только правого ребенка
                Node* temp = node;
                node = node->right;
                delete temp;
                size--;
            }
            else {  // Узел имеет двух детей
                Node* minNode = node->right;
                Node* parentOfMinNode = node;
                if (!minNode->left) {  // Минимальный узел находится непосредственно справа
                    node->data = minNode->data;
                    node->right = minNode->right;  // Подвесим правое поддерево минимального узла к текущему узлу
                    delete minNode;
                }
                else {
                    while (minNode->left) {  // Находим минимальный узел в правом поддереве
                        parentOfMinNode = minNode;
                        minNode = minNode->left;
                    }
                    node->data = minNode->data;  // Заменяем данные узла на минимальные из правого поддерева
                    removeHelper(parentOfMinNode->left, minNode->data);  // Удаляем минимальный узел
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

    void toArrayHelper(Node* node, int*& array, int& index, Order order) {
        if (!node) return;
        if (order == Prefix) array[index++] = node->data;
        toArrayHelper(node->left, array, index, order);
        if (order == Infix) array[index++] = node->data;
        toArrayHelper(node->right, array, index, order);
        if (order == Postfix) array[index++] = node->data;
    }

    int* ToArray(Order order) {
        int* array = new int[size];
        int index = 0;
        toArrayHelper(root, array, index, order);
        return array;
    }

    int* ToArray() {
        return ToArray(Infix);
    }

    void ToLeft(int value) {
        Node* parent = nullptr;
        Node* node = root;

        while (node && node->data != value) {
            parent = node;
            if (value < node->data) node = node->left;
            else node = node->right;
        }

        if (!node || !node->right) return;

        if (!parent) root = rotateLeft(node);
        else if (parent->left == node) parent->left = rotateLeft(node);
        else parent->right = rotateLeft(node);
    }

    void ToRight(int value) {
        Node* parent = nullptr;
        Node* node = root;

        while (node && node->data != value) {
            parent = node;
            if (value < node->data) node = node->left;
            else node = node->right;
        }

        if (!node || !node->left) return;

        if (!parent) root = rotateRight(node);
        else if (parent->left == node) parent->left = rotateRight(node);
        else parent->right = rotateRight(node);
    }

    void Balance() {
        root = balanceHelper(root);
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
        else if (choice == "remove") {
            cin >> data;
            t.remove(data);
        }
        else if (choice == "clear") {
            t.clear();
        }
        else if (choice == "count") {
            cout << t.count() << endl;
        }
        else if (choice == "toarray") {
            string orderStr;
            cin >> orderStr;
            Tree::Order order = Tree::Infix;
            if (orderStr == "prefix") order = Tree::Prefix;
            else if (orderStr == "postfix") order = Tree::Postfix;
            int* arr = t.ToArray(order);
            for (int i = 0; i < t.count(); i++) {
                cout << arr[i] << " ";
            }
            cout << endl;
            delete[] arr;
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
        else if (choice == "stop") {
            break;
        }
        else {
            break;
        }
    }
}
