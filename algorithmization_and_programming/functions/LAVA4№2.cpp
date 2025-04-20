#include <iostream>

using namespace std;


int count_binari(int binary_choice);


int main() {
	setlocale(LC_ALL, "RU");
	int number = 0;

	cout << "������� ����� �����" << '\n';

	cin >> number;
	if (!cin) {
		cerr << "��������� �������� �� ����� ���� ������" << '\n';
		return 1;
	}
	else if (number == 0) {
		cerr << "��������� �������� ������ ���� ������� �� ����" << '\n';
		return 1;
	}

	else if (number < 0) {
		cout << "������ � �����: " << count_binari(abs(number)) << '\n';
	}

	else if (number > 0) {
		cout << "������ � �����: " << count_binari(number) << '\n';
	}
	return 0;
}

int count_binari(int binary_choice) {
	int count = 0;
	while (binary_choice > 0) {
		if (binary_choice % 2 == 1) {
			count++;
		}
		binary_choice = binary_choice / 2;
	}
	return count;
}