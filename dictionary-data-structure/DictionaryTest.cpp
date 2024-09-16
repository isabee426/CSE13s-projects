/*
Isabella Shapland // First and Last Name
ishaplan // UCSC UserID
2024 Winter CSE101 PA8 // Replace ID with assignment number
dictionarytest.cpp // FileName
The main testing file for the dictionary adt// Description
*/

#include <iostream>
#include "Dictionary.h"

int main() {
    // Create a Dictionary object
    Dictionary dict;

    // Test size() function
    std::cout << "Size of dictionary: " << dict.size() << std::endl;

    // Test setValue() function
    dict.setValue("apple", 10);
    //std::cout << "dictionary after adding elements: " << dict << std::endl;
    //std::cout << "passed set value: " << std::endl;

    dict.setValue("banana", 20);
    dict.setValue("cherry", 30);

    // Test size() function after adding elements
    std::cout << "Size of dictionary after adding elements: " << dict.size() << std::endl;

    // Test contains() function
    std::cout << "Contains 'banana': " << dict.contains("banana") << std::endl;
    std::cout << "Contains 'grape': " << dict.contains("grape") << std::endl;

    // Test getValue() function
    std::cout << "Value of 'cherry': " << dict.getValue("cherry") << std::endl;

    // Test to_string() function
    std::cout << "Dictionary contents:\n" << dict.to_string() << std::endl;

    // Test remove() function
    dict.remove("banana");

    // Test size() function after removing an element
    std::cout << "Size of dictionary after removing an element: " << dict.size() << std::endl;

    // Test clear() function
    dict.clear();

    // Test size() function after clearing the dictionary
    std::cout << "Size of dictionary after clearing: " << dict.size() << std::endl;

    return 0;
}
