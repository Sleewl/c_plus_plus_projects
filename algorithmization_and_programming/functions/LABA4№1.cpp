#include <iostream>

using namespace std;

bool testing(int numberForFunctions);

int main() {
	setlocale(LC_ALL, "RU");
	int number;
	int result;
	cout << "¬ведите число" << '\n';
	cin >> number;
	if (!cin) {
		cerr << "¬веденное значение некорректно" << '\n';
		return 1;
	}
	else if (number <= 1) {
		cerr << "„исло не €вл€етс€ простым" << '\n';
	}
	else {
		result = testing(number);
		if (result == 1) {
			cout << "„исло €вл€етс€ простым " << '\n';
		}
		else if (result == 0) {
			cout << "„исло не €вл€етс€ простым " << '\n';
		}
	}
	return 0;
}

bool testing(int numberForFunctions) {
	if (numberForFunctions <= 1) {  // если число меньше или равно 1, оно не €вл€етс€ простым
		return false;
	}

	for (int i = 2; i * i <= numberForFunctions; i++) {  // провер€ем делители до корн€ из числа
		if (numberForFunctions % i == 0) {  // если число делитс€ на i без остатка, оно не €вл€етс€ простым
			return false;
		}
	}

	return true;  // если все проверки пройдены, число €вл€етс€ простым
}






