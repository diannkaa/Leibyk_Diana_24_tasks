#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

struct Bank {
    string name;
    double depositRate;
    double creditRate;
    int clients;
    string country;
};

void addBank(Bank*& banks, int& size) {
    Bank b;

    cout << "Назва: ";
    cin.ignore();
    getline(cin, b.name);

    cout << "Депозитна ставка: ";
    cin >> b.depositRate;

    cout << "Кредитна ставка: ";
    cin >> b.creditRate;

    cout << "Кількість клієнтів: ";
    cin >> b.clients;

    cout << "Країна: ";
    cin.ignore();
    getline(cin, b.country);

    Bank* temp = new Bank[size + 1];

    for (int i = 0; i < size; i++)
        temp[i] = banks[i];

    temp[size] = b;

    delete[] banks;
    banks = temp;
    size++;

    cout << "Банк додано!\n";
}

void showBanks(Bank* banks, int size) {
    if (size == 0) {
        cout << "Немає банків\n";
        return;
    }

    for (int i = 0; i < size; i++) {
        cout << "\nНазва: " << banks[i].name << endl;
        cout << "Депозит: " << banks[i].depositRate << endl;
        cout << "Кредит: " << banks[i].creditRate << endl;
        cout << "Клієнти: " << banks[i].clients << endl;
        cout << "Країна: " << banks[i].country << endl;
    }
}

void bestBanks(Bank* banks, int size) {
    if (size == 0) {
        cout << "Немає даних\n";
        return;
    }

    int bestDep = 0;
    int bestCred = 0;

    for (int i = 1; i < size; i++) {
        if (banks[i].depositRate > banks[bestDep].depositRate)
            bestDep = i;

        if (banks[i].creditRate < banks[bestCred].creditRate)
            bestCred = i;
    }

    cout << "\nНайкраща депозитна ставка:\n";
    cout << banks[bestDep].name << " (" << banks[bestDep].depositRate << "%)\n";

    cout << "\nНайкраща кредитна ставка:\n";
    cout << banks[bestCred].name << " (" << banks[bestCred].creditRate << "%)\n";
}

void saveToFile(Bank* banks, int size) {
    ofstream file("banks.txt");

    for (int i = 0; i < size; i++) {
        file << banks[i].name << endl;
        file << banks[i].depositRate << endl;
        file << banks[i].creditRate << endl;
        file << banks[i].clients << endl;
        file << banks[i].country << endl;
    }

    file.close();
    cout << "Збережено!\n";
}

void readFromFile(Bank*& banks, int& size) {
    ifstream file("banks.txt");

    if (!file) return;

    Bank b;

    while (getline(file, b.name)) {
        file >> b.depositRate;
        file >> b.creditRate;
        file >> b.clients;
        file.ignore();
        getline(file, b.country);

        Bank* temp = new Bank[size + 1];

        for (int i = 0; i < size; i++)
            temp[i] = banks[i];

        temp[size] = b;

        delete[] banks;
        banks = temp;
        size++;
    }

    file.close();
}

void removeBank(Bank*& banks, int& size) {
    if (size == 0) {
        cout << "Немає банків\n";
        return;
    }

    for (int i = 0; i < size; i++) {
        cout << i + 1 << ". " << banks[i].name << endl;
    }

    int index;
    cout << "Номер для видалення: ";
    cin >> index;

    if (index < 1 || index > size) return;

    Bank* temp = new Bank[size - 1];

    for (int i = 0, j = 0; i < size; i++) {
        if (i != index - 1)
            temp[j++] = banks[i];
    }

    delete[] banks;
    banks = temp;
    size--;

    cout << "Видалено!\n";
}

int main() {

    setlocale(LC_ALL, "Ukrainian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    Bank* banks = nullptr;
    int size = 0;

    readFromFile(banks, size);

    int choice;

    do {
        cout << "\n1.Додати банк\n";
        cout << "2.Показати банки\n";
        cout << "3.Найкращі ставки\n";
        cout << "4.Видалити банк\n";
        cout << "5.Зберегти у файл\n";
        cout << "0.Вихід\n";
        cout << "Вибір: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addBank(banks, size);
            break;
        case 2:
            showBanks(banks, size);
            break;
        case 3:
            bestBanks(banks, size);
            break;
        case 4:
            removeBank(banks, size);
            break;
        case 5:
            saveToFile(banks, size);
            break;
        case 0:
            cout << "Вихід...\n";
            break;
        default:
            cout << "Помилка!\n";
        }

    } while (choice != 0);

    delete[] banks;
}