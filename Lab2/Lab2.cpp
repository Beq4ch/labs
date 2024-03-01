#include <iostream>
#include <windows.h>
using namespace std;

struct Node {

    int data;
    Node* next;

};

class Queue {
private:
    Node* head;
    Node* tail;
    int size;

public:
    Queue() {
        head = tail = nullptr;
        size = 0;
    }

    ~Queue() {
        clear();
    }

    void queue(int data) {
        Node* temp = new Node;
        temp->data = data;
        temp->next = nullptr;
        if (head == nullptr) {
            head = temp;
        }
        else {
            tail->next = temp;
        }
        tail = temp;
        size++;
    }

    int count(int data) {
        int count = 0;
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->data == data) {
                count++;
            }
            curr = curr->next;
        }
        return count;
    }

    void clear() {
        Node* curr = head;
        while (curr != nullptr) {
            Node* temp = curr;
            curr = curr->next;
            delete temp;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    void outPut() {
        Node* curr = head;
        while (curr != nullptr) {
            cout << curr->data << " ";
            curr = curr->next;
        }
    }
};

int main()
{
    SetConsoleCP(1251); // Установка кодировки консоли для ввода
    SetConsoleOutputCP(1251); // Установка кодировки консоли для вывода

    Queue q;
    int choice;
    int data;
    bool exit = false;
    while (!exit) {
        system("cls");
        cout << "Выберите операцию:\n";
        cout << "1. Добавить элемент в очередь\n";
        cout << "2. Извлечь элемент из очереди\n";
        cout << "3. Вставить перед каждым отрицательным числом элемент со значением 1\n";
        cout << "4. Удалить из очереди все элементы с отрицательной информационной частью\n";
        cout << "5. Подсчитать количество вхождений переданного значения в коллекцию\n";
        cout << "6. Удалить все элементы коллекции\n";
        cout << "7. Выход\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Введите значение, которое хотите добавить в очередь: ";
            cin >> data;
            q.queue(data);
            cout << "Элемент " << data << " добавлен в очередь\n";
            break;
        case 2:
            cout << "Очередь:\n";
            q.outPut();
            system("pause");
            break;
        default:
            break;
        }
    }
}

