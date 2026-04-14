#include <iostream>
#include <ctime>
#include <windows.h>

using namespace std;

double** createMatrix(int size) {
    double** arr = new double* [size];
    for (int i = 0; i < size; i++) {
        arr[i] = new double[size];
    }
    return arr;
}

void fillRandom(double** arr, int size) {
    int left = -10;
    int right = 10;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            arr[i][j] = rand() % (right - left + 1) + left;
        }
    }
}

void printMatrix(double** arr, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << arr[i][j] << "\t";
        }
        cout << endl;
    }
}

void deleteMatrix(double** arr, int size) {
    for (int i = 0; i < size; i++) {
        delete[] arr[i];
    }
    delete[] arr;
}

double sector5Sum(double** arr, int size, int k) {
    double sum = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i <= j && arr[i][j] < k) {
                sum += arr[i][j];
            }
        }
    }

    return sum;
}

double averageNegative(double** arr, int size) {
    double sum = 0;
    int count = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (arr[i][j] < 0) {
                sum += arr[i][j];
                count++;
            }
        }
    }

    return (count != 0) ? sum / count : 0;
}

int processSector1(double** arr, int size, double avgNeg) {
    int count = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i <= j && i + j <= size - 1) {
                arr[i][j] = avgNeg;
                count++;
            }
        }
    }

    return count;
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, "Ukrainian");

    srand(time(0));

    int size, k;

    cout << "Введіть розмір матриці n: ";
    cin >> size;

    cout << "Введіть k: ";
    cin >> k;

    double** arr = createMatrix(size);
    fillRandom(arr, size);

    cout << "\nПочаткова матриця:\n";
    printMatrix(arr, size);

    double sum = sector5Sum(arr, size, k);
    double avgNeg = averageNegative(arr, size);
    int sector1Count = processSector1(arr, size, avgNeg);

    cout << "\nСума в секторі 5\\ (< k): " << sum << endl;
    cout << "Середнє від’ємних: " << avgNeg << endl;
    cout << "Кількість елементів у секторі *1: " << sector1Count << endl;

    cout << "\nМатриця після змін:\n";
    printMatrix(arr, size);

    deleteMatrix(arr, size);

    return 0;
}