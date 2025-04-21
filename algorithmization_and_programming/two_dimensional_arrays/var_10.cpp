#include <iostream> 

using namespace std;

int** allocate_memory(int rows, int cols);

void free_memory(int** matrix, int rows);

void initialize_matrix(int** matrix, int rows, int cols);

void print_matrix(int** matrix, int rows, int cols);

int has_duplicate_column(int** matrix, int rows, int col);

int count_duplicate_columns(int** matrix, int rows, int cols);

int main() {
    int rows = 3;
    int cols = 3;
    int** matrix = allocate_memory(rows, cols);

    initialize_matrix(matrix, rows, cols);

    printf("Matrix:\n");
    print_matrix(matrix, rows, cols);

    int duplicate_columns = count_duplicate_columns(matrix, rows, cols);
    printf("Êîëè÷åñòâî ñòîëáöîâ ñ ïîâòîðÿþùèìèñÿ ýëåìåíòàìè: %d\n", duplicate_columns);

    free_memory(matrix, rows);

    return 0;
}

int** allocate_memory(int rows, int cols) {
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }
    return matrix;
}

void free_memory(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}


void initialize_matrix(int** matrix, int rows, int cols) {
    setlocale(LC_ALL, "Ru");
    cout << "Ââåäèòå ìàòðèöó 3 íà 3 " << '\n';
    try {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cin >> matrix[i][j];
                if (cin.fail()) {
                    throw invalid_argument("Ââåäåíû íåêîððåêòíûå äàííûå ");
                }
            }
        }

    }
    catch (invalid_argument) {
        cerr << "Âû ââåëè íåêîððåêòíûå äàííûå, ïîæàëóéñòà ïîïðîáóéòå ñíîâà." << endl;
        exit(EXIT_FAILURE);

    } 
}

void print_matrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

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

int count_duplicate_columns(int** matrix, int rows, int cols) {
    int count = 0;
    for (int j = 0; j < cols; j++) {
        if (has_duplicate_column(matrix, rows, j)) {
            count++;
        }
    }
    return count;
}
