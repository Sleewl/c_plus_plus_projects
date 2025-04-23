#include <iostream>
using namespace std;

void inArray(int arr[], int size) {
    cout << "In inArray(int arr[], int size)" << endl;
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

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
        int arr1[size];
        cout << "Enter the elements of the array: ";
        for (int i = 0; i < size; i++) {
            cin >> arr1[i];
        }

        inArray(arr1, size);

        int* arr2 = new int[size];
        cout << "Enter the elements of the array: ";
        for (int i = 0; i < size; i++) {
            cin >> arr2[i];
        }

        inArray(arr2, size);

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
