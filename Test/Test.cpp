#include <iostream>
using namespace std;

int main()
{
    int* m = {};

    for (int i = 4; i > 0; i--) {
        cin >> m[i];
    }

    cout << endl;

    for (int i = 1; i < 5; i++) {
        cout << m[i] << endl;
    }
    system("pause");
}


