#include <iostream>

using namespace std;

bool testing(int numberForFunctions);

int main() {
	setlocale(LC_ALL, "RU");
	int number;
	int result;
	cout << "������� �����" << '\n';
	cin >> number;
	if (!cin) {
		cerr << "��������� �������� �����������" << '\n';
		return 1;
	}
	else if (number <= 1) {
		cerr << "����� �� �������� �������" << '\n';
	}
	else {
		result = testing(number);
		if (result == 1) {
			cout << "����� �������� ������� " << '\n';
		}
		else if (result == 0) {
			cout << "����� �� �������� ������� " << '\n';
		}
	}
	return 0;
}

bool testing(int numberForFunctions) {
	if (numberForFunctions <= 1) {  // ���� ����� ������ ��� ����� 1, ��� �� �������� �������
		return false;
	}

	for (int i = 2; i * i <= numberForFunctions; i++) {  // ��������� �������� �� ����� �� �����
		if (numberForFunctions % i == 0) {  // ���� ����� ������� �� i ��� �������, ��� �� �������� �������
			return false;
		}
	}

	return true;  // ���� ��� �������� ��������, ����� �������� �������
}






