#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "RUS");
    double x, y;
    int dayNumber = 1;
    cout << "������� �������������� ����� x y" << endl;
    cin >> x;
    cin >> y;
    if (cin.fail() || x == 0 || y == 0) {
        cerr << "��������� ������ �� ������� ��� ������ �����������";
        return 1;
    }
    while (x < y) {
        x += x * 0.1;
        dayNumber++;
    }
    if (x >= y) {
        cout << "����� ���: " << dayNumber;
    }
    return 0;

}
