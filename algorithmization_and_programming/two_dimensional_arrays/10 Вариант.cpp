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

// Функция для проверки, содержит ли столбец повторяющиеся элементы
int has_duplicate_column(int** matrix, int rows, int col);

// Функция для подсчета количества столбцов, содержащих повторяющиеся элементы
int count_duplicate_columns(int** matrix, int rows, int cols);

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

    // Подсчет количества столбцов, содержащих повторяющиеся элементы
    int duplicate_columns = count_duplicate_columns(matrix, rows, cols);
    printf("Количество столбцов с повторяющимися элементами: %d\n", duplicate_columns);

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
    cout << "Введите матрицу 3 на 3 " << '\n';
    try {
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

// Функция для проверки, содержит ли столбец повторяющиеся элементы
int has_duplicate_column(int** matrix, int rows, int col) {
    for (int i = 0; i < rows - 1; i++) {
        for (int j = i + 1; j < rows; j++) {
            if (matrix[i][col] != matrix[j][col]) {
                return EXIT_SUCCESS; 
            }
        }
    }
    return EXIT_FAILURE; 
}

// Функция для подсчета количества столбцов, содержащих повторяющиеся элементы
int count_duplicate_columns(int** matrix, int rows, int cols) {
    int count = 0;
    for (int j = 0; j < cols; j++) {
        if (has_duplicate_column(matrix, rows, j)) {
            count++;
        }
    }
    return count;
}