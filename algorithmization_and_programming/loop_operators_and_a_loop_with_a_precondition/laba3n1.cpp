#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "RUS");
    int number;
    int min_positive = 105500000;
    int min_positive_index = -1;
    int index = 0;

    cout << "������� ������������������ ����� ����� (��� ���������� ������� 0):" << endl;

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
        cout << "����������� ������������� ��������: " << min_positive << endl;
        cout << "��� ����� ����� ���� ��������� �����: " << min_positive_index << endl;
    }
    else {
        cout << "� ������������������ ��� ������������� �����." << endl;
    }

    return 0;
}