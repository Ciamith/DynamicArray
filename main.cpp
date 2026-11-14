#include <iostream>
#include <string>
#include "DynamicArray.h"
using namespace std;

int main() {

    cout << "=== PARTIE 3 : TEMPLATES ===" << endl << endl;

    // TYPE NUMERIQUE : int
    cout << "--- DynamicArray<int> (numerique) ---" << endl;
    try {
        DynamicArray<int> a1(3);
        a1.set(0, 1); a1.set(1, 2); a1.set(2, 3);

        DynamicArray<int> a2(3);
        a2.set(0, 4); a2.set(1, 6); a2.set(2, 3);

        cout << "a1 = " << a1 << endl;
        cout << "a2 = " << a2 << endl;
        cout << "distance = " << a1.distance(a2) << endl;

        cout << "push_back(150) sur int..." << endl;
        a1.push_back(150);
    }
    catch (const exception& e) {
        cout << "Erreur : " << e.what() << endl;
    }

    // TYPE NON-NUMERIQUE : string
    cout << "\n--- DynamicArray<string> (non-numerique) ---" << endl;
    try {
        DynamicArray<string> s1(2);
        s1.set(0, "Hello"); s1.set(1, "World");

        cout << "s1 = " << s1 << endl;

        DynamicArray<string> s2(2);
        s2.set(0, "Hi"); s2.set(1, "There");

        cout << "distance sur string..." << endl;
        double d = s1.distance(s2);
        cout << "distance = " << d << endl;
    }
    catch (const bad_typeid&) {
        cout << "Erreur : bad_typeid (distance impossible pour string)" << endl;
    }
    catch (const exception& e) {
        cout << "Erreur : " << e.what() << endl;
    }

    return 0;
}