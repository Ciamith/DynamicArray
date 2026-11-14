#include <iostream>
#include <string>
#include "DynamicArray.h"

using namespace std;

int main() {

    cout << "=== PARTIE 3 : TEMPLATES ===" << endl << endl;

    // Type numerique (int)
    cout << "--- Test 1 : DynamicArray<int> (numerique) ---" << endl;
    try {
        DynamicArray<int> a1(3);
        a1.set(0, 1); a1.set(1, 2); a1.set(2, 3);

        DynamicArray<int> a2(3);
        a2.set(0, 4); a2.set(1, 6); a2.set(2, 3);

        cout << "a1 = " << a1 << endl;
        cout << "a2 = " << a2 << endl;
        cout << "Distance = " << a1.distance(a2) << endl;

        cout << "Tentative d'ajout de 150..." << endl;
        a1.push_back(150);
    }
    catch (const exception& e) {
        cout << "Erreur : " << e.what() << endl;
    }

    // Type non-numerique (string)
    cout << "\n--- Test 2 : DynamicArray<string> (non-numerique) ---" << endl;
    try {
        DynamicArray<string> s1(2);
        s1.set(0, "Hello"); s1.set(1, "World");

        DynamicArray<string> s2(2);
        s2.set(0, "Hi"); s2.set(1, "There");

        cout << "s1 = " << s1 << endl;
        cout << "Tentative de distance sur des string..." << endl;
        double d = s1.distance(s2);
        cout << "Distance = " << d << endl;
    }
    catch (const bad_typeid&) {
        cout << "Erreur : bad_typeid (distance impossible pour string)" << endl;
    }
    catch (const exception& e) {
        cout << "Erreur : " << e.what() << endl;
    }

    return 0;
}