#include <vector>

#include <iostream>

using namespace std;



// Функция для выделения памяти под матрицу в динамической памяти
int** allocate_memory(int rows, int cols);

// Функция для освобождения памяти, выделенной под матрицу
void free_memory(int** matrix, int rows);

// Функция для инициализации элементов матрицы значениями
void initialize_matrix(int** matrix, int rows, int cols);

// Функция для вывода матрицы на экран
void print_matrix(int** matrix, int rows, int cols);

// Функция для проверки, содержит ли строка только различные элементы
int is_unique_row(int* row, int cols);

// Функция для подсчета количества строк, содержащих только различные элементы
int count_unique_rows(int** matrix, int rows, int cols);

int main() {
    int rows = 3;
    int cols = 3;

    // Выделение памяти под матрицу
    int** matrix = allocate_memory(rows, cols);

    // Инициализация матрицы
    initialize_matrix(matrix, rows, cols);

    // Вывод матрицы
    printf("Matrix:\n");
    print_matrix(matrix, rows, cols);

    // Подсчет количества строк, содержащих только различные элементы
    int unique_rows = count_unique_rows(matrix, rows, cols);
    printf("Количество строк с уникальными элементами: %d\n", unique_rows);


    //Подсчет количества столбцов, содержащих одинаковые элементы
    int notUnique_cols = 0;

    // Освобождение памяти
    free_memory(matrix, rows);

    return 0;
}




// Функция для выделения памяти под матрицу в динамической памяти
int** allocate_memory(int rows, int cols) {
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }
    return matrix;
}

// Функция для освобождения памяти, выделенной под матрицу
void free_memory(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
// Функция для инициализации элементов матрицы
void initialize_matrix(int** matrix, int rows, int cols) {
    setlocale(LC_ALL, "Ru");
    try {
        cout << "Введите элементы матрицы 3 на 3: " << '\n';
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cin >> matrix[i][j];
                if (cin.fail()) {
                    throw invalid_argument("Введены некорректные данные ");
                }
            }
        }

    }
    catch (invalid_argument) {
        cerr << "Вы ввели некорректные данные, пожалуйста попробуйте снова." << endl;
        exit(EXIT_FAILURE);

    }
}

// Функция для вывода матрицы на экран
void print_matrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Функция для проверки, содержит ли строка только различные элементы
int is_unique_row(int* row, int cols) {
    for (int i = 0; i < cols - 1; i++) {
        for (int j = i + 1; j < cols; j++) {
            if (row[i] != row[j]) {
                return(EXIT_FAILURE); 
            }
        }
    }
    return(EXIT_SUCCESS); 
}

// Функция для подсчета количества строк, содержащих только различные элементы
int count_unique_rows(int** matrix, int rows, int cols) {
    int count = 0;
    for (int i = 0; i < rows; i++) {
        if (is_unique_row(matrix[i], cols)) {
            count++;
        }
    }
    return count;
}








































































/**
//функция для встроенного массива
void inArray1(int* arr1, int size) {
	cout << "Элементы встроенного массива:";
	for (int i = 0; i < size; i++) {
		cout << '\n' << arr1[i] << '\n';
	}

}

int main() {
	setlocale(LC_ALL, "RU");
	int count = 0;
	const int ROWS = 3;
	const int COLS = 2;
	int arr[ROWS][COLS]{};
	cout << "Введите элементы встроенного массива" << '\n';
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS;j++) {
			cin >> arr[i][j];

		}
	}
	for (int l = 1; l < ROWS; l++) {
		if (arr[l] != arr[l - 1]) {
			count++;
		}			
	}
	cout << "Количество строк, содержащее различные элементы: " <<  count ;
	return 0;

}*/
	
	

		
	