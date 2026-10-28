#ifndef ARRAY_H
#define ARRAY_H
#include <iostream>

struct Array{
    std::string* data;
    size_t size;
    size_t capacity;
};

void killArray(Array& arr);
size_t lengthArray(const Array& arr);
std::string getArray(const Array& arr, size_t index);
void setArray(Array& arr, size_t index, std::string value);
void push_backArray(Array& arr, std::string value);
void insertArray(Array& arr, size_t index, std::string value);
void deleteArray(Array& arr, std::string value);
void removeArray(Array& arr, size_t index);
void printArray(const Array& arr);

#endif