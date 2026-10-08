#include "array.h"
using namespace std;

Array createArray() {
    Array arr;
    arr.data = nullptr;
    arr.size = 0;
    arr.capacity = 0;
    return arr;
}

void killArray(Array& arr) {
    delete[] arr.data;
    arr.data = nullptr;
    arr.size = 0;
    arr.capacity = 0;
}

size_t lengthArray(const Array& arr) {
    return arr.size;
}

int getArray(const Array& arr, size_t index) {
    if (index >= arr.size) {
        throw out_of_range("ОШИБКА: (MGET) индекс вне массива!!!");
    }
    return arr.data[index];
}

void setArray(Array& arr, size_t index, int value) {
    if (index >= arr.size) {
        throw out_of_range("ОШИБКА: (MSET) индекс вне массива!!!");
    }
    arr.data[index] = value;
}

void expandCapacity(Array& arr, size_t newCapacity) {
    if (newCapacity <= arr.capacity) return;

    int* newData = new int[newCapacity];
    for (size_t i = 0; i < arr.size; ++i) {
        newData[i] = arr.data[i];
    }
    delete[] arr.data;
    arr.data     = newData;
    arr.capacity = newCapacity;
}

void push_backArray(Array& arr, int value) {
    if (arr.size == arr.capacity) {
        expandCapacity(arr, arr.capacity == 0 ? 1 : arr.capacity * 2);
    }
    arr.data[arr.size] = value;
    ++arr.size;
}

void insertArray(Array& arr, size_t index, int value) {
    if (index >= arr.size ) {
        throw out_of_range("ОШИБКА: (MINSERT) индекс вне массива!!!");
    }

    if (arr.size >= arr.capacity) {
        expandCapacity(arr, arr.capacity == 0 ? 1 : arr.capacity * 2);
    }

    for (size_t i = arr.size; i > index; --i) {
        arr.data[i] = arr.data[i - 1];
    }

    arr.data[index] = value;
    ++arr.data;
}

void removeArray(Array& arr, size_t index) {
    if (index >= arr.size) {
        throw out_of_range("ОШИБКА: (MREMOVE) индекс вне массива!!!");
    }

    for (size_t i = index; i < arr.size - 1; ++i) {
        arr.data[i] = arr.data[i + 1];
    }

    --arr.size;
}

void printArray(const Array& arr) {
    if (arr.size == 0) {
        cout << "Массив пуст." << endl;
        return;
    }
    cout << "[ ";
    for (size_t i = 0; i < arr.size; ++i) {
        cout << arr.data[i];
        if (i < arr.size - 1) cout << ", ";
    }
    cout << " ]" << endl;
}