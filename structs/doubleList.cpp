#include "doubleList.h"
using namespace std;

void createDList(DoubleList& DList){
    DList.head = nullptr;
    DList.tail = nullptr;
}

void killDList(DoubleList& DList) {
    while (DList.head != nullptr) {
        pop_frontDList(DList);
    }
}

void push_frontDList(DoubleList& DList, string value) {
    DNode* newNode = new DNode{value, DList.head, nullptr};
    DList.head->prev = newNode;
    DList.head = newNode;
}

void push_backDList(DoubleList& DList, string value) {
    DNode* newNode = new DNode{value, nullptr, DList.tail};
    DList.tail->next = newNode;
    DList.tail = newNode;
}

void push_afterDList(DoubleList& DList, string value, string target) {
    DNode* current = DList.head;
    while (current != nullptr && current->data != target) {
        current = current->next;
    }
    if (current == nullptr) {
        throw out_of_range("ОШИБКА: (push_afterDList) target вне списка!");
    }
    DNode* newNode = new DNode{value, current->next, current};
    current->next = newNode;
    newNode->next->prev = newNode;
}

void push_beforeDList(DoubleList& DList, string value, string target) {
    DNode* current = DList.tail;
    while (current != nullptr && current->data != target) {
        current = current->prev;
    }
    if (current == nullptr) {
        throw out_of_range("ОШИБКА: (push_beforeDList) index вне списка!");
    }
    DNode* newNode = new DNode{value, current, current->prev};
    current->prev = newNode;
    newNode->prev->next = newNode;
}

void pop_frontDList(DoubleList& DList){
    if (DList.head == nullptr) return;
    DNode* temp = DList.head;
    DList.head = DList.head->next;
    delete temp;
}

void pop_backDList(DoubleList& DList) {
    if (DList.tail == nullptr) return;
    DNode* temp = DList.tail;
    DList.tail = DList.tail->prev;
    delete temp;
}

void pop_afterDList(DoubleList& DList, string target){
    DNode* current = DList.head;
    while (current != nullptr && current->data != target) {
        current = current->next;
    }
    if (current != nullptr && current->next != nullptr){
        DNode* temp = current->next;
        current->next = temp->next;
        delete temp;
        return;
    }
    if (current != nullptr && current->next == nullptr){
        return;
    }
    throw out_of_range("ОШИБКА: (popAfterDList) target вне списка!");
}

void pop_beforeDList(DoubleList& DList, string target){
    DNode* current = DList.tail;
    while (current != nullptr && current->data != target) {
        current = current->prev;
    }
    if (current != nullptr && current->prev != nullptr){
        DNode* temp = current->prev;
        current->prev = temp->prev;
        delete temp;
        return;
    }
    if (current != nullptr && current->prev == nullptr){
        return;
    }
    throw out_of_range("ОШИБКА: (popBeforeDList) target вне списка!");
}

void deleteByValueDList(DoubleList& DList, string target) {
    if (DList.head == nullptr) return;
    
    DNode* current = DList.head;
    while (current->next != nullptr && current->next->data != target) {
        current = current->next;
    }
    if (current == DList.head) {
        pop_frontDList(DList);
        return;
    }
    if (current == DList.tail) {
        pop_backDList(DList);
        return;
    }
    if (current->next != nullptr) {
        DNode* temp = current->next;
        current->next = temp->next;
        delete temp;
    }
}

string getByIndexDList(const DoubleList& DList, size_t index){
    if (!index) throw out_of_range("ОШИБКА: (getByIndexDList) index вне размера списка!");
    DNode* current = DList.head;
    size_t count = 0;
    while (current != nullptr) {
        if (count == index) return current->data;
        count++;
        current = current->next;
    }
    throw out_of_range("ОШИБКА: (getByIndexDList) index вне размера списка!");
}

void printDList(const DoubleList& DList) {
    if (DList.head == nullptr) {
        cout << "Двусвязный список пуст." << endl;
        return;
    }
    cout << "Двусвязный список: " << endl;
    DNode* current = DList.head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}