#pragma once
#include <iostream>
#include <stdexcept>

class DynamicArray {
private:
    int* data;
    int size;
    int capacity;

public:
    // Constructeur corrigé (size = n)
    DynamicArray(int n = 4) {
        if (n <= 0) {
            throw std::invalid_argument("La taille doit etre positive");
        }
        size = n;
        capacity = n;
        try {
            data = new int[capacity];
            for (int i = 0; i < size; i++) {
                data[i] = 0;
            }
        }
        catch (const std::bad_alloc&) {
            throw std::bad_alloc();
        }
    }

    ~DynamicArray() {
        delete[] data;
    }

    // Constructeur de copie
    DynamicArray(const DynamicArray& other) {
        size = other.size;
        capacity = other.capacity;
        try {
            data = new int[capacity];
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        catch (const std::bad_alloc&) {
            throw std::bad_alloc();
        }
    }

    // get() avec out_of_range
    int get(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index hors limites dans get()");
        }
        return data[index];
    }

    // set() avec out_of_range et invalid_argument
    void set(int index, int value) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index hors limites dans set()");
        }
        if (value < -100 || value > 100) {
            throw std::invalid_argument("Valeur hors de [-100, 100]");
        }
        data[index] = value;
    }

    void push_back(int value) {
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

    // add() utilisant get() et set() pour hériter des exceptions out_of_range
    void add(const DynamicArray& other) {
        for (int i = 0; i < size; i++) {
            int val = get(i);
            int otherVal = 0;
            if (i < other.size) {
                otherVal = other.get(i); // Peut lancer out_of_range
            }
            set(i, val + otherVal);      // Peut lancer out_of_range et invalid_argument
        }
    }

    // sub() utilisant get() et set()
    void sub(const DynamicArray& other) {
        for (int i = 0; i < size; i++) {
            int val = get(i);
            int otherVal = 0;
            if (i < other.size) {
                otherVal = other.get(i); // Peut lancer out_of_range
            }
            set(i, val - otherVal);      // Peut lancer out_of_range et invalid_argument
        }
    }

    void print() const {
        std::cout << "[ ";
        for (int i = 0; i < size; i++) {
            std::cout << data[i] << (i < size - 1 ? " " : "");
        }
        std::cout << " ]" << std::endl;
    }

    int getSize() const { return size; }
};