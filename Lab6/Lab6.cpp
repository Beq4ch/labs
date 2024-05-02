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
        else if (choice == "remove") {
            cin >> data;
            t.remove(data);
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