#include "List.h"
#include <iostream>
#include <windows.h>
using namespace std;

class HashSet {
private:
    static const int TABLE_SIZE = 256; // Размер хеш-таблицы
    List<string>* table[TABLE_SIZE]; // Массив указателей на списки

    // Хеш-функция
    int hash(string key) const {
        unsigned long hash = 5381;
        for (char c : key) {
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        }
        return hash % TABLE_SIZE;
    }
public:
    HashSet() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            table[i] = new List<string>();
        }
    }

    ~HashSet() {
        clear();
        for (int i = 0; i < TABLE_SIZE; ++i) {
            delete table[i];
        }
    }

    void add(string data) {
        int index = hash(data);
        if (!contains(data)) {
            table[index]->add(data);
        }
    }

    void remove(string data) {
        int index = hash(data);
        int count = table[index]->count();
        for (int i = 0; i < count; ++i) {
            if (table[index]->elementAt(i) == data) {
                table[index]->removeAt(i);
                break;
            }
        }
    }

    bool contains(string data) {
        int index = hash(data);
        int count = table[index]->count();
        for (int i = 0; i < count; ++i) {
            if (table[index]->elementAt(i) == data)
                return true;
        }
        return false;
    }

    void clear() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            table[i]->clear();
        }
    }

    int count() {
        int total = 0;
        for (int i = 0; i < TABLE_SIZE; ++i) {
            total += table[i]->count();
        }
        return total;
    }

    string* ToArray() {
        int total = count();
        string* array = new string[total];
        int idx = 0;

        for (int i = 0; i < TABLE_SIZE; ++i) {
            int bucketSize = table[i]->count();
            for (int j = 0; j < bucketSize; ++j) {
                if (idx < total) {
                    array[idx] = table[i]->elementAt(j);
                    idx++;
                }
                else {
                    break;
                }
            }
        }
        return array;
    }
};

int main() {


}
