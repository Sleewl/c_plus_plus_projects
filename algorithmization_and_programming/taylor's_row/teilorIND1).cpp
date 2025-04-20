#include <iostream>

#include <iomanip>

#include <cmath>

using namespace std;

// Функция для вычисления значения функции e^-x
double calculateExponential(double x, double absError, int numberMax);

int main() {
    setlocale(LC_ALL, "ru");
    double absError = 1e-6;  // Абсолютная погрешность
    int numberMax = 100;     // Максимальное число слагаемых
    double intervalStart = -1.0;
    double intervalEnd = 1.0;
    double intervalStep = 0.1;
   

    try {
        cout << "Введите точность вычислений:";
        cin >> absError;
        if (cin.fail()) {
            throw invalid_argument("");
        }
        cout << "Введите число слагаемых:";
        cin >> numberMax;
        if (cin.fail()) {
            throw invalid_argument("");
        }
        cout << "Введите первое число интервала:";
        cin >> intervalStart;
        if (cin.fail()) {
            throw invalid_argument("");
        }
        cout << "Введите последнее число интервала:";
        cin >> intervalEnd;
        if (cin.fail()) {
            throw invalid_argument("");
        }
        cout << "Введите шаг интверала:";
        cin >> intervalStep;
        if (cin.fail()) {
            throw invalid_argument("");
        }
        cout << left << setw(10) << "x" << setw(20) << "Approximated e^-x" << setw(15) << "Actual e^-x" << endl;
    }
    catch (invalid_argument) {
        cerr << "Вы ввели некорректные данные, пожалуйста попробуйте снова." << endl;
        return 1;
    }
    

    for (double x = intervalStart; x <= intervalEnd; x += intervalStep) {
        try {
            double approximatedValue = calculateExponential(x, absError, numberMax);
            double actualValue = exp(-x);
            cout << fixed << setprecision(6) << left << setw(10) << x << setw(20) << approximatedValue << setw(15) << actualValue << endl;
        }
        catch (out_of_range) {
            cerr << "x is not in the range(-1, 1)";
            return 1;
        }
    }
    return 0;
}


double calculateExponential(double x, double absError, int numberMax) {
    if (x <= -1 || x >= 1) {
        throw out_of_range("x is not in the range (-1, 1)");
    }

    double result = 1.0; // Первый член ряда
    double term = 1.0;  // Текущий член ряда
    int n = 1;

    while (abs(term) > absError && n < numberMax) {
        term *= (-x) / n;
        result += term;
        n++;
    }

    return result;
}