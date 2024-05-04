// Lab4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
using namespace std;

struct City {
    string name;
    string region;
    int population;


    City(string city = "", string nameRegion = "", int populationK = 0) {
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
        if (index < 0 || index >= size) {
            return nullptr;
        }
        if (index == 0) return head;
        if (index == size - 1) return tail;

        // Оптимизация: если запрашиваемый индекс близок к последнему 
        // использованному, идём от currentNode
        if (currentNode != nullptr && abs(index - currentIndex) < size / 2) {
            Node* current = currentNode;
            if (index > currentIndex) {
                for (int i = currentIndex; i < index; i++) {
                    current = current->next;
                }
            }
            else {
                for (int i = currentIndex; i > index; i--) {
                    current = current->prev;
                }
            }
            currentNode = current;
            currentIndex = index;
            return current;
        }

        // В остальных случаях идём от начала или конца списка
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

    ~List() {
        clear();
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
        if (index < 0 || index > size) {
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
            newNode->prev = curr->prev;
            newNode->next = curr;
            curr->prev = newNode;
            newNode->prev->next = newNode;
        }
        currentNode = newNode;
        currentIndex = index;
        size++;
    }

    void removeAt(int index) {
        if (index < 0 || index >= size) {
            return;
        }

        Node* temp = nullptr;
        if (index == 0) {
            temp = head;
            head = head->next;
            if (head != nullptr) {
                head->prev = nullptr;
            }
            else {
                tail = currentNode = nullptr;
                currentIndex = 0;
            }
        }
        else if (index == size - 1) {
            temp = tail;
            tail = tail->prev;
            tail->next = nullptr;
        }
        else {
            temp = getNode(index);
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }

        if (temp == currentNode) {
            currentNode = temp->prev;
            currentIndex = max(0, index - 1);
        }
        else if (index < currentIndex) {
            currentIndex--;
        }

        delete temp;
        size--;
    }

    T elementAt(int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("");
        }

        if (index == currentIndex && currentNode != nullptr) {
            return currentNode->data;
        }

        return getNode(index)->data;
    }

    int count() {
        return size;
    }

    void swappedAt(int index, T data) {
        Node* curr = getNode(index);
        curr->data = data;
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
};

void printList(List<City> list) {
    for (int i = 0; i < list.count(); i++) {
        City info = list.elementAt(i);
        cout << info.name << " (" << info.region << ", " << info.population << ")" << endl;
    }
}

void removeCitiesFromRegion(string regionName, List<City> &list) {
    int i = 0;
    while (i < list.count()) {
        if (list.elementAt(i).region == regionName) {
            list.removeAt(i);
        }
        else {
            i++;
        }
    }
}

void printRegionPopulation(List<City> list) {
    List<City> temp;
    for (int i = 0; i < list.count(); i++) {
        City listCity = list.elementAt(i);
        bool regionInList = false;
        for (int j = 0; j < temp.count(); j++) {
            City tempCity = temp.elementAt(j);
            if (tempCity.region == listCity.region) {
                tempCity.population += listCity.population;
                temp.swappedAt(j, tempCity);
                regionInList = true;
                break;
            }
        }

        if (!regionInList)
            temp.add(listCity);
    }

    for (int i = 0; i < temp.count(); i++) {
        for (int j = 0; j < temp.count() - 1; j++) {
            City curr = temp.elementAt(j);
            City next = temp.elementAt(j + 1);
            if (curr.population < next.population) {
                temp.swappedAt(i, next);
                temp.swappedAt(i + 1, curr);
            }
        }
    }

    for (int i = 0; i < temp.count(); i++) {
        cout << temp.elementAt(i).region << " " << temp.elementAt(i).population << endl;
    }

}

int main()
{
    List<City> cityList;

    int population, index;
    string name, region, choice;

    while (true) {
        cin >> choice;
        if (choice == "add") {
            cin >> name;
            cin >> region;
            cin >> population;
            cityList.add(City(name, region, population));
        }
        else if (choice == "insert") {
            cin >> index;
            cin >> name;
            cin >> region;
            cin >> population;
            cityList.insert(index, City(name, region, population));
        }
        else if (choice == "removeAt") {
            cin >> index;
            cityList.removeAt(index);
        }
        else if (choice == "elementAt") {
            cin >> index;
            try {
                City info = cityList.elementAt(index);
                cout << info.name << " (" << info.region << ", " << info.population << ")" << endl;
            }
            catch (out_of_range) {}
            
        }
        else if (choice == "count") {
            cout << cityList.count() << endl;
        }
        else if (choice == "removeCitiesFromRegion") {
            cin >> region;
            removeCitiesFromRegion(region, cityList);
        }
        else if (choice == "printRegionPopulation") {
            printRegionPopulation(cityList);
        }
        else if (choice == "print") {
            printList(cityList);
        }
        else if (choice == "clear") {
            cityList.clear();
        }
        else if (choice == "stop") {
            break;
        }
        else {
            break;
        }
    }
}

