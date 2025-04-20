
/**
#include <iostream>

using namespace std;

void inArray(int arr[], int size) {

}

void inArray(int* arr, int size) {
    cin >> size;

}


int main() {
    
}
*/

#include <iostream>
using namespace std;

// Функция для встроенного массива
void inArray(int arr[], int size) {
    cout << "In inArray(int arr[], int size)" << endl;
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Функция для динамического массива
void inArray(int* arr, int size) {
    cout << "In inArray(int* arr, int size)" << endl;
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int size;
    cout << "Enter the number of elements: ";
    cin >> size;

    try {
        // Создание встроенного массива
        int arr1[size];
        cout << "Enter the elements of the array: ";
        for (int i = 0; i < size; i++) {
            cin >> arr1[i];
        }

        // Вызов функции для встроенного массива
        inArray(arr1, size);

        // Создание динамического массива
        int* arr2 = new int[size];
        cout << "Enter the elements of the array: ";
        for (int i = 0; i < size; i++) {
            cin >> arr2[i];
        }

        // Вызов функции для динамического массива
        inArray(arr2, size);

        // Освобождение памяти
        delete[] arr2;
    }
    catch (bad_alloc& e) {
        cout << "Error: Failed to allocate memory" << endl;
    }
    catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}





































/**
void inArray(int* arr, int size);

int main() {
    setlocale(LC_ALL, "rus");
    const int SIZE = 5;
    int arr[SIZE];

    try {
        cout << "Введите 5 элементов массива" << '\n';
        inArray(arr, SIZE);
    } 
    catch (const exception &ex) {
        cout << "Исключение: " << ex.what() << '\n';
    }
    

    return 0;
}

void inArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        if (!(cin >> arr[i])) {
            throw runtime_error("Ошибка ввода");
        }
    }
}*/



