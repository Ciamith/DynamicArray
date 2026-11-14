#include <iostream>
#include "DynamicArray.h"

using namespace std;

int main() {
    cout << "=== PARTIE 2 : GESTION DES EXCEPTIONS ===" << endl << endl;

    // Test 1 : std::bad_alloc
    cout << "--- Test 1 : bad_alloc ---" << endl;
    try {
        DynamicArray arr(10000000000); // 10 milliards pour forcer l'erreur
    }
    catch (const bad_alloc& e) {
        cout << "Exception bad_alloc attrapee : pas assez de memoire" << endl;
    }

    // Test 2 : std::out_of_range
    cout << "\n--- Test 2 : out_of_range ---" << endl;
    try {
        DynamicArray arr(5);
        arr.set(2, 50);
        cout << arr.get(10) << endl; // Index 10 n'existe pas
    }
    catch (const out_of_range& e) {
        cout << "Exception out_of_range attrapee : " << e.what() << endl;
    }

    // Test 3 : std::invalid_argument
    cout << "\n--- Test 3 : invalid_argument ---" << endl;
    try {
        DynamicArray arr(3);
        arr.push_back(150); // Hors de [-100, 100]
    }
    catch (const invalid_argument& e) {
        cout << "Exception invalid_argument attrapee : " << e.what() << endl;
    }

    return 0;
}