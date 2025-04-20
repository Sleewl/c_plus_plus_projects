#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "RUS");
    double x, y;
    int dayNumber = 1;
    cout << "Введите действительные числа x y" << endl;
    cin >> x;
    cin >> y;
    if (cin.fail() || x == 0 || y == 0) {
        cerr << "Спортсмен никуда не побежал или данные некорректны";
        return 1;
    }
    while (x < y) {
        x += x * 0.1;
        dayNumber++;
    }
    if (x >= y) {
        cout << "Номер дня: " << dayNumber;
    }
    return 0;

}
