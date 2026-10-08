#include "flist.h"
using namespace std;

void createSingleList(SingleList& SList) {
    SList.head = nullptr;
}

void killSingleList(SingleList& SList) {
    while (SList.head != nullptr) {
        pop_frontSList(SList);
    }
}

void push_frontSList(SingleList& SList, int value) {
    SNode* newNode = new SNode;
    newNode->data = value;
    newNode->next = SList.head;
    SList.head = newNode;
}

void push_afterSList(SingleList& SList, int value, int target) {
    SNode* current = SList.head;
    while (current != nullptr && current->data != target) {
        current = current->next;
    }
    if (current != nullptr) {
        SNode* newNode = new SNode;
        newNode->data = value;
        newNode->next = current->next;
        current->next = newNode;
    }
}

void push_beforeSList(SingleList& SList, int value, int target) {
    if (SList.head == nullptr) return;
    if (SList.head->data == target) {
        push_frontSList(SList, value);
        return;
    }
    SNode* current = SList.head;
    while (current->next != nullptr && current->next->data != target) {
        current = current->next;
    }
    if (current->next != nullptr) {
        SNode* newNode = new SNode;
        newNode->data = value;
        newNode->next = current->next;
        current->next = newNode;
    }
}

void pop_frontSList(SingleList& SList) {
    if (SList.head == nullptr) return;
    SNode* temp = SList.head;
    SList.head = SList.head->next;
    delete temp;
}

void pop_backSList(SingleList& SList) {
    if (SList.head == nullptr) return;
    if (SList.head->next == nullptr) {
        pop_frontSList(SList);
        return;
    }
    SNode* current = SList.head;
    while (current->next->next != nullptr) {
        current = current->next;
    }
    delete current->next;
    current->next = nullptr;
}

void pop_afterSList(SingleList& SList, int target) {
    SNode* current = SList.head;
    while (current != nullptr && current->data != target) {
        current = current->next;
    }
    if (current != nullptr && current->next != nullptr) {
        SNode* temp = current->next;
        current->next = temp->next;
        delete temp;
    }
}

void pop_beforeSList(SingleList& SList, int target) {
    if (SList.head == nullptr || SList.head->next == nullptr || SList.head->data == target) return;
    if (SList.head->next->data == target) {
        pop_frontSList(SList);
        return;
    }
    SNode* current = SList.head;
    while (current->next->next != nullptr && current->next->next->data != target) {
        current = current->next;
    }
    if (current->next->next != nullptr) {
        SNode* temp = current->next;
        current->next = temp->next;
        delete temp;
    }
}

void deleteByValueSList(SingleList& SList, int target) {
    if (SList.head == nullptr) return;
    if (SList.head->data == target) {
        pop_frontSList(SList);
        return;
    }
    SNode* current = SList.head;
    while (current->next != nullptr && current->next->data != target) {
        current = current->next;
    }
    if (current->next != nullptr) {
        SNode* temp = current->next;
        current->next = temp->next;
        delete temp;
    }
}

