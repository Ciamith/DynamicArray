#include "DynamicArray.h"
#include <iostream>
#include <stdexcept>

using namespace std;

DynamicArray::DynamicArray(int s) {
    size = s;
    capacity = s;
    if (capacity > 0) {
        data = new int[capacity];
        for (int i = 0; i < size; i++) {
            data[i] = 0;
        }
    }
    else {
        data = nullptr;
    }
}

DynamicArray::DynamicArray(const DynamicArray& other) {
    size = other.size;
    capacity = other.capacity;
    if (capacity > 0) {
        data = new int[capacity];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
    else {
        data = nullptr;
    }
}

DynamicArray::~DynamicArray() {
    delete[] data;
}

void DynamicArray::print() {
    cout << "[ ";
    for (int i = 0; i < size; i++) {
        cout << data[i];
        if (i < size - 1) cout << ", ";
    }
    cout << " ]" << endl;
}

int DynamicArray::get(int index) {
    if (index < 0 || index >= size) {
        throw out_of_range("Index invalide");
    }
    return data[index];
}

void DynamicArray::set(int index, int value) {
    if (index < 0 || index >= size) {
        throw out_of_range("Index invalide");
    }
    if (value < -100 || value > 100) {
        throw invalid_argument("Valeur doit etre entre -100 et 100");
    }
    data[index] = value;
}

void DynamicArray::push_back(int value) {
    if (value < -100 || value > 100) {
        throw invalid_argument("Valeur doit etre entre -100 et 100");
    }

    if (size == capacity) {
        int new_capacity = (capacity == 0) ? 1 : capacity * 2;
        int* new_data = new int[new_capacity];

        for (int i = 0; i < size; i++) {
            new_data[i] = data[i];
        }

        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

    data[size] = value;
    size++;
}

void DynamicArray::add(const DynamicArray& other) {
    for (int i = 0; i < size; i++) {
        int val_other = 0;
        if (i < other.size) {
            val_other = other.data[i];
        }
        data[i] += val_other;
    }
}

void DynamicArray::sub(const DynamicArray& other) {
    for (int i = 0; i < size; i++) {
        int val_other = 0;
        if (i < other.size) {
            val_other = other.data[i];
        }
        data[i] -= val_other;
    }
}