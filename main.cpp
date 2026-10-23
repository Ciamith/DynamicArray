#include "DynamicArray.h"
#include <iostream>

using namespace std;

int main() {
    cout << "--- Test 1 : Creation et affichage ---" << endl;
    DynamicArray arr1(3);
    arr1.set(0, 10);
    arr1.set(1, -50);
    arr1.set(2, 100);
    arr1.print();

    cout << "\n--- Test 2 : Constructeur de copie ---" << endl;
    DynamicArray arr2(arr1);
    arr2.set(0, 99);
    cout << "arr2 (copie modifiee) : ";
    arr2.print();
    cout << "arr1 (original) : ";
    arr1.print();

    cout << "\n--- Test 3 : Ajout a la fin (push_back) ---" << endl;
    DynamicArray arr3(2);
    arr3.set(0, 5);
    arr3.set(1, 5);
    arr3.push_back(10);
    arr3.push_back(-100);
    arr3.print();

    cout << "\n--- Test 4 : Addition et soustraction ---" << endl;
    DynamicArray arrA(4);
    arrA.set(0, 10); arrA.set(1, 20); arrA.set(2, 30); arrA.set(3, 40);

    DynamicArray arrB(2);
    arrB.set(0, 5); arrB.set(1, 15);

    cout << "arrA avant add : ";
    arrA.print();

    arrA.add(arrB);
    cout << "arrA apres add : ";
    arrA.print();

    arrA.sub(arrB);
    cout << "arrA apres sub : ";
    arrA.print();

    return 0;
}