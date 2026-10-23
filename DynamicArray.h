#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

class DynamicArray {
private:
    int* data;
    int size;
    int capacity;

public:
    DynamicArray(int s);
    DynamicArray(const DynamicArray& other);
    ~DynamicArray();

    void print();
    int get(int index);
    void set(int index, int value);
    void push_back(int value);
    void add(const DynamicArray& other);
    void sub(const DynamicArray& other);
};

#endif