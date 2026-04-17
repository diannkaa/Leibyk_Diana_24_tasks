#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

int countWords(const string& sentence) {
    int wordCount = 0;
    bool isInsideWord = false;

    for (int i = 0; i < sentence.size(); i++) {
        char symbol = sentence[i];

        if (symbol != ' ' && symbol != '\t' && symbol != '\n') {
            if (!isInsideWord) {
                isInsideWord = true;
                wordCount++;
            }
        }
        else {
            isInsideWord = false;
        }
    }

    return wordCount;
}

void processFile(const string& inputFileName, const string& outputFileName) {
    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);

    if (!inputFile.is_open()) {
        cout << "Помилка відкриття вхідного файлу!" << endl;
        return;
    }

    if (!outputFile.is_open()) {
        cout << "Помилка створення вихідного файлу!" << endl;
        return;
    }

    string text = "";
    string line;

    while (getline(inputFile, line)) {
        text += line + " ";
    }

    inputFile.close();

    string sentence = "";
    string shortestSentence = "";
    int minWordCount = -1;

    for (int i = 0; i < text.size(); i++) {
        char symbol = text[i];
        sentence += symbol;

        if (symbol == '.' || symbol == '!' || symbol == '?') {
            int wordCount = countWords(sentence);

            if (wordCount > 0) {
                if (minWordCount == -1 || wordCount < minWordCount) {
                    minWordCount = wordCount;
                    shortestSentence = sentence;
                }
            }

            sentence = "";
        }
    }

    int wordCount = countWords(sentence);
    if (wordCount > 0) {
        if (minWordCount == -1 || wordCount < minWordCount) {
            minWordCount = wordCount;
            shortestSentence = sentence;
        }
    }

    if (minWordCount != -1) {
        outputFile << "Речення з найменшою кількістю слів:\n";
        outputFile << shortestSentence << endl;
        outputFile << "Кількість слів: " << minWordCount << endl;
    }
    else {
        outputFile << "Файл порожній або не містить речень." << endl;
    }

    outputFile.close();
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, "Ukrainian");

    processFile("input.txt", "output.txt");

    cout << "Готово! Результат записано у файл output.txt" << endl;

    return 0;
}