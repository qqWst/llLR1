#include <iostream>
#include <sstream>
#include <string>

#include "file.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "");

    LoadAll();
    cout << "Абстрактные типы данных. Напишите HELP для просмотра списка команд." << endl;

    string line;
    while (true) {
        cout << "> ";
        if (!getline(cin, line)) break;
        istringstream in(line);
        string cmdName, dsName, value, target, out;
        if (!(in >> cmdName)) continue;

        commandType cmd = getCommand(cmdName);
        if (cmd == commandType::HELP) { printHelp(); continue; }
        if (cmd == commandType::EXIT) break;

        if (!(in >> dsName)) { cout << "Такого названия нет!" << endl; continue; }

        int index = -1;
        bool changed = false;

        switch (cmd) {

            case commandType::MPUSH: {
                Array* arr = fetchArray(dsName);
                if (in >> value) { push_backArray(*arr, value); cout << ">> " << value << endl; changed = true; }
                else cout << "Ошибка" << endl;
                break;
            }
            case commandType::MINSERT: {
                Array* arr = fetchArray(dsName);
                if (in >> value >> index && index >= 0 && (size_t)index <= lengthArray(*arr)) {
                    insertArray(*arr, (size_t)index, value); cout << ">> " << value << endl; changed = true;
                } else cout << "Ошибка" << endl;
                break;
            }
            case commandType::MGET: {
                Array* arr = fetchArray(dsName);
                if (in >> index && index >= 0 && (size_t)index < lengthArray(*arr))
                    cout << ">> " << getArray(*arr, (size_t)index) << endl;
                else cout << "Ошибка" << endl;
                break;
            }
            case commandType::MSET: {
                Array* arr = fetchArray(dsName);
                if (in >> value >> index && index >= 0 && (size_t)index < lengthArray(*arr)) {
                    setArray(*arr, (size_t)index, value); cout << ">> " << value << endl; changed = true;
                } else cout << "Ошибка" << endl;
                break;
            }
            case commandType::MREMOVE: {
                Array* arr = fetchArray(dsName);
                if (in >> index && index >= 0 && (size_t)index < lengthArray(*arr)) {
                    value = getArray(*arr, (size_t)index);
                    removeArray(*arr, (size_t)index);
                    cout << ">> " << value << endl; changed = true;
                } else cout << "Ошибка" << endl;
                break;
            }
            case commandType::MDEL: {
                Array* arr = fetchArray(dsName);
                if (in >> value) {
                    MDEL(*arr, value);
                } else cout << "Ошибка" << endl;
                break;
            }
            case commandType::MSIZE: {
                Array* arr = fetchArray(dsName);
                cout << ">> " << lengthArray(*arr) << endl;
                break;
            }

            
            case commandType::SLPUSHBACK: {
                SingleList slist = *fetchSingleList(dsName);
                if (in >> value) {
                    push_backSList(slist, value);
                    cout << ">> " << value << endl; changed = true; }
                else cout << "Ошибка" << endl;
                break;
            }
            case commandType::SLPUSHFRONT: {
                SingleList* slist = fetchSingleList(dsName);
                if (in >> value) { push_frontSList(*slist, value); cout << ">> " << value << endl; changed = true; }
                else cout << "Ошибка" << endl;
                break;
            }
            case commandType::SLPUSHAFTER: {
                SingleList* slist = fetchSingleList(dsName);
                if (in >> value >> target) {
                    if (getSList(*slist, target)) {
                        push_afterSList(*slist, value, target);
                        cout << ">> " << value << endl; changed = true;
                    } else cout << "Ошибка" << endl;
                } else cout << "Ошибка" << endl;
                break;
            }
            case commandType::SLPUSHBEFORE: {
                SingleList* slist = fetchSingleList(dsName);
                if (in >> value >> target) {
                    if (getSList(*slist, target)) {
                        push_beforeSList(*slist, value, target);
                        cout << ">> " << value << endl; changed = true;
                    } else cout << "Ошибка" << endl;
                } else cout << "Ошибка" << endl;
                break;
            }
            case commandType::SLSET: {
                SingleList* slist = fetchSingleList(dsName);
                if (in >> value >> target) {
                    if (getSList(*slist, target)) {
                        setSList(*slist, value, target);
                        cout << ">> " << value < endl; changed = true;
                    }
                } else cout << "Ошибка" << endl;
                break;
            }
            case commandType::SLGET: {
                SingleList* slist = fetchSingleList(dsName);
                if (in >> value) {
                    if (getSList(*slist, value)) cout << ">> " << value << endl;
                    else cout << "Ошибка" << endl;
                } else cout << "Ошибка" << endl;
                break;
            }
            case commandType::SLREMOVE: {
                SingleList* slist = fetchSingleList(dsName);
                if (in >> value) {
                    if (getSList(*slist, value)) {
                        deleteByValueSList(*slist, value);
                        cout << ">> " << value << endl; changed = true;
                    } else cout << "Ошибка" << endl;
                } else cout << "Ошибка" << endl;
                break;
            }
            case commandType::SLSIZE: {
                SingleList* slist = fetchSingleList(dsName);
                cout << ">> " << sizeOfSList(*slist) << endl;
                break;
            }
            case commandType::SLPOPFRONT: {
                SingleList* slist = fetchSingleList(dsName);
                if (slist->head) {
                    out = slist->head->data;
                    pop_frontSList(*slist);
                    cout << ">> " << out << endl; changed = true;
                } else cout << "Ошибка" << endl;
                break;
            }
            case commandType::SLPOPBACK: {
                SingleList* slist = fetchSingleList(dsName);
                if (slist->head) {
                    pop_backSList(*slist);
                    cout << ">> Удалено" << endl; changed = true;
                } else cout << "Ошибка" << endl;
                break;
            }
            case commandType::SLPOPAFTER: {
                SingleList* slist = fetchSingleList(dsName);
                if (in >> target) {
                    pop_afterSList(*slist, target);
                    cout << ">> Удалено" << endl; changed = true;
                } else cout << "Ошибка" << endl;
                break;
            }
            case commandType::SLPOPBEFORE: {
                SingleList* slist = fetchSingleList(dsName);
                if (in >> target) {
                    pop_beforeSList(*slist, target);
                    cout << ">> Удалено" << endl; changed = true;
                } else cout << "Ошибка" << endl;
                break;
            }


            case commandType::DLPUSHBACK: {
                DoubleList* dlist = fetchDoubleList(dsName);
                if (in >> value) { push_backDList(*dlist, value); cout << ">> " << value << endl; changed = true; }
                else cout << "Ошибка" << endl;
                break;
            }
            case commandType::DLPUSHFRONT: {
                DoubleList* dlist = fetchDoubleList(dsName);
                if (in >> value) { push_frontDList(*dlist, value); cout << ">> " << value << endl; changed = true; }
                else cout << "Ошибка" << endl;
                break;
            }
            case commandType::DLPUSHAFTER: {
                DoubleList* dlist = fetchDoubleList(dsName);
                if (in >> value >> target) {
                    push_afterDList(*dlist, value, target); cout << ">> " << value << endl; changed = true; 
                } else cout << "Ошибка" << endl;
                break;
            }
            case commandType::DLPUSHBEFORE: {
                DoubleList* dlist = fetchDoubleList(dsName);
                if (in >> value >> target) {
                    push_beforeDList(*dlist, value, target); cout << ">> " << value << endl; changed = true;
                } else cout << "Ошибка" << endl;
                break;
            }
            case commandType::DLSET: {
                DoubleList* dlist = fetchDoubleList(dsName);
                if (in >> value >> target) {
                    setDList(*dlist, value, target);
                    cout << ">> " << value << endl; changed = true;
                } else cout << "Ошибка" << endl;
                break;
            }
            case commandType::DLGET: {
                DoubleList* dlist = fetchDoubleList(dsName);
                if (in >> value) {
                    cout << ">> " << (getDList(*dlist, value)) ? "True" : "False" << endl;
                } else cout << "Ошибка" << endl;
                break;
            }
            case commandType::DLREMOVE: {
                DoubleList* dlist = fetchDoubleList(dsName);
                if (in >> value) {
                    deleteByValueDList(*dlist, value);
                    cout << ">> " << value << endl; changed = true;
                } else cout << "Ошибка" << endl;
                break;
            }
            case commandType::DLSIZE: {
                DoubleList* dlist = fetchDoubleList(dsName);
                cout << ">> " << sizeOfSList(*dlist) << endl;
                break;
            }
            case commandType::DLPOPFRONT: {
                DoubleList* dlist = fetchDoubleList(dsName);
                if (dlist->head) {
                    out = dlist->head->data;
                    pop_frontDList(*dlist);
                    cout << ">> " << out << endl; changed = true;
                } else cout << "Ошибка" << endl;
                break;
            }
            case commandType::DLPOPBACK: {
                DoubleList* dlist = fetchDoubleList(dsName);
                if (dlist->tail) {
                    out = dlist->tail->data;
                    pop_backDList(*dlist);
                    cout << ">> " << out << endl; changed = true;
                } else cout << "Ошибка" << endl;
                break;
            }
            case commandType::DLPOPAFTER: {
                DoubleList* dlist = fetchDoubleList(dsName);
                if (in >> target) {
                    pop_afterDList(*dlist, target);
                    cout << ">> Удалено" << endl; changed = true;
                } else cout << "Ошибка" << endl;
                break;
            }
            case commandType::DLPOPBEFORE: {
                DoubleList* dlist = fetchDoubleList(dsName);
                if (in >> target) {
                    pop_beforeDList(*dlist, target);
                    cout << ">> Удалено" << endl; changed = true;
                } else cout << "Ошибка" << endl;
                break;
            }


            case commandType::SPUSH: {
                Stack* stack = fetchStack(dsName);
                if (in >> value) {
                    pushStack(stack, value);
                    cout << ">> " << value << endl; changed = true;
                } else cout << "Ошибка" << endl;
                break;
            }
            case commandType::SPOP: {
                Stack* stack = fetchStack(dsName);
                if (!isEmptyStack(stack)) {
                    out = stack->head->value;
                    popStack(*stack);
                    cout << ">> " << out << endl; changed = true;
                } else cout << "Ошибка" << endl;
                break;
            }


            case commandType::QPUSH: {
                Queue* queue = fetchQueue(dsName);
                if (in >> value) {
                    pushQueue(queue, value);
                    cout << ">> " << value << endl; changed = true;
                } else cout << "Ошибка" << endl;
                break;
            }
            case commandType::QPOP: {
                Queue* queue = fetchQueue(dsName);
                if (!isEmptyQueue(queue)) {
                    popQueue(queue, out);
                    cout << ">> " << out << endl; changed = true;
                } else cout << "Ошибка" << endl;
                break;
            }


            case commandType::TADD: {
                TreeNode** tree = fetchTree(dsName);
                if (in >> value) {
                    try {
                        int v = stoi(value);
                        AddTree(*tree, v);
                        cout << ">> " << v << endl; changed = true;
                    } catch (...) { cout << "Ошибка" << endl; }
                } else cout << "Ошибка" << endl;
                break;
            }
            case commandType::TFIND: {
                TreeNode** tree = fetchTree(dsName);
                if (in >> value) {
                    try {
                        int v = stoi(value);
                        if (searchTree(*tree, v)) cout << ">> " << v << endl;
                        else cout << "Ошибка" << endl;
                    } catch (...) { cout << "Ошибка" << endl; }
                } else cout << "Ошибка" << endl;
                break;
            }
            case commandType::TDEL: {
                TreeNode** tree = fetchTree(dsName);
                if (in >> value) {
                    try {
                        int v = stoi(value);
                        if (searchTree(*tree, v)) {
                            *tree = removeTree(*tree, v);
                            cout << ">> " << v << endl; changed = true;
                        } else cout << "Ошибка" << endl;
                    } catch (...) { cout << "Ошибка" << endl; }
                } else cout << "Ошибка" << endl;
                break;
            }

            case commandType::PRINT: {
                string targetName;
                if (!(in >> targetName)) { cout << "Ошибка" << endl; break; }

                if (dsName == "array")      { Array* arr = fetchArray(targetName); printArray(*arr); }
                else if (dsName == "slist") { SingleList* slist = fetchSingleList(targetName); printSList(*slist); }
                else if (dsName == "dlist") { DoubleList* dlist = fetchDoubleList(targetName); printDList(*dlist); }
                else if (dsName == "stack") { Stack* stack = fetchStack(targetName); printStack(*stack); }
                else if (dsName == "queue") { Queue* queue = fetchQueue(targetName); printQueue(*queue); }
                else if (dsName == "tree")  { TreeNode** tree = fetchTree(targetName); PrintTree(*tree); }
                else cout << "Ошибка" << endl;
                break;
            }

            default:
                cout << "Неизвестная команда. HELP — список команд" << endl;
        }

        if (changed) SaveAll();
    }

    SaveAll();
    freeEverything();

    cout << "Завершение..." << endl;
    return 0;
}