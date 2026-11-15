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
    // ===== Proxy pour operator[] (Partie 4) =====
    class Reference {
    private:
        DynamicArray& arr;
        int index;
    public:
        Reference(DynamicArray& a, int i) : arr(a), index(i) {}
        operator T() const { return arr.get(index); }
        Reference& operator=(const T& value) { arr.set(index, value); return *this; }
    };

    // ===== Constructeur =====
    DynamicArray(int n = 4) {
        if (n <= 0) throw std::invalid_argument("La taille doit etre positive");
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

    // ===== REGLE DE 5, 1/5 : Destructeur =====
    ~DynamicArray() {
        std::cout << "[DTOR] libere data@" << (void*)data << " taille=" << size << std::endl;
        delete[] data;
    }

    // ===== REGLE DE 5, 2/5 : Constructeur de copie =====
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
        std::cout << "[COPY ctor] taille=" << size << std::endl;
    }

    // ===== REGLE DE 5, 3/5 (Задание 1) : operator= de copie =====
    DynamicArray& operator=(const DynamicArray& other) {
        if (this == &other) return *this;          // protection auto-affectation
        delete[] data;                             // pas de fuite (libere l'ancien)
        size = other.size;
        capacity = other.capacity;
        try {
            data = new T[capacity];
            for (int i = 0; i < size; i++) data[i] = other.data[i];
        }
        catch (const std::bad_alloc&) {
            data = nullptr; size = 0; capacity = 0; // etat sur, pas de double-free
            throw;
        }
        std::cout << "[COPY =] taille=" << size << std::endl;
        return *this;                              // chainage a = b = c
    }

    // ===== REGLE DE 5, 4/5 (Задание 2) : Move-constructeur =====
    DynamicArray(DynamicArray&& other) noexcept {
        data = other.data;            // voler le pointeur
        size = other.size;
        capacity = other.capacity;
        other.data = nullptr;         // neutraliser la source
        other.size = 0;
        other.capacity = 0;
        std::cout << "[MOVE ctor] taille=" << size << std::endl;
    }

    // ===== REGLE DE 5, 5/5 (Задание 3) : Move-operator= =====
    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this == &other) return *this;   // auto-affectation
        delete[] data;                      // liberer SES donnees
        data = other.data;                  // voler
        size = other.size;
        capacity = other.capacity;
        other.data = nullptr;               // neutraliser source
        other.size = 0;
        other.capacity = 0;
        std::cout << "[MOVE =] taille=" << size << std::endl;
        return *this;
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
        if (index < 0 || index >= size) throw std::out_of_range("Index hors limites dans get()");
        return data[index];
    }

    void set(int index, const T& value) {
        if (index < 0 || index >= size) throw std::out_of_range("Index hors limites dans set()");
        checkValue(value);
        data[index] = value;
    }

    void add(const DynamicArray& other) {
        for (int i = 0; i < size; i++) {
            T val = get(i);
            T otherVal = (i < other.size) ? other.get(i) : T();
            set(i, val + otherVal);
        }
    }

    void sub(const DynamicArray& other) {
        for (int i = 0; i < size; i++) {
            T val = get(i);
            T otherVal = (i < other.size) ? other.get(i) : T();
            set(i, val - otherVal);
        }
    }

    // ===== Partie 4 =====
    Reference operator[](int index) { return Reference(*this, index); }
    const T& operator[](int index) const { return get(index); }

    bool operator==(const DynamicArray& other) const {
        if (size != other.size) return false;
        for (int i = 0; i < size; i++) if (data[i] != other.data[i]) return false;
        return true;
    }
    bool operator!=(const DynamicArray& other) const { return !(*this == other); }

    DynamicArray& operator+=(const DynamicArray& other) {
        for (int i = 0; i < size; i++) {
            T otherVal = (i < other.size) ? other.get(i) : T();
            T newVal = data[i] + otherVal;
            checkValue(newVal);
            data[i] = newVal;
        }
        return *this;
    }
    DynamicArray& operator-=(const DynamicArray& other) {
        for (int i = 0; i < size; i++) {
            T otherVal = (i < other.size) ? other.get(i) : T();
            T newVal = data[i] - otherVal;
            checkValue(newVal);
            data[i] = newVal;
        }
        return *this;
    }
    DynamicArray& operator+=(const T& value) {
        for (int i = 0; i < size; i++) {
            T newVal = data[i] + value;
            checkValue(newVal);
            data[i] = newVal;
        }
        return *this;
    }
    DynamicArray& operator-=(const T& value) {
        for (int i = 0; i < size; i++) {
            T newVal = data[i] - value;
            checkValue(newVal);
            data[i] = newVal;
        }
        return *this;
    }

    T* begin() { return data; }
    T* end() { return data + size; }
    const T* begin() const { return data; }
    const T* end() const { return data + size; }

    friend std::ostream& operator<<(std::ostream& os, const DynamicArray<T>& arr) {
        os << "[ ";
        for (int i = 0; i < arr.size; i++) {
            os << arr.data[i];
            if (i < arr.size - 1) os << " ";
        }
        os << "]";
        return os;
    }

    double distance(const DynamicArray<T>& other) const {
        if constexpr (!std::is_arithmetic_v<T>) {
            throw std::bad_typeid();
        }
        else {
            if (size != other.size) throw std::invalid_argument("Les tableaux doivent avoir la meme taille");
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