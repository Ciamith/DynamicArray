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

    // Vérification de la valeur (uniquement pour les types entiers)
    void checkValue(const T& value) {
        if constexpr (std::is_integral_v<T>) {
            if (value > 100 || value < -100) {
                throw std::invalid_argument("Valeur hors de [-100, 100]");
            }
        }
    }

public:
    // ===== PARTIE 4, TÂCHE 1 : Classe Proxy pour operator[] =====
    class Reference {
    private:
        DynamicArray& arr;
        int index;
    public:
        Reference(DynamicArray& a, int i) : arr(a), index(i) {}

        // Conversion implicite en T (pour la lecture : int x = arr[0];)
        operator T() const {
            return arr.get(index);
        }

        // Opérateur d'affectation (pour l'écriture : arr[0] = 5;)
        Reference& operator=(const T& value) {
            arr.set(index, value); // Passe par set() pour garantir la vérification
            return *this;
        }
    };

    // ===== Constructeurs et Destructeur =====
    DynamicArray(int n = 4) {
        if (n <= 0) {
            throw std::invalid_argument("La taille doit etre positive");
        }
        size = n;
        capacity = n;
        try {
            data = new T[capacity];
            for (int i = 0; i < size; i++) {
                data[i] = T();
            }
        }
        catch (const std::bad_alloc&) {
            throw std::bad_alloc();
        }
    }

    ~DynamicArray() {
        delete[] data;
    }

    DynamicArray(const DynamicArray& other) {
        size = other.size;
        capacity = other.capacity;
        try {
            data = new T[capacity];
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        catch (const std::bad_alloc&) {
            throw std::bad_alloc();
        }
    }

    // ===== Méthodes de base (Parties 1 & 2) =====
    T get(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index hors limites dans get()");
        }
        return data[index];
    }

    void set(int index, const T& value) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index hors limites dans set()");
        }
        checkValue(value);
        data[index] = value;
    }

    void push_back(const T& value) {
        checkValue(value);
        if (size >= capacity) {
            int newCap = capacity * 2;
            T* newData = new T[newCap];
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

    void add(const DynamicArray& other) {
        for (int i = 0; i < size; i++) {
            T val = get(i);
            T otherVal = (i < other.size) ? other.get(i) : T();
            set(i, val + otherVal); // Utilise set() pour hériter de out_of_range et invalid_argument
        }
    }

    void sub(const DynamicArray& other) {
        for (int i = 0; i < size; i++) {
            T val = get(i);
            T otherVal = (i < other.size) ? other.get(i) : T();
            set(i, val - otherVal); // Utilise set() pour hériter de out_of_range et invalid_argument
        }
    }

    // ===== PARTIE 4, TÂCHE 1 : operator[] =====
    Reference operator[](int index) {
        return Reference(*this, index);
    }

    const T& operator[](int index) const {
        return get(index);
    }

    // ===== PARTIE 4, TÂCHE 2 : Opérateurs de comparaison =====
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

    // ===== PARTIE 4, TÂCHE 3 : Opérateurs composés (Version Tableau) =====
    DynamicArray& operator+=(const DynamicArray& other) {
        for (int i = 0; i < size; i++) {
            T otherVal = (i < other.size) ? other.get(i) : T();
            T newVal = data[i] + otherVal;
            checkValue(newVal); // Vérifie que le RÉSULTAT est valide
            data[i] = newVal;
        }
        return *this;
    }

    DynamicArray& operator-=(const DynamicArray& other) {
        for (int i = 0; i < size; i++) {
            T otherVal = (i < other.size) ? other.get(i) : T();
            T newVal = data[i] - otherVal;
            checkValue(newVal); // Vérifie que le RÉSULTAT est valide
            data[i] = newVal;
        }
        return *this;
    }

    // ===== PARTIE 4, TÂCHE 3 : Opérateurs composés (Version Scalaire) =====
    DynamicArray& operator+=(const T& value) {
        for (int i = 0; i < size; i++) {
            T newVal = data[i] + value;
            checkValue(newVal); // Vérifie que le RÉSULTAT est valide
            data[i] = newVal;
        }
        return *this;
    }

    DynamicArray& operator-=(const T& value) {
        for (int i = 0; i < size; i++) {
            T newVal = data[i] - value;
            checkValue(newVal); // Vérifie que le RÉSULTAT est valide
            data[i] = newVal;
        }
        return *this;
    }

    // ===== PARTIE 4, TÂCHE 4 : Itérateurs =====
    T* begin() { return data; }
    T* end() { return data + size; }
    const T* begin() const { return data; }
    const T* end() const { return data + size; }

    // ===== PARTIE 3, TÂCHE 2 : Opérateur de sortie << =====
    friend std::ostream& operator<<(std::ostream& os, const DynamicArray<T>& arr) {
        os << "[ ";
        for (int i = 0; i < arr.size; i++) {
            os << arr.data[i];
            if (i < arr.size - 1) os << " ";
        }
        os << "]";
        return os;
    }

    // ===== PARTIE 3, TÂCHE 3 : Distance euclidienne =====
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