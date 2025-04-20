#include <iostream>

#include <fstream>

#include <string>

using namespace std;

const string ERROR_WRONG_OPEN_FILE = "Не удалось открыть файл";
const string IN_FILE = "in.txt";
const string OUT_FILE = "out.txt";

char* createNewStringVarFifteen(const char* source1, const char* source2);

int main() {
    setlocale(LC_ALL, "Ru");

    ifstream file1(IN_FILE);
    ofstream file2(OUT_FILE);
    string inputString1, inputString2;

    if (!file1.is_open()) {
        cerr << "Error: " << ERROR_WRONG_OPEN_FILE << '\n';
        return EXIT_FAILURE;
    }

    if (getline(file1, inputString1) && getline(file1, inputString2)) {
        const char* total = createNewStringVarFifteen(inputString1.c_str(), inputString2.c_str());
        file2 << total;
        delete[] total;
    }
    else {
        cerr << "Error: Не удалось прочитать данные из файла.\n";
        return EXIT_FAILURE;
    }

    // Закрыть входной файл
    file1.close();
    // Закрыть выходной файл
    file2.close();

    return 0;
}

char* createNewStringVarFifteen(const char* source1, const char* source2) {
    int source1Length = strlen(source1);
    int source2Length = strlen(source2);

    char* destination = new char[source1Length + 1];
    int destinationIndex = 0;
    bool found = false;

    for (int i = 0; i < source1Length; i++) {
        found = false;

        for (int j = 0; j < source2Length; j++) {
            if (source1[i] == source2[j]) {
                found = true;
                break;
            }
        }

        if (!found) {
            destination[destinationIndex] = source1[i];
            destinationIndex++;
        }
    }

    destination[destinationIndex] = '\0';

    return destination;
}