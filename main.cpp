#include <iostream>
#include <string>
#include "DynamicArray.h"
using namespace std;

int main() {

    cout << "=== PARTIE 4 : OPERATEURS ===" << endl << endl;

    // ----- Задание 1 : operator[] -----
    cout << "--- Задание 1 : operator[] ---" << endl;
    try {
        DynamicArray<int> arr(3);
        arr[0] = 10;
        arr[1] = 20;
        arr[2] = 30;
        cout << "arr = " << arr << endl;
        cout << "arr[1] = " << arr[1] << endl;

        cout << "arr[5] = 99 (hors limites)..." << endl;
        arr[5] = 99;
    }
    catch (const exception& e) {
        cout << "Erreur : " << e.what() << endl;
    }

    try {
        DynamicArray<int> arr2(2);
        arr2[0] = 50;
        arr2[1] = 150;  // hors de [-100, 100]
    }
    catch (const exception& e) {
        cout << "Erreur : " << e.what() << endl;
    }

    // ----- Задание 2 : operateurs de comparaison -----
    cout << "\n--- Задание 2 : == et != ---" << endl;
    DynamicArray<int> a1(3);
    a1[0] = 1; a1[1] = 2; a1[2] = 3;

    DynamicArray<int> a2(3);
    a2[0] = 1; a2[1] = 2; a2[2] = 3;

    DynamicArray<int> a3(3);
    a3[0] = 1; a3[1] = 2; a3[2] = 4;

    cout << "a1 = " << a1 << endl;
    cout << "a2 = " << a2 << endl;
    cout << "a3 = " << a3 << endl;
    cout << "a1 == a2 : " << (a1 == a2 ? "vrai" : "faux") << endl;
    cout << "a1 != a3 : " << (a1 != a3 ? "vrai" : "faux") << endl;

    // ----- Задание 3 : operateurs composes -----
    cout << "\n--- Задание 3 : += et -= ---" << endl;

    // Version tableau
    DynamicArray<int> b1(3);
    b1[0] = 10; b1[1] = 20; b1[2] = 30;

    DynamicArray<int> b2(3);
    b2[0] = 1; b2[1] = 2; b2[2] = 3;

    cout << "b1 = " << b1 << endl;
    cout << "b2 = " << b2 << endl;
    b1 += b2;
    cout << "b1 += b2 -> " << b1 << endl;

    b1 -= b2;
    cout << "b1 -= b2 -> " << b1 << endl;

    // Version scalaire
    DynamicArray<int> c1(3);
    c1[0] = 10; c1[1] = 20; c1[2] = 30;
    cout << "\nc1 = " << c1 << endl;
    c1 += 5;
    cout << "c1 += 5 -> " << c1 << endl;
    c1 -= 3;
    cout << "c1 -= 3 -> " << c1 << endl;

    // ----- Задание 4 : iterateurs begin()/end() -----
    cout << "\n--- Задание 4 : iterateurs (for range) ---" << endl;
    DynamicArray<int> d1(4);
    d1[0] = 10; d1[1] = 20; d1[2] = 30; d1[3] = 40;

    cout << "Lecture avec for (const auto& x : arr) :" << endl;
    for (const auto& x : d1) {
        cout << x << " ";
    }
    cout << endl;

    cout << "Modification avec for (auto& x : arr) :" << endl;
    for (auto& x : d1) {
        x = x * 2;
    }
    cout << "d1 apres multiplication par 2 : " << d1 << endl;

    return 0;
}