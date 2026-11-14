#pragma once
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <typeinfo>
#include <cmath>

template <typename T>
class DynamicArray {
private:
    T* data;
    int size;
    int capacity;

    // Tache 1 : verification separee pour les entiers
    void checkValue(const T& value) {
        if constexpr (std::is_integral_v<T>) {
            if (value > 100 || value < -100) {
                throw std::invalid_argument("Valeur hors de [-100, 100]");
            }
        }
    }

public:
    DynamicArray(int n = 4) {
        if (n <= 0) {
            throw std::invalid_argument("La taille doit etre positive");
        }
        size = n;
        capacity = n;
        try {
            data = new T[capacity];
            for (int i = 0; i < size; i++) data[i] = T();
        }
        catch (const std::bad_alloc&) {
            throw std::bad_alloc();
        }
    }

    ~DynamicArray() { delete[] data; }

    DynamicArray(const DynamicArray& other) {
        size = other.size;
        capacity = other.capacity;
        try {
            data = new T[capacity];
            for (int i = 0; i < size; i++) data[i] = other.data[i];
        }
        catch (const std::bad_alloc&) {
            throw std::bad_alloc();
        }
    }

    void push_back(const T& value) {
        checkValue(value);
        if (size >= capacity) {
            int newCap = capacity * 2;
            T* newData = new T[newCap];
            for (int i = 0; i < size; i++) newData[i] = data[i];
            delete[] data;
            data = newData;
            capacity = newCap;
        }
        data[size] = value;
        size++;
    }

    T get(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index hors limites");
        }
        return data[index];
    }

    void set(int index, const T& value) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index hors limites");
        }
        checkValue(value);
        data[index] = value;
    }

    DynamicArray add(const DynamicArray& other) const {
        int minSize = (size < other.size) ? size : other.size;
        DynamicArray result(minSize);
        for (int i = 0; i < minSize; i++)
            result.data[i] = get(i) + other.get(i);
        return result;
    }

    DynamicArray sub(const DynamicArray& other) const {
        int minSize = (size < other.size) ? size : other.size;
        DynamicArray result(minSize);
        for (int i = 0; i < minSize; i++)
            result.data[i] = get(i) - other.get(i);
        return result;
    }

    // Tache 2 : operateur de sortie <<
    friend std::ostream& operator<<(std::ostream& os, const DynamicArray<T>& arr) {
        os << "[ ";
        for (int i = 0; i < arr.size; i++) {
            os << arr.data[i];
            if (i < arr.size - 1) os << " ";
        }
        os << "]";
        return os;
    }

    // Tache 3 : distance euclidienne
    double distance(const DynamicArray<T>& other) const {
        if constexpr (!std::is_arithmetic_v<T>) {
            throw std::bad_typeid();
        }
        else {
            if (size != other.size) {
                throw std::invalid_argument("Les tableaux doivent avoir la meme taille");
            }
            double sum = 0.0;
            for (int i = 0; i < size; i++) {
                double diff = static_cast<double>(data[i]) - static_cast<double>(other.data[i]);
                sum += diff * diff;
            }
            return std::sqrt(sum);
        }
    }

    int getSize() const { return size; }
};