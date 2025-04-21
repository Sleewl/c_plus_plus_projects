#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "RUS");
    int number;
    int min_positive = 105500000;
    int min_positive_index = -1;
    int index = 0;

    cout << "Введите последовательность целых чисел (для завершения введите 0):" << endl;

    while (true) {
        cin >> number;

        if (number == 0) {
            break;
        }

        index++;

        if (number > 0 && num < min_positive) {
            min_positive = number;
            min_positive_index = index;
        }
    }

    if (min_positive_index != -1) {
        cout << "Минимальное положительное значение: " << min_positive << endl;
        cout << "Его номер среди всех введенных чисел: " << min_positive_index << endl;
    }
    else {
        cout << "В последовательности нет положительных чисел." << endl;
    }

    return 0;
}