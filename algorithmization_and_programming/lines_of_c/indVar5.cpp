#include <iostream>

#include <fstream>

#include <string>

using namespace std;

const string ERROR_WRONG_OPEN_FILE = "Не удалось открыть файл";
const string IN_FILE = "in.txt";
const string OUT_FILE = "out.txt";

char* createNewStringVarFive(const char* source1, const char* source2);

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
        const char* total = createNewStringVarFive(inputString1.c_str(), inputString2.c_str());
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

char* createNewStringVarFive(const char* source1, const char* source2) {
    int source1Length = 0;
    while (source1[source1Length] != '\0') {
        source1Length++;
    }

    int source2Length = 0;
    while (source2[source2Length] != '\0') {
        source2Length++;
    }

    char* destination = new char[source1Length + source2Length + 1];
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

    for (int i = 0; i < source2Length; i++) {
        found = false;

        for (int j = 0; j < source1Length; j++) {
            if (source2[i] == source1[j]) {
                found = true;
                break;
            }
        }

        if (!found) {
            destination[destinationIndex] = source2[i];
            destinationIndex++;
        }
    }

    destination[destinationIndex] = '\0';

    return destination;
}


































