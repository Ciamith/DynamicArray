#include <iostream>
#include <utility>
#include "DynamicArray.h"
using namespace std;

DynamicArray<int> takeByValue(DynamicArray<int> arr) {
    cout << "  (dans takeByValue) recu : " << arr << endl;
    return arr;   // move sur le return
}

int main() {
    cout << "=== PARTIE 5 : REGLE DE TROIS/CINQ ===" << endl;

    // --- Задание 1 : operator= de copie + auto-affectation ---
    cout << "\n--- Задание 1 : operator= (copie) ---" << endl;
    DynamicArray<int> a(3); a[0] = 10; a[1] = 20; a[2] = 30;
    DynamicArray<int> b(2); b[0] = 99; b[1] = 99;
    cout << "b = a ..." << endl;
    b = a;                       // [COPY =]
    cout << "b = " << b << endl;
    a[0] = 50;                   // valeur VALIDE (<=100) pour prouver la copie profonde
    cout << "a = " << a << " | b = " << b << endl;
    cout << "auto-affectation a = a ..." << endl;
    a = a;                       // protege, pas de crash
    cout << "a = " << a << endl;

    // --- Задание 4 : AVANT / APRES move (par valeur) ---
    cout << "\n--- Задание 4 : AVANT move (lvalue -> COPIE) ---" << endl;
    DynamicArray<int> src(3); src[0] = 1; src[1] = 2; src[2] = 3;
    takeByValue(src);            // on voit [COPY ctor] -> copie couteuse
    cout << "src intact apres copie : " << src << endl;

    cout << "\n--- Задание 4 : APRES move (rvalue -> MOVE) ---" << endl;
    takeByValue(std::move(src)); // on voit [MOVE ctor] -> transfert de pointeur
    cout << "src VIDE apres move (size=" << src.getSize() << ") : " << src << endl;

    cout << "\n=== FIN : aucun leak / double-free (verifie par ASan) ===" << endl;
    return 0;
}