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

    void checkValue(const T& value) {
        if constexpr (std::is_integral_v<T>) {
            if (value > 100 || value < -100) {
                throw std::invalid_argument("Valeur hors de [-100, 100]");
            }
        }
    }

public:
    // ===== Classe proxy pour operator[] =====
    // Permet que arr[i] = value passe par set() avec verification
    class Reference {
    private:
        DynamicArray& arr;
        int index;
    public:
        Reference(DynamicArray& a, int i) : arr(a), index(i) {}

        operator T() const {
            return arr.get(index);
        }

        Reference& operator=(const T& value) {
            arr.set(index, value);
            return *this;
        }
    };

    // ===== Constructeur =====
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

    // ===== Methodes de base =====
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

    // ===== Задание 1 : operator[] avec proxy =====
    Reference operator[](int index) {
        return Reference(*this, index);
    }

    const T& operator[](int index) const {
        return get(index);
    }

    // ===== Задание 2 : operateurs de comparaison =====
    bool operator==(const DynamicArray& other) const {
        if (size != other.size) return false;
        for (int i = 0; i < size; i++) {
            if (data[i] != other.data[i]) return false;
        }
        return true;
    }

    bool operator!=(const DynamicArray& other) const {
        return !(*this == other);
    }

    // ===== Задание 3 : operateurs composes =====
    // Version tableau : element par element, manquants = 0, taille ne change pas
    DynamicArray& operator+=(const DynamicArray& other) {
        for (int i = 0; i < size; i++) {
            T otherVal = (i < other.size) ? other.data[i] : T();
            checkValue(data[i] + otherVal);
            data[i] = data[i] + otherVal;
        }
        return *this;
    }

    DynamicArray& operator-=(const DynamicArray& other) {
        for (int i = 0; i < size; i++) {
            T otherVal = (i < other.size) ? other.data[i] : T();
            checkValue(data[i] - otherVal);
            data[i] = data[i] - otherVal;
        }
        return *this;
    }

    // Version scalaire : ajouter/soustraire un nombre a tous les elements
    DynamicArray& operator+=(const T& value) {
        checkValue(value);
        for (int i = 0; i < size; i++) {
            data[i] = data[i] + value;
        }
        return *this;
    }

    DynamicArray& operator-=(const T& value) {
        checkValue(value);
        for (int i = 0; i < size; i++) {
            data[i] = data[i] - value;
        }
        return *this;
    }

    // ===== Задание 4 : iterateurs begin() et end() =====
    T* begin() { return data; }
    T* end() { return data + size; }

    const T* begin() const { return data; }
    const T* end() const { return data + size; }

    // ===== Affichage =====
    friend std::ostream& operator<<(std::ostream& os, const DynamicArray<T>& arr) {
        os << "[ ";
        for (int i = 0; i < arr.size; i++) {
            os << arr.data[i];
            if (i < arr.size - 1) os << " ";
        }
        os << "]";
        return os;
    }

    int getSize() const { return size; }
};