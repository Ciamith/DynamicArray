#pragma once
#include <iostream>
#include <stdexcept>

class DynamicArray {
private:
    int* data;
    int size;
    int capacity;

public:
    DynamicArray(int n = 4);
    ~DynamicArray();
    DynamicArray(const DynamicArray& other);
    DynamicArray& operator=(const DynamicArray& other);

    void push_back(int value);
    int get(int index) const;
    void set(int index, int value);
    DynamicArray add(const DynamicArray& other) const;
    DynamicArray sub(const DynamicArray& other) const;
    void print() const;
    int getSize() const;
};