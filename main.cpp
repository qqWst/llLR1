#include "array.h"
#include <iostream>
using namespace std;

enum class commandType {
    MCREATE,
    MPUSH,
    MSET,
    MGET,
    MREMOVE,
    MINSERT,
    MSIZE,
    MDEL,
    PRINT,
    UNKNOWN
};

commandType getCommand(const string& command) {

    if (command == "MPUSH") return commandType::MPUSH;
    if (command == "MSET") return commandType::MSET;
    if (command == "MGET") return commandType::MGET;
    if (command == "MREMOVE") return commandType::MREMOVE;
    if (command == "MINSERT") return commandType::MINSERT;
    if (command == "MSIZE") return commandType::MSIZE;
    if (command == "MDEL") return commandType::MDEL;

    if (command == "PRINT") return commandType::PRINT;
    return commandType::UNKNOWN; 
}

int main(){
    setlocale(LC_ALL, "ru_RU.UTF-8");

    cout << "Реализация абстрактных структур данных" << endl;
    cout << "Команды:  MDEL" << endl;
    cout << "          MPUSH" << endl;
    cout << "          MSET" << endl;
    cout << "          MGET" << endl;
    cout << "          MREMOVE" << endl;
    cout << "          MINSERT" << endl;
    cout << "          MSIZE" << endl;
    cout << "          PRINT" << endl;

    Array arr = createArray();

    cout << "Способ ввода и вывода: 1. Консоль" << endl;
    cout << "                       2. Файл" << endl;
    int choice;
    cin >> choice;
    if (choice == 2) {
        cout << "Введите название файла:" << endl;
        string nameFile;
        cin >> nameFile;
        
    }

    string input;
    while (cin >> input) {
        commandType command = getCommand(input);
        switch (command) {
            case commandType::MPUSH: {
                cout << "Введите элемент:" << endl;
                int value;
                cin >> value;
                push_backArray(arr, value);
                cout << "Элемент " << value << " добавлен в конец массива." << endl;
                break;
            }
            case commandType::MSET: {
                cout << "Введите индекс и значение: " << endl;
                int value;
                size_t index;
                cin >> index >> value;
                setArray(arr, index, value);
                cout << "Элемент " << value << " добавлен в массив по индексу " << index << "." << endl;
                break;
            }
            case commandType::MGET: {
                cout << "Введите индекс элемента:" << endl;
                size_t index;
                cin >> index;
                int value = getArray(arr, index);
                cout << "Элемент по индексу " << index << " - " << value << "." << endl;
                break;
            }
            case commandType::MREMOVE: {
                cout << "Введите индекс:" << endl;
                size_t index;
                cin >> index;
                removeArray(arr, index);
                cout << "Элемент по индексу " << index << " был удален." << endl;
                break;
            }
            case commandType::MINSERT: {
                cout << "Введите индекс и элемент:" << endl;
                size_t index;
                int value;
                cin >> index >> value;
                insertArray(arr, index, value);
                cout << "Элемент " << value << " добавлен в массив по индексу " << index << "." << endl;
                break;
            }
            case commandType::MSIZE: {
                cout << "Размер массива: " << lengthArray(arr) << endl;
                break;
            }
            case commandType::MDEL: {
                killArray(arr);
                cout << "Массив был успешно удален." << endl;
                break;
            }
            case commandType::PRINT: {
                printArray(arr);
                break;
            }
            default: {
                cout << "ОШИБКА: Команда не распознана!!!" << endl;
                break;
            }
        }
    }
}