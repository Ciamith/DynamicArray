#include <iostream>
#include "DynamicArray.h"

using namespace std;

int main() {

    // Test 1 : std::bad_alloc
    cout << "Test 1 (bad_alloc) :" << endl;
    try {
        DynamicArray arr(1000000000);
    }
    catch (const bad_alloc& e) {
        cout << "Exception bad_alloc attrapee : pas assez de memoire" << endl;
    }

    // Test 2 : std::out_of_range
    cout << "\nTest 2 (out_of_range) :" << endl;
    try {
        DynamicArray arr(5);
        arr.set(2, 50);
        cout << arr.get(10) << endl;
    }
    catch (const out_of_range& e) {
        cout << "Exception out_of_range attrapee : " << e.what() << endl;
    }

    // Test 3 : std::invalid_argument
    cout << "\nTest 3 (invalid_argument) :" << endl;
    try {
        DynamicArray arr(3);
        arr.push_back(150);
    }
    catch (const invalid_argument& e) {
        cout << "Exception invalid_argument attrapee : " << e.what() << endl;
    }

    return 0;
}