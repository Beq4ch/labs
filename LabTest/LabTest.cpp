#include <iostream>
using namespace std;

class Stack {
private:
    int* arr;
    int top;
    int size;
public:

    Stack() {
        arr = nullptr;
        top = -1;
        size = 0;
    }

    Stack(int n) {
        arr = new int[n];
        size = n;
        top = -1;
    }

    ~Stack() {
        delete[] arr;
    }
    



};


int main()
{
    cout << "Hello World!\n";
}

