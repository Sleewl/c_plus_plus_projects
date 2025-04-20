#include <iostream> 

using namespace std;


int getMaxOfArray(int** array, int size);

int** createArray(int** arr, int const row, int const col);

void fillArray(int** arr, int const row, int const col);

const int ROWS = 2;
const int COLS = 3;

int main() {
    setlocale(LC_ALL, "ru");

    int** array = 0;

    array = createArray(array, ROWS, COLS);

    fillArray(array, ROWS, COLS);

    cout << "MaxOfArray - " << getMaxOfArray(array, ROWS * COLS);
    return 0;
}

int** createArray(int** arr, int const row, int const col) {
    arr = new int* [row];
    for (int i = 0; i < row; i++) {
        arr[i] = new int[col];
    }

    return arr;
}

void fillArray(int** arr, int const row, int const col) {
    try {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                cout << "Enter elemt of array > ";
                //cin >> arr[i][j];
                cin >> *(*(arr + i) + j);
                if (cin.fail()) {
                    throw invalid_argument("¬веденные данные некорректны");
                }

            }
        }

    }
    catch (invalid_argument) {
        cerr << "¬веденные данные некорректны" << '\n';
        exit(EXIT_FAILURE);
    }
    
}

int getMaxOfArray(int** array, int const size) {
  int maxOfArray = 0;
  for (int i = 0; i < ROWS; i++) {
    for (int k = 0; k < COLS; k++) {
      if (i+k == 0){
        maxOfArray = array[i][k];
      }
      else{
        if (array[i][k] > maxOfArray) {
          maxOfArray = array[i][k];
        }
      }
    }
  }
return maxOfArray;

}

