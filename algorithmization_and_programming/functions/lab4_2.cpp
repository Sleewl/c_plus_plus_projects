#include <iostream>

using namespace std;


int count_binari(int binary_choice);


int main() {
	setlocale(LC_ALL, "RU");
	int number = 0;

	cout << "Ââåäèòå öåëîå ÷èñëî" << '\n';

	cin >> number;
	if (!cin) {
		cerr << "Ââåäåííîå çíà÷åíèå íå ìîæåò áûòü áóêâîé" << '\n';
		return 1;
	}
	else if (number == 0) {
		cerr << "Ââåäåííîå çíà÷åíèå äîëæíî áûòü îòëè÷íî îò íóëÿ" << '\n';
		return 1;
	}

	else if (number < 0) {
		cout << "Åäèíèö â ÷èñëå: " << count_binari(abs(number)) << '\n';
	}

	else if (number > 0) {
		cout << "Åäèíèö â ÷èñëå: " << count_binari(number) << '\n';
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
