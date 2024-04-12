// Lab4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h> // Подключение библиотеки для работы с консолью
#include <string>
using namespace std;

struct City {
    string name;
    string region;
    int population;
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
        if (index == currentIndex + 1 && currentNode && currentNode->next) {
            currentNode = currentNode->next;
            currentIndex++;
            return currentNode;
        }
        else if (index == currentIndex - 1 && currentNode && currentNode->prev) {
            currentNode = currentNode->prev;
            currentIndex--;
            return currentNode;
        }

        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
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
        if (tail) {
            tail->next = newNode;
            newNode->prev = tail;
        }
        else {
            head = newNode;
        }
        tail = newNode;
        size++;
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
        lastAccessedNode = nullptr;
        lastAccessedIndex = 0;
    }
};

void printCities(List<City> cityList) {
    for (int i = 0; i < cityList.count(); ++i) {
        City city = cityList.elementAt(i);
        cout << "Город: " << city.name << ", Регион: " << city.region << ", Население: " << city.population << endl;
    }
}

int main()
{
    List<City> cityList;

    SetConsoleCP(1251); // Установка кодировки консоли для ввода
    SetConsoleOutputCP(1251); // Установка кодировки консоли для вывода

    // Заполнение списка городов с клавиатуры
    int numCities;
    cout << "Введите количество городов: ";
    cin >> numCities;

    for (int i = 0; i < numCities; ++i) {
        City city;
        cout << "Город " << i + 1 << ":" << endl;
        cout << "Название: ";
        cin >> city.name;
        cout << "Регион: ";
        cin >> city.region;
        cout << "Население: ";
        cin >> city.population;
        cityList.add(city);
    }

    // Вывод списка городов
    cout << "\nСписок городов:" << endl;
    printCities(cityList);
}
