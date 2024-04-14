// Lab4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>
#include <string>
using namespace std;

struct City {
    string name;
    string region;
    int population;

    City(string city, string nameRegion, int populationK) {
        name = city;
        region = nameRegion;
        population = populationK;
    }
};


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
        if (index == currentIndex) {
            return currentNode;
        }

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
        if (index < 0 || index >= size) {
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

        }
    }

    T elementAt(int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of bounds");
        }

        if (index == currentIndex) {
            return currentNode->data;
        }

        Node* current = getNode(index);

        return current->data;
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

    void printList() {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data.name << " (" << current->data.region << ", " << current->data.population << ")" << endl;
            current = current->next;
        }
        cout << endl;
    }
};

int main()
{
    List<City> cityList;

    SetConsoleCP(1251); // Установка кодировки консоли для ввода
    SetConsoleOutputCP(1251); // Установка кодировки консоли для вывода

    // Заполнение списка городов с клавиатуры
    int numCities, population;
    string name, region;
    cout << "Введите количество городов: ";
    cin >> numCities;

    for (int i = 0; i < numCities; ++i) {
        cout << "Город " << i + 1 << ":" << endl;
        cout << "Название: ";
        cin >> name;
        cout << "Регион: ";
        cin >> region;
        cout << "Население: ";
        cin >> population;
        cityList.add(City(name, region, population));
    }

    // Вывод списка городов
    cout << "\nСписок городов:" << endl;
    cityList.printList();
}

