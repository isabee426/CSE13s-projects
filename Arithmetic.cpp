/*
Isabella Shapland // First and Last Name
ishaplan // UCSC UserID
2024 Winter CSE101 PA6 // Replace ID with assignment number
arithmetic.cpp // FileName
The main, arithmetic// Description
*/ 

#include <iostream>
#include <fstream>
#include <string>
#include "BigInteger.h" // Assuming BigInteger class is defined in BigInteger.h

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: ./Arithmetic.cpp  <input file> <output file>" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    std::ofstream outputFile(argv[2]);

    if (!inputFile || !outputFile) {
        std::cerr << "Error opening files." << std::endl;
        return 1;
    }

    std::string line;
    BigInteger A, B;

    if (std::getline(inputFile, line)) {
        A = BigInteger(line);
    } else {
        std::cerr << "Error reading input file." << std::endl;
        return 1;
    }

    if (!std::getline(inputFile, line)) {
        std::cerr << "Error reading input file." << std::endl;
        return 1;
    }

    if (std::getline(inputFile, line)) {
        B = BigInteger(line);
    } else {
        std::cerr << "Error reading input file." << std::endl;
        return 1;
    }
    outputFile << A << std::endl;
    outputFile << std::endl;

    outputFile << B << std::endl;
    outputFile << std::endl;


    BigInteger sum = A+B;

    outputFile << sum << std::endl;
    outputFile << std::endl;

    BigInteger diff = A-B;
    outputFile << diff << std::endl;
    outputFile << std::endl;

    BigInteger zero = A-A;
    outputFile << zero << std::endl;
    outputFile << std::endl;


    BigInteger scalar = (3*A) - (2*B);
    outputFile << scalar << std::endl;
    outputFile << std::endl;


    BigInteger mult = A * B;
    outputFile << mult << std::endl;
    outputFile << std::endl;


    BigInteger asq = A * A;
    outputFile << asq << std::endl;
    outputFile << std::endl;


    BigInteger bsq = B* B;
    outputFile << bsq << std::endl;
    outputFile << std::endl;

    BigInteger alast = (A*A*A*A);
    BigInteger blast = (B*B*B*B*B);
    BigInteger sumlast = 9*alast+16*blast;
    outputFile << sumlast << std::endl;
    outputFile << std::endl;
    
    inputFile.close();
    outputFile.close();
    return 0;
}
