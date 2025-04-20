#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "RUS");
    int x1 = 0,
        y1 = 0,
        x2 = 0,
        y2 = 0;
    cout << "Введите x1 y1 x2 y2" << endl;
    cin >> x1 >> y1 >> x2 >> y2;
    if (!cin) {
        cerr << "Введенные числа должны быть целыми и не являться буквенным символом";
        return 1;        
    }
    if (x1 == 0 || y1 == 0 || x2 == 0 || y2 == 0) {
        cerr << "Все координаты должны быть отличны от нуля";
        return 1;
    }
    else if (x1 * x2 > 0 && y1 * y2 > 0)
        cout << "ДА";
    else {
        cout << "НЕТ";
    }
    return 0;

}