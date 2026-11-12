#include "DynamicArray.h"

DynamicArray::DynamicArray(int n) {
    if (n <= 0) {
        throw std::invalid_argument("Taille doit etre positive");
    }
    size = n;
    capacity = n;
    data = new int[capacity];
    for (int i = 0; i < size; i++) {
        data[i] = 0;
    }
}

DynamicArray::~DynamicArray() {
    delete[] data;
}

DynamicArray::DynamicArray(const DynamicArray& other) {
    size = other.size;
    capacity = other.capacity;
    data = new int[capacity];
    for (int i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
}

DynamicArray& DynamicArray::operator=(const DynamicArray& other) {
    if (this != &other) {
        delete[] data;
        size = other.size;
        capacity = other.capacity;
        data = new int[capacity];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

void DynamicArray::push_back(int value) {
    if (value < -100 || value > 100) {
        throw std::invalid_argument("Valeur hors de [-100, 100]");
    }
    if (size >= capacity) {
        int newCap = capacity * 2;
        int* newData = new int[newCap];
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCap;
    }
    data[size] = value;
    size++;
}

int DynamicArray::get(int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index hors limites");
    }
    return data[index];
}

void DynamicArray::set(int index, int value) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index hors limites");
    }
    if (value < -100 || value > 100) {
        throw std::invalid_argument("Valeur hors de [-100, 100]");
    }
    data[index] = value;
}

DynamicArray DynamicArray::add(const DynamicArray& other) const {
    int minSize = size < other.size ? size : other.size;
    DynamicArray result(minSize);
    for (int i = 0; i < minSize; i++) {
        result.data[i] = get(i) + other.get(i);
    }
    return result;
}

DynamicArray DynamicArray::sub(const DynamicArray& other) const {
    int minSize = size < other.size ? size : other.size;
    DynamicArray result(minSize);
    for (int i = 0; i < minSize; i++) {
        result.data[i] = get(i) - other.get(i);
    }
    return result;
}

void DynamicArray::print() const {
    std::cout << "[ ";
    for (int i = 0; i < size; i++) {
        std::cout << data[i] << " ";
    }
    std::cout << "]" << std::endl;
}

int DynamicArray::getSize() const {
    return size;
}