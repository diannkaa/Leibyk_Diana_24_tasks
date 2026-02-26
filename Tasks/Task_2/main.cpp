#include <iostream>
#include <windows.h>
using namespace std;

double sumArray(double arr[], int size)
{
    double sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += arr[i];
    }
    return sum;
}

double sumSquares(double arr[], int size)
{
    double sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum = sum + arr[i] * arr[i];
    }
    return sum;
}

int findStarts(double Q, double Wp, double sumRi, double sumRi2)
{
    double result = (Q / Wp) * (sumRi - sumRi2);
    return (int)result; 
}

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, "Ukrainian");

    const int n = 8;

    double Ri[n] = { 0.4, 0.5, 2.1, 3.0, 2.6, 1.4, 1.6, 1.8 };

    double Q = 54;
    double Wp = 180;

    double sumRi = sumArray(Ri, n);
    double sumRi2 = sumSquares(Ri, n);

    int numDob = findStarts(Q, Wp, sumRi, sumRi2);

    cout << "Сума Ri = " << sumRi << endl;
    cout << "Сума Ri^2 = " << sumRi2 << endl;
    cout << "Добове число ввімкнень насоса = " << numDob << endl;
}