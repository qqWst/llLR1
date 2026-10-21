#ifndef DOUBLELIST_H
#define DOUBLELIST_H
#include <iostream>

struct DNode{
    std::string data;
    DNode* next;
    DNode* prev;
};

struct DoubleList{
    DNode* head;
    DNode* tail;
};

void createDList(DoubleList& DList);
void killDList(DoubleList& DList);
void push_frontDList(DoubleList& DList, std::string value);
void push_backDList(DoubleList& DList, std::string value);
void push_afterDList(DoubleList& DList, std::string value, std::string target);
void push_beforeDList(DoubleList& DList, std::string value, std::string target);
void pop_frontDList(DoubleList& DList);
void pop_backDList(DoubleList& DList);
void pop_afterDList(DoubleList& DList, std::string target);
void pop_beforeDList(DoubleList& DList, std::string target);
void deleteByValueDList(DoubleList& DList, std::string target);
std::string getByIndexDList(const DoubleList& DList, size_t index);
void printDList(const DoubleList& DList);

#endif