#include <vector>

#include <iostream>

using namespace std;


int** allocate_memory(int rows, int cols);

void free_memory(int** matrix, int rows);

void initialize_matrix(int** matrix, int rows, int cols);

void print_matrix(int** matrix, int rows, int cols);

int is_unique_row(int* row, int cols);

int count_unique_rows(int** matrix, int rows, int cols);

int main() {
    int rows = 3;
    int cols = 3;
    int** matrix = allocate_memory(rows, cols);

    initialize_matrix(matrix, rows, cols);

    printf("Matrix:\n");
    print_matrix(matrix, rows, cols);

    int unique_rows = count_unique_rows(matrix, rows, cols);
    printf("Êîëè÷åñòâî ñòðîê ñ óíèêàëüíûìè ýëåìåíòàìè: %d\n", unique_rows);
    int notUnique_cols = 0;

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
    try {
        cout << "Ââåäèòå ýëåìåíòû ìàòðèöû 3 íà 3: " << '\n';
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
//ôóíêöèÿ äëÿ âñòðîåííîãî ìàññèâà
void inArray1(int* arr1, int size) {
	cout << "Ýëåìåíòû âñòðîåííîãî ìàññèâà:";
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
	cout << "Ââåäèòå ýëåìåíòû âñòðîåííîãî ìàññèâà" << '\n';
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
	cout << "Êîëè÷åñòâî ñòðîê, ñîäåðæàùåå ðàçëè÷íûå ýëåìåíòû: " <<  count ;
	return 0;

}*/
	
	

		
	
