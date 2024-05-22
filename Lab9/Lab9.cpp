#include <iostream>
#include "Tree.h"
using namespace std;

class HashTree {
private:
    static const int TABLE_SIZE = 256; // Размер хеш-таблицы
    Tree table[TABLE_SIZE];          // Массив деревьев

    int hash(int value) const {
        int hash = 5381;
        hash = hash * 33 + value;
        return hash % TABLE_SIZE;
    }

public:
    HashTree() {}

    ~HashTree() {
        clear();
    }

    void add(int value) {
        int index = hash(value);
        if (!table[index].contains(value)) {
            table[index].add(value);
        }
    }

    void remove(int value) {
        int index = hash(value);
        if (table[index].contains(value)) {
            table[index].remove(value);
        }
    }

    void clear() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            table[i].clear();
        }
    }

    bool contains(int value) {
        int index = hash(value);
        return table[index].contains(value);
    }

    int count() {
        int totalCount = 0;
        for (int i = 0; i < TABLE_SIZE; ++i) {
            totalCount += table[i].count();
        }
        return totalCount;
    }

    int* ToArray() {
        int totalSize = count();
        int* array = new int[totalSize];
        int index = 0;
        for (int i = 0; i < TABLE_SIZE; ++i) {
            table[i].fillArray(array, index);
        }
        return array;
    }
};

int main() {
    HashTree ht;
    string choice;
    int data;

    while (true) {
        cin >> choice;
        if (choice == "add") {
            cin >> data;
            ht.add(data);
        }
        else if (choice == "remove") {
            cin >> data;
            ht.remove(data);
        }
        else if (choice == "clear") {
            ht.clear();
        }
        else if (choice == "count") {
            cout << ht.count() << endl;
        }
        else if (choice == "contains") {
            cin >> data;
            cout << (ht.contains(data) ? "Yes" : "No") << endl;
        }
        else if (choice == "toArray") {
            int* array = ht.ToArray();
            int count = ht.count();
            cout << "Elements in HashTree: ";
            for (int i = 0; i < count; ++i) {
                cout << array[i] << " ";
            }
            cout << endl;
            delete[] array;
        }
        else if (choice == "stop") {
            break;
        }
        else {
            cout << "Unknown command" << endl;
        }
    }
}
