#ifndef ARRAY_H
#define ARRAY_H
#include <iostream>

struct Array{
    int* data;
    size_t size;
    size_t capacity;
};

Array createArray();
void killArray(Array& arr);
size_t lengthArray(const Array& arr);
int getArray(const Array& arr, size_t index);
void setArray(Array& arr, size_t index, int value);
void push_backArray(Array& arr, int value);
void insertArray(Array& arr, size_t index, int value);
void removeArray(Array& arr, size_t index);
void printArray(const Array& arr);

#endif