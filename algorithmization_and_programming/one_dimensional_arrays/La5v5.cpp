#include <iostream>

using namespace std;


// Функция для динамического массива
void inArray(int* arr, int size);

//функция для встроенного массива
void inArray1(int* arr1, int size);

int main() {
    setlocale(LC_ALL, "ru");
    const int SIZE = 5; 

    try {
        // Создание встроенного массива
        int arr1[SIZE] = {};
        cout << "Enter 5 elements of the array1: " << '\n';
       
        for (int i = 0; i < SIZE; i++) {
            cin >> arr1[i];
            if (cin.fail()) {
                throw invalid_argument("");
            }
        }

        // Вызов функции для встроенного массива
        inArray1(arr1, SIZE);

        // создание динамического массива
        
        int size2 = 0;
        cout << "Введите размер второго - динамического массива: " << '\n';
        cin >> size2;
        if (cin.fail()) {
            throw runtime_error("");
        }
        int* arr2 = new int[size2];
        if (!arr2) { // если память не выделена
            throw domain_error("");
        }
        cout << "Enter the elements of the array2: " << '\n';
        for (int i = 0; i < size2; i++) {
            cin >> *(arr2 + i);
            if (cin.fail()) {
                throw exception("");
            }
        }
        inArray(arr2, size2);
    
    }
    catch (runtime_error) {
        cerr << "количество элементов задано некорректно" << '\n';
    }
    catch (domain_error) {
        cerr << "Не удалось выделить память" << '\n';
    }
    catch (invalid_argument) {
        cerr << "Введенные значения некорректны!" << '\n';
    }
    catch (exception) {
        cerr << "Введенные значения некорректны" << '\n';
    }
    
 }


//функция для встроенного массива
void inArray1(int* arr1, int size) {
    cout << "Элементы встроенного массива:";
    for (int i = 0; i < size; i++) {
        cout << '\n' << arr1[i] << '\n';
    }

}

// Функция для динамического массива
void inArray(int* arr, int size) {
    cout << "Элементы динамического массива массива:";
    for (int i = 0; i < size; i++) {
        cout << '\n' << arr[i] << '\n';
    }
    delete[] arr;
}