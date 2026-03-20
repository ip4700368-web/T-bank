#include <iostream>
using namespace std;

int main() {
    system("chcp 1251");
    system("cls");

    int start, end;
    cin >> start >> end;

    if (start >= end) {
        return 1;
    }

    bool found = false;
    int a = 0, b = 1;

    while (a <= end) {
        if (a >= start) {
            cout << a << " ";
            found = true;
        }
        int next = a + b;
        a = b;
        b = next;
    }

    if (!found) {
        cout << "В заданном диапазоне нет чисел Фибоначчи";
    }
    cout << endl;

    return 0;
}