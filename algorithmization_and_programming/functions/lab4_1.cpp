#include <iostream>

using namespace std;

bool testing(int numberForFunctions);

int main() {
	setlocale(LC_ALL, "RU");
	int number;
	int result;
	cout << "Ââåäèòå ÷èñëî" << '\n';
	cin >> number;
	if (!cin) {
		cerr << "Ââåäåííîå çíà÷åíèå íåêîððåêòíî" << '\n';
		return 1;
	}
	else if (number <= 1) {
		cerr << "×èñëî íå ÿâëÿåòñÿ ïðîñòûì" << '\n';
	}
	else {
		result = testing(number);
		if (result == 1) {
			cout << "×èñëî ÿâëÿåòñÿ ïðîñòûì " << '\n';
		}
		else if (result == 0) {
			cout << "×èñëî íå ÿâëÿåòñÿ ïðîñòûì " << '\n';
		}
	}
	return 0;
}

bool testing(int numberForFunctions) {
	if (numberForFunctions <= 1) {
		return false;
	}

	for (int i = 2; i * i <= numberForFunctions; i++) {
		if (numberForFunctions % i == 0) {
			return false;
		}
	}

	return true;
}






