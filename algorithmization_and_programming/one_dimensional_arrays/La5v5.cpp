#include <iostream>

using namespace std;


void inArray(int* arr, int size);

void inArray1(int* arr1, int size);

int main() {
    setlocale(LC_ALL, "ru");
    const int SIZE = 5; 

    try {
        // Ñîçäàíèå âñòðîåííîãî ìàññèâà
        int arr1[SIZE] = {};
        cout << "Enter 5 elements of the array1: " << '\n';
       
        for (int i = 0; i < SIZE; i++) {
            cin >> arr1[i];
            if (cin.fail()) {
                throw invalid_argument("");
            }
        }

        inArray1(arr1, SIZE);

        
        int size2 = 0;
        cout << "Ââåäèòå ðàçìåð âòîðîãî - äèíàìè÷åñêîãî ìàññèâà: " << '\n';
        cin >> size2;
        if (cin.fail()) {
            throw runtime_error("");
        }
        int* arr2 = new int[size2];
        if (!arr2) { // åñëè ïàìÿòü íå âûäåëåíà
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
        cerr << "êîëè÷åñòâî ýëåìåíòîâ çàäàíî íåêîððåêòíî" << '\n';
    }
    catch (domain_error) {
        cerr << "Íå óäàëîñü âûäåëèòü ïàìÿòü" << '\n';
    }
    catch (invalid_argument) {
        cerr << "Ââåäåííûå çíà÷åíèÿ íåêîððåêòíû!" << '\n';
    }
    catch (exception) {
        cerr << "Ââåäåííûå çíà÷åíèÿ íåêîððåêòíû" << '\n';
    }
    
 }

void inArray1(int* arr1, int size) {
    cout << "Ýëåìåíòû âñòðîåííîãî ìàññèâà:";
    for (int i = 0; i < size; i++) {
        cout << '\n' << arr1[i] << '\n';
    }

}

// Ôóíêöèÿ äëÿ äèíàìè÷åñêîãî ìàññèâà
void inArray(int* arr, int size) {
    cout << "Ýëåìåíòû äèíàìè÷åñêîãî ìàññèâà ìàññèâà:";
    for (int i = 0; i < size; i++) {
        cout << '\n' << arr[i] << '\n';
    }
    delete[] arr;
}
