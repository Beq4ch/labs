﻿#include <iostream>
#include <windows.h>
using namespace std;

// Структура узла связанного списка
struct Node {
    int data; // Значение, хранящееся в узле
    Node* next; // Указатель на следующий узел
};

// Класс Queue, реализующий структуру данных очередь
class Queue {
private:
    Node* head; // Указатель на первый узел очереди
    Node* tail; // Указатель на последний узел очереди
    int size; // Количество элементов в очереди
public:
    Queue() {
        head = tail = nullptr; // Инициализация пустой очереди
        size = 0;
    }

    ~Queue() {
        clear(); // Освобождение памяти при удалении объекта
    }

    void queue(int data) { // Метод для добавления элемента в очередь
        Node* temp = new Node(); // Создание нового узла
        temp->data = data; // Присваивание значения новому узлу
        temp->next = nullptr; // Установка следующего указателя на nullptr

        if (head == nullptr) { // Если очередь пуста
            head = temp; // Новый узел становится головой
        }
        else {
            tail->next = temp; // Новый узел добавляется в конец очереди
        }

        tail = temp; // Обновление указателя на последний узел
        size++; // Увеличение размера очереди
    }

    int unqueue() { // Метод для извлечения элемента из очереди
        if (head == nullptr) { // Если очередь пуста
            return 0; // Возвращаем ноль
        }
        Node* temp = head; // Сохранение указателя на первый узел
        int data = temp->data; // Получение значения первого узла
        head = head->next; // Перемещение головы на следующий узел
        delete temp; // Освобождение памяти первого узла
        size--; // Уменьшение размера очереди
        return data; // Возвращение значения извлеченного элемента
    }

    void insertBeforeNegative() { // Метод для вставки 1 перед отрицательными элементами
        Node* curr = head; // Текущий указатель, начиная с головы
        Node* prev = nullptr; // Предыдущий указатель, начиная с nullptr
        while (curr != nullptr) { // Проход по всем узлам очереди
            if (curr->data < 0) { // Если текущий элемент отрицательный
                Node* temp = new Node(); // Создание нового узла со значением 1
                temp->data = 1; // Присваивание единицы новому узлу
                temp->next = curr; // Новый узел указывает на текущий
                if (prev == nullptr) { // Если это первый отрицательный элемент
                    head = temp; // Новый узел становится головой
                }
                else {
                    prev->next = temp; // Иначе, новый узел вставляется перед текущим
                }
                prev = temp->next; // Перемещение указателя на предыдущий узел
            }
            else {
                prev = curr; // Если элемент не отрицательный, обновляем предыдущий указатель
            }
            size++; // Увеличение размера очереди
            curr = curr->next; // Переход к следующему узлу
        }
    }

    // Удаление из очереди всех элементов с отрицательной информационной частью
    void removeNegative() {
        Node* prev = nullptr; // Указатель на предыдущий узел
        Node* curr = head; // Указатель на текущий узел
        while (curr != nullptr) { // Пока не достигнут конец очереди
            if (curr->data < 0) { // Если текущий узел содержит отрицательное число
                Node* temp = curr; // Сохранение указателя на текущий узел
                if (prev == nullptr) { // Если текущий узел является головой
                    head = head->next; // Перемещение головы на следующий узел
                }
                else { // Если текущий узел не является головой
                    prev->next = curr->next; // Пропуск текущего узла
                }
                if (curr == tail) { // Если текущий узел является хвостом
                    tail = prev; // Предыдущий узел становится хвостом
                }
                curr = curr->next; // Переход к следующему узлу
                delete temp; // Удаление текущего узла
                size--; // Уменьшение размера очереди
            }
            else { // Если текущий узел не содержит отрицательное число
                prev = curr; // Текущий узел становится предыдущим
                curr = curr->next; // Переход к следующему узлу
            }
        }
    }

    int count(int data) { // Метод для подсчета количества вхождений заданного значения
        int count = 0; // Счетчик вхождений
        Node* curr = head; // Текущий указатель, начиная с головы
        while (curr != nullptr) { // Проход по всем узлам очереди
            if (curr->data == data) { // Если значение совпадает
                count++; // Увеличение счетчика
            }
            curr = curr->next; // Переход к следующему узлу
        }
        return count; // Возвращение количества вхождений
    }

    void clear() { // Метод для очистки очереди
        Node* curr = head; // Текущий указатель, начиная с головы
        while (curr != nullptr) { // Проход по всем узлам очереди
            Node* temp = curr; // Сохранение текущего узла
            curr = curr->next; // Переход к следующему узлу
            delete temp; // Освобождение памяти текущего узла
        }
        head = nullptr; // Установка головы в nullptr
        tail = nullptr; // Установка хвоста в nullptr
        size = 0; // Обнуление размера очереди
    }
};

int main()
{
    SetConsoleCP(1251); // Установка кодировки консоли для ввода
    SetConsoleOutputCP(1251); // Установка кодировки консоли для вывода

    Queue q; // Создание объекта очереди
    string choice; // Переменная для хранения выбора пользователя
    int data; // Переменная для хранения ввода пользователя
    while (true) { // Цикл, пока пользователь не выберет выход
        cin >> choice; // Ввод выбора пользователя
        if (choice == "insert") {
            cin >> data; // Ввод значения
            q.queue(data); // Добавление элемента в очередь
        }
        else if (choice == "front") {
            cout << q.unqueue() << endl; // Извлечение элемента из очереди
        }
        else if (choice == "insertBeforeNegative") { // Если выбрана вставка 1 перед отрицательными элементами
            q.insertBeforeNegative();
        }
        else if (choice == "removeNegative") { // Если выбрано удаление отрицательных элементов
            q.removeNegative();
        }
        else if (choice == "count") {  // Если выбран подсчет вхождений
            cin >> data; // Ввод значения
            cout << q.count(data) << endl; // Вывод результата
        }
        else if (choice == "clear") { // Если выбрана очистка очереди
            q.clear();
            cout << "Очередь очищена" << endl; // Сообщение об успешной очистке
        }
        else if (choice == "stop") { // Если выбран выход
            break;
        }
        else { // Если выбрано неверное значение
            cout << "Неверный выбор, попробуйте еще раз" << endl; // Сообщение об ошибке
            break;
        }
    }
}
