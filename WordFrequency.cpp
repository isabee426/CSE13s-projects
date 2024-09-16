/*
Isabella Shapland // First and Last Name
ishaplan // UCSC UserID
2024 Winter CSE101 PA8 // Replace ID with assignment number
wordfrequency.cpp // FileName
The main file for finding the frequency of words// Description
*/

#include <fstream>
#include <iostream>
#include <string>
#include "Dictionary.h"

using namespace std;

int main(int argc, char* argv[]) {

    if (argc != 3) {
        cerr << "Usage: ./WordFrequency <in> <out>\n";
        return 1;
    }

    ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        cerr << "Error opening input file." << endl;
        return 1;
    }

    ofstream outputFile(argv[2]);
    if (!outputFile.is_open()) {
        cerr << "Error opening output file." << endl;
        return 1;
    }

    Dictionary dictionary;
    string line;
    string delim = " \r\t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";
    while (getline(inputFile, line)) {
        size_t len = line.length();
        size_t begin = 0;

        while (begin < len) {
            size_t end = line.find_first_of(delim, begin);
            if (end == std::string::npos) {
                end = len;
            }
            string token = line.substr(begin, end - begin);

            for (char& tok : token) {
                tok = tolower(tok);
            }

            if (!token.empty()) {
                if (dictionary.contains(token)) {
                   dictionary.getValue(token)++;
                   
                } else { 
                    dictionary.setValue(token, 1);
                }
            }
            begin = line.find_first_not_of(delim, end);
            if (begin == std::string::npos) {
                break; // End of line reached
            }
        }
    }

    outputFile << dictionary;

    inputFile.close();
    outputFile.close();

    return 0;
}
