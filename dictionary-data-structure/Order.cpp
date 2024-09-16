/*
Isabella Shapland // First and Last Name
ishaplan // UCSC UserID
2024 Winter CSE101 PA8 // Replace ID with assignment number
order.cpp // FileName
The main, order// Description
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include "Dictionary.h" // Include the Dictionary header file

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: ./Order.cpp  <input file> <output file>" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    std::ofstream outputFile(argv[2]);

    if (!inputFile || !outputFile) {
        std::cerr << "Error opening files." << std::endl;
        return 1;
    }
    Dictionary dictionary;
    std::string line;
    int lineNumber = 1;
    while (std::getline(inputFile, line)) {
        dictionary.setValue(line, lineNumber);
        lineNumber++;
    }

    inputFile.close();
    
    if (!outputFile) {
        std::cerr << "Error: Unable to open output file.\n";
        return 1;
    }

    // Write the first string representation of the Dictionary (pairs of "key : value")
    outputFile << dictionary.to_string();

    // Write the second string representation of the Dictionary (keys only)
    outputFile << dictionary.pre_string();

    // Close the output file
    outputFile.close();

    return 0;
}
