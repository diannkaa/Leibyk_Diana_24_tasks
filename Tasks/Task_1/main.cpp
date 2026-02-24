#include <iostream>
#include <chrono>
#include <future>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;
using namespace chrono;

void showArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

void countingSort(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++)
        if (arr[i] > max) 
            max = arr[i];

    int* count = new int[max + 1] {};
    for (int i = 0; i < size; i++)
        count[arr[i]]++;

    int x = 0;
    for (int i = 0; i <= max; i++)
        while (count[i]--)
            arr[x++] = i;

    delete[] count;
}

void selectionSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int min = i;
        for (int j = i + 1; j < size; j++)
            if (arr[j] < arr[min])
                min = j;
        swap(arr[i], arr[min]);
    }
}

int partition(int arr[], int left, int right) {
    int marker = arr[right];
    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (arr[j] < marker) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[right]);
    return i + 1;
}

void quickSort(int arr[], int left, int right) {
    if (left < right) {
        int m = partition(arr, left, right);
        quickSort(arr, left, m - 1);
        quickSort(arr, m + 1, right);
    }
}

int binarySearch(int arr[], int left, int right, int key) {
    while (left <= right) {
        int splitPoint = left + (right - left) / 2;
        if (arr[splitPoint] == key) 
            return splitPoint;
        if (arr[splitPoint] < key) 
            left = splitPoint + 1;
        else right = splitPoint - 1;
    }
    return -1;
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, "Ukrainian");

    srand(time(0));

    cout << "******************************************\n";
    cout << "\tПОРІВНЯННЯ ЧАСУ СОРТУВАННЯ\n";
    cout << "******************************************\n";

    int sizesArray[] = { 10, 100, 1000, 8000, 50000, 150000 };
    for (int i = 0; i < 6; i++) {
        int n = sizesArray[i];
        int* arrC = new int[n];
        int* arrS = new int[n];
        int* arrQ = new int[n];

        for (int j = 0; j < n; j++) {
            int v = rand() % 10000;
            arrC[j] = arrS[j] = arrQ[j] = v;
        }

        auto startTimeC = high_resolution_clock::now();
        countingSort(arrC, n);
        double timeCount = duration<double>(high_resolution_clock::now() - startTimeC).count();

        auto startTimeS = high_resolution_clock::now();
        selectionSort(arrS, n);
        double timeSelect = duration<double>(high_resolution_clock::now() - startTimeS).count();

        auto startTimeQ = high_resolution_clock::now();
        quickSort(arrQ, 0, n - 1);
        double timeQuick = duration<double>(high_resolution_clock::now() - startTimeQ).count();

        cout << "\nРозмір: " << n << " -> Сортування підрахунком: " << timeCount << " сек.\n";
        cout << "Розмір: " << n << " -> Сортування вибором: " << timeSelect << " сек.\n";
        cout << "Розмір: " << n << " -> Швидке сортування: " << timeQuick << " сек.\n";
        cout << "--------------------------------------------------\n";

        delete[] arrC;
        delete[] arrS;
        delete[] arrQ;
    }

    cout << "\n===== СИНХРОННЕ ТА АСИНХРОННЕ ШВИДКЕ СОРТУВАННЯ =====\n";
    int arraySize = 150000;
    int* arraySync = new int[arraySize];
    int* arrayAsync = new int[arraySize];

    for (int i = 0; i < arraySize; i++) {
        int randomValue = rand() % 10000;
        arraySync[i] = arrayAsync[i] = randomValue;
    }

    auto sStart = high_resolution_clock::now();
    quickSort(arraySync, 0, arraySize - 1);
    double tSync = duration<double>(high_resolution_clock::now() - sStart).count();

    auto aStart = high_resolution_clock::now();
    future<void> fut = async(launch::async, quickSort, arrayAsync, 0, arraySize - 1);
    fut.get();
    double tAsync = duration<double>(high_resolution_clock::now() - aStart).count();

    cout << "Синхронне Швидке сортування (" << arraySize << " елементів): " << tSync << " сек.\n";
    cout << "Асинхронне Швидке сортування (" << arraySize << " елементів): " << tAsync << " сек.\n";

    delete[] arraySync;
    delete[] arrayAsync;

    cout << "\n*********************************************\n";
    cout << "\tСОРТУВАННЯ МАСИВУ КОРИСТУВАЧА\n";
    cout << "*********************************************\n";

    int numbersCount;
    cout << "Введіть кількість елементів масиву: ";
    cin >> numbersCount;

    int* userNumbers = new int[numbersCount];
    for (int i = 0; i < numbersCount; i++)
        userNumbers[i] = rand() % 1000;

    cout << "\nМасив чисел:\n";
    showArray(userNumbers, numbersCount);

    cout << "\nВкажіть метод сортування:\n1 - Сортування підрахунком\n2 - Сортування вибором\n3 - Швидке сортування\nВаш вибір: ";
    int choice;
    cin >> choice;

    auto startSortTime = high_resolution_clock::now();
    if (choice == 1) 
        countingSort(userNumbers, numbersCount);
    else if 
        (choice == 2) selectionSort(userNumbers, numbersCount);
    else 
        quickSort(userNumbers, 0, numbersCount - 1);
    auto endSortTime = high_resolution_clock::now();

    double timeToSort = duration<double>(endSortTime - startSortTime).count();

    cout << "\nВідсортований масив:\n";
    showArray(userNumbers, numbersCount);
    cout << "Тривалість сортування: " << timeToSort << " сек.\n";

    int searchNumber;
    cout << "\nВведіть число для пошуку: ";
    cin >> searchNumber;

    auto searchStartTime = high_resolution_clock::now();
    int foundIndex = binarySearch(userNumbers, 0, numbersCount - 1, searchNumber);
    auto searchEndTime = high_resolution_clock::now();

    double searchTime = duration<double>(searchEndTime - searchStartTime).count();
    if (foundIndex != -1)
        cout << "Знайдено число! Його індекс: " << foundIndex << endl;
    else
        cout << "Число відсутнє у масиві." << endl;
    cout << "Тривалість пошуку: " << searchTime << " сек.\n";

    delete[] userNumbers;
    cout << "\nПрограма завершила роботу.\n";
}