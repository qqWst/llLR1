#include <iostream>
#include <sstream>
#include <string>

#include "file.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "");

    LoadAll();
    cout << "Abstract Data Structures. HELP — list of commands." << endl;

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

        if (!(in >> dsName)) { cout << "No name provided" << endl; continue; }

        int index = -1;
        bool changed = false;

        switch (cmd) {

            // ======================= МАССИВ (M..) =======================
            case commandType::MPUSH: {
                Array* arr = fetchArray(dsName);
                if (in >> value) { push_backArray(*arr, value); cout << "-> " << value << endl; changed = true; }
                else cout << "No" << endl;
                break;
            }
            case commandType::MINSERT: {
                Array* arr = fetchArray(dsName);
                if (in >> value >> index && index >= 0 && (size_t)index <= lengthArray(*arr)) {
                    insertArray(*arr, (size_t)index, value); cout << "-> " << value << endl; changed = true;
                } else cout << "No" << endl;
                break;
            }
            case commandType::MGET: {
                Array* arr = fetchArray(dsName);
                if (in >> index && index >= 0 && (size_t)index < lengthArray(*arr))
                    cout << "-> " << getArray(*arr, (size_t)index) << endl;
                else cout << "No" << endl;
                break;
            }
            case commandType::MSET: {
                Array* arr = fetchArray(dsName);
                if (in >> value >> index && index >= 0 && (size_t)index < lengthArray(*arr)) {
                    setArray(*arr, (size_t)index, value); cout << "-> " << value << endl; changed = true;
                } else cout << "No" << endl;
                break;
            }
            case commandType::MDEL: {
                Array* arr = fetchArray(dsName);
                if (in >> index && index >= 0 && (size_t)index < lengthArray(*arr)) {
                    value = getArray(*arr, (size_t)index);
                    removeArray(*arr, (size_t)index);
                    cout << "-> " << value << endl; changed = true;
                } else cout << "No" << endl;
                break;
            }
            case commandType::MREMOVE: {
                Array* arr = fetchArray(dsName);
                if (in >> value) {
                    bool found = false;
                    for (size_t i = 0; i < lengthArray(*arr); ++i) {
                        if (getArray(*arr, i) == value) {
                            removeArray(*arr, i);
                            found = true;
                            break;
                        }
                    }
                    if (found) { cout << "-> " << value << endl; changed = true; }
                    else cout << "No" << endl;
                } else cout << "No" << endl;
                break;
            }
            case commandType::MSIZE: {
                Array* arr = fetchArray(dsName);
                cout << "-> " << lengthArray(*arr) << endl;
                break;
            }

            // ==================== ОДНОСВЯЗНЫЙ СПИСОК (SL..) ====================
            case commandType::SLPUSHBACK: {
                SingleList* slist = fetchSingleList(dsName);
                if (in >> value) { push_backSList(*slist, value); cout << "-> " << value << endl; changed = true; }
                else cout << "No" << endl;
                break;
            }
            case commandType::SLPUSHFRONT: {
                SingleList* slist = fetchSingleList(dsName);
                if (in >> value) { push_frontSList(*slist, value); cout << "-> " << value << endl; changed = true; }
                else cout << "No" << endl;
                break;
            }
            case commandType::SLPUSHAFTER: {
                SingleList* slist = fetchSingleList(dsName);
                if (in >> value >> target) {
                    if (getSList(*slist, target)) {
                        push_afterSList(*slist, value, target);
                        cout << "-> " << value << endl; changed = true;
                    } else cout << "No" << endl;
                } else cout << "No" << endl;
                break;
            }
            case commandType::SLPUSHBEFORE: {
                SingleList* slist = fetchSingleList(dsName);
                if (in >> value >> target) {
                    if (getSList(*slist, target)) {
                        push_beforeSList(*slist, value, target);
                        cout << "-> " << value << endl; changed = true;
                    } else cout << "No" << endl;
                } else cout << "No" << endl;
                break;
            }
            case commandType::SLINSERT: {
                // вставка после узла с данным значением (аналог PUSHAFTER)
                SingleList* slist = fetchSingleList(dsName);
                if (in >> value >> target) {
                    if (getSList(*slist, target)) {
                        push_afterSList(*slist, value, target);
                        cout << "-> " << value << endl; changed = true;
                    } else cout << "No" << endl;
                } else cout << "No" << endl;
                break;
            }
            case commandType::SLSET: {
                // найти узел с data==target, заменить на value
                SingleList* slist = fetchSingleList(dsName);
                if (in >> value >> target) {
                    SNode* n = slist->head;
                    while (n && n->data != target) n = n->next;
                    if (n) { n->data = value; cout << "-> " << value << endl; changed = true; }
                    else cout << "No" << endl;
                } else cout << "No" << endl;
                break;
            }
            case commandType::SLGET: {
                SingleList* slist = fetchSingleList(dsName);
                if (in >> value) {
                    if (getSList(*slist, value)) cout << "-> " << value << endl;
                    else cout << "No" << endl;
                } else cout << "No" << endl;
                break;
            }
            case commandType::SLREMOVE: {
                SingleList* slist = fetchSingleList(dsName);
                if (in >> value) {
                    if (getSList(*slist, value)) {
                        deleteByValueSList(*slist, value);
                        cout << "-> " << value << endl; changed = true;
                    } else cout << "No" << endl;
                } else cout << "No" << endl;
                break;
            }
            case commandType::SLSIZE: {
                SingleList* slist = fetchSingleList(dsName);
                int count = 0;
                for (SNode* n = slist->head; n; n = n->next) count++;
                cout << "-> " << count << endl;
                break;
            }
            case commandType::SLPOPFRONT: {
                SingleList* slist = fetchSingleList(dsName);
                if (slist->head) {
                    out = slist->head->data;
                    pop_frontSList(*slist);
                    cout << "-> " << out << endl; changed = true;
                } else cout << "No" << endl;
                break;
            }
            case commandType::SLPOPBACK: {
                SingleList* slist = fetchSingleList(dsName);
                if (slist->head) {
                    SNode* n = slist->head; while (n->next) n = n->next;
                    out = n->data;
                    pop_backSList(*slist);
                    cout << "-> " << out << endl; changed = true;
                } else cout << "No" << endl;
                break;
            }
            case commandType::SLPOPAFTER: {
                SingleList* slist = fetchSingleList(dsName);
                if (in >> target) {
                    SNode* n = slist->head; while (n && n->data != target) n = n->next;
                    if (n && n->next) {
                        out = n->next->data;
                        pop_afterSList(*slist, target);
                        cout << "-> " << out << endl; changed = true;
                    } else cout << "No" << endl;
                } else cout << "No" << endl;
                break;
            }
            case commandType::SLPOPBEFORE: {
                SingleList* slist = fetchSingleList(dsName);
                if (in >> target) {
                    SNode* n = slist->head;
                    SNode* prev = nullptr;
                    while (n && n->data != target) { prev = n; n = n->next; }
                    if (n && prev) {
                        out = prev->data;
                        pop_beforeSList(*slist, target);
                        cout << "-> " << out << endl; changed = true;
                    } else cout << "No" << endl;
                } else cout << "No" << endl;
                break;
            }

            // ==================== ДВУСВЯЗНЫЙ СПИСОК (DL..) ====================
            case commandType::DLPUSHBACK: {
                DoubleList* dlist = fetchDoubleList(dsName);
                if (in >> value) { push_backDList(*dlist, value); cout << "-> " << value << endl; changed = true; }
                else cout << "No" << endl;
                break;
            }
            case commandType::DLPUSHFRONT: {
                DoubleList* dlist = fetchDoubleList(dsName);
                if (in >> value) { push_frontDList(*dlist, value); cout << "-> " << value << endl; changed = true; }
                else cout << "No" << endl;
                break;
            }
            case commandType::DLPUSHAFTER: {
                DoubleList* dlist = fetchDoubleList(dsName);
                if (in >> value >> target) {
                    DNode* n = dlist->head; while (n && n->data != target) n = n->next;
                    if (n) { push_afterDList(*dlist, value, target); cout << "-> " << value << endl; changed = true; }
                    else cout << "No" << endl;
                } else cout << "No" << endl;
                break;
            }
            case commandType::DLPUSHBEFORE: {
                DoubleList* dlist = fetchDoubleList(dsName);
                if (in >> value >> target) {
                    DNode* n = dlist->head; while (n && n->data != target) n = n->next;
                    if (n) { push_beforeDList(*dlist, value, target); cout << "-> " << value << endl; changed = true; }
                    else cout << "No" << endl;
                } else cout << "No" << endl;
                break;
            }
            case commandType::DLINSERT: {
                // вставка после узла с данным значением (аналог PUSHAFTER)
                DoubleList* dlist = fetchDoubleList(dsName);
                if (in >> value >> target) {
                    DNode* n = dlist->head; while (n && n->data != target) n = n->next;
                    if (n) { push_afterDList(*dlist, value, target); cout << "-> " << value << endl; changed = true; }
                    else cout << "No" << endl;
                } else cout << "No" << endl;
                break;
            }
            case commandType::DLSET: {
                // заменить значение узла по индексу
                DoubleList* dlist = fetchDoubleList(dsName);
                if (in >> value >> index && index >= 0) {
                    DNode* n = dlist->head;
                    int i = 0;
                    while (n && i < index) { n = n->next; i++; }
                    if (n) { n->data = value; cout << "-> " << value << endl; changed = true; }
                    else cout << "No" << endl;
                } else cout << "No" << endl;
                break;
            }
            case commandType::DLGET: {
                DoubleList* dlist = fetchDoubleList(dsName);
                if (in >> index && index >= 0) {
                    DNode* n = dlist->head;
                    int i = 0;
                    while (n && i < index) { n = n->next; i++; }
                    if (n) cout << "-> " << getByIndexDList(*dlist, (size_t)index) << endl;
                    else cout << "No" << endl;
                } else cout << "No" << endl;
                break;
            }
            case commandType::DLREMOVE: {
                DoubleList* dlist = fetchDoubleList(dsName);
                if (in >> value) {
                    DNode* n = dlist->head; while (n && n->data != value) n = n->next;
                    if (n) {
                        deleteByValueDList(*dlist, value);
                        cout << "-> " << value << endl; changed = true;
                    } else cout << "No" << endl;
                } else cout << "No" << endl;
                break;
            }
            case commandType::DLSIZE: {
                DoubleList* dlist = fetchDoubleList(dsName);
                int count = 0;
                for (DNode* n = dlist->head; n; n = n->next) count++;
                cout << "-> " << count << endl;
                break;
            }
            case commandType::DLPOPFRONT: {
                DoubleList* dlist = fetchDoubleList(dsName);
                if (dlist->head) {
                    out = dlist->head->data;
                    pop_frontDList(*dlist);
                    cout << "-> " << out << endl; changed = true;
                } else cout << "No" << endl;
                break;
            }
            case commandType::DLPOPBACK: {
                DoubleList* dlist = fetchDoubleList(dsName);
                if (dlist->tail) {
                    out = dlist->tail->data;
                    pop_backDList(*dlist);
                    cout << "-> " << out << endl; changed = true;
                } else cout << "No" << endl;
                break;
            }
            case commandType::DLPOPAFTER: {
                DoubleList* dlist = fetchDoubleList(dsName);
                if (in >> target) {
                    DNode* n = dlist->head; while (n && n->data != target) n = n->next;
                    if (n && n->next) {
                        out = n->next->data;
                        pop_afterDList(*dlist, target);
                        cout << "-> " << out << endl; changed = true;
                    } else cout << "No" << endl;
                } else cout << "No" << endl;
                break;
            }
            case commandType::DLPOPBEFORE: {
                DoubleList* dlist = fetchDoubleList(dsName);
                if (in >> target) {
                    DNode* n = dlist->head; while (n && n->data != target) n = n->next;
                    if (n && n->prev) {
                        out = n->prev->data;
                        pop_beforeDList(*dlist, target);
                        cout << "-> " << out << endl; changed = true;
                    } else cout << "No" << endl;
                } else cout << "No" << endl;
                break;
            }

            // ======================= СТЕК =======================
            case commandType::SPUSH: {
                Stack* stack = fetchStack(dsName);
                if (in >> value) {
                    try {
                        int v = stoi(value);
                        pushStack(stack, v);
                        cout << "-> " << v << endl; changed = true;
                    } catch (...) { cout << "No" << endl; }
                } else cout << "No" << endl;
                break;
            }
            case commandType::SPOP: {
                Stack* stack = fetchStack(dsName);
                if (!isEmptyStack(stack)) {
                    int v = stack->head->value;
                    popStack(*stack);
                    cout << "-> " << v << endl; changed = true;
                } else cout << "No" << endl;
                break;
            }

            // ======================= ОЧЕРЕДЬ =======================
            case commandType::QPUSH: {
                Queue* queue = fetchQueue(dsName);
                if (in >> value) {
                    try {
                        int v = stoi(value);
                        pushQueue(queue, v);
                        cout << "-> " << v << endl; changed = true;
                    } catch (...) { cout << "No" << endl; }
                } else cout << "No" << endl;
                break;
            }
            case commandType::QPOP: {
                Queue* queue = fetchQueue(dsName);
                if (!isEmptyQueue(queue)) {
                    popQueue(queue, out);
                    cout << "-> " << out << endl; changed = true;
                } else cout << "No" << endl;
                break;
            }

            // ======================= ДЕРЕВО =======================
            case commandType::TADD: {
                TreeNode** tree = fetchTree(dsName);
                if (in >> value) {
                    try {
                        int v = stoi(value);
                        AddTree(*tree, v);
                        cout << "-> " << v << endl; changed = true;
                    } catch (...) { cout << "No" << endl; }
                } else cout << "No" << endl;
                break;
            }
            case commandType::TFIND: {
                TreeNode** tree = fetchTree(dsName);
                if (in >> value) {
                    try {
                        int v = stoi(value);
                        if (searchTree(*tree, v)) cout << "-> " << v << endl;
                        else cout << "No" << endl;
                    } catch (...) { cout << "No" << endl; }
                } else cout << "No" << endl;
                break;
            }
            case commandType::TDEL: {
                TreeNode** tree = fetchTree(dsName);
                if (in >> value) {
                    try {
                        int v = stoi(value);
                        if (searchTree(*tree, v)) {
                            *tree = removeTree(*tree, v);
                            cout << "-> " << v << endl; changed = true;
                        } else cout << "No" << endl;
                    } catch (...) { cout << "No" << endl; }
                } else cout << "No" << endl;
                break;
            }

            // ======================= ВЫВОД =======================
            case commandType::PRINT: {
                string targetName;
                if (!(in >> targetName)) { cout << "No" << endl; break; }

                if (dsName == "array")      { Array* arr = fetchArray(targetName); printArray(*arr); }
                else if (dsName == "slist") { SingleList* slist = fetchSingleList(targetName); printSList(*slist); }
                else if (dsName == "dlist") { DoubleList* dlist = fetchDoubleList(targetName); printDList(*dlist); }
                else if (dsName == "stack") { Stack* stack = fetchStack(targetName); printStack(*stack); }
                else if (dsName == "queue") { Queue* queue = fetchQueue(targetName); printQueue(*queue); }
                else if (dsName == "tree")  { TreeNode** tree = fetchTree(targetName); PrintTree(*tree); }
                else cout << "No" << endl;
                break;
            }

            default:
                cout << "Unknown command. HELP — list of commands" << endl;
        }

        if (changed) SaveAll();
    }

    SaveAll();
    freeEverything();

    cout << "Done." << endl;
    return 0;
}