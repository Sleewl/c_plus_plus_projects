#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "RUS");
    int x1 = 0,
        y1 = 0,
        x2 = 0,
        y2 = 0;
    cout << "������� x1 y1 x2 y2" << endl;
    cin >> x1 >> y1 >> x2 >> y2;
    if (!cin) {
        cerr << "��������� ����� ������ ���� ������ � �� �������� ��������� ��������";
        return 1;        
    }
    if (x1 == 0 || y1 == 0 || x2 == 0 || y2 == 0) {
        cerr << "��� ���������� ������ ���� ������� �� ����";
        return 1;
    }
    else if (x1 * x2 > 0 && y1 * y2 > 0)
        cout << "��";
    else {
        cout << "���";
    }
    return 0;

}