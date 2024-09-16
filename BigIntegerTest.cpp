/*
Isabella Shapland // First and Last Name
ishaplan // UCSC UserID
2024 Winter CSE101 PA6 // Replace ID with assignment number
bigintegertest.cpp // FileName
All of the testing for the bigint structure// Description
*/ 

#include <iostream>
#include "BigInteger.h"

int main() {
    // Test the constructors
    BigInteger zeroBigInt;
    BigInteger longBigInt(1000292);
    BigInteger stringBigInt("6002398439123456876548492938328992398298392832892293894873");
    //BigInteger copyBigInt(longBigInt);
    //-100029298316935996400717666582216945996055935841534596565432094088610
    std::cout << "longBigInt " << longBigInt << std::endl;
    std::string str2 = stringBigInt.to_string();
    std::cout << "StringBitInt " << str2 << std::endl;
    //
    // Test the access functions
    std::cout << "Sign of stringBigInt: " << stringBigInt.sign() << std::endl;
    std::cout << "Comparison result: " << longBigInt.compare(stringBigInt) << std::endl;

    
    // Test the manipulation procedures
    zeroBigInt.makeZero();
    //longBigInt.negate();
    std::cout << "made it through the first stage " << std::endl;
    // Test the BigInteger arithmetic operations
    BigInteger sum = stringBigInt.add(longBigInt);
    BigInteger diff = stringBigInt.sub(longBigInt);

    BigInteger A = BigInteger("+13378008135");
    //A.makeZero();
    if (A.sign() != 0)
        std::cout << "not passsing test 1" << std::endl;

    BigInteger B = BigInteger();
    if (!(A == B))
        std::cout << "not passsing test 2" << std::endl;

    // Test other functions
    std::cout << "String representation of mult: " << sum.to_string() << std::endl;
    std::cout << "String representation of diff: " << diff.to_string() << std::endl;

    BigInteger scalarmult = 56778*A;
    std::cout << "String representation of mult: " << scalarmult.to_string() << std::endl;

    // Test overridden operators
    std::cout << "Testing operators: " << (zeroBigInt == longBigInt) << std::endl;
    std::cout << "Testing operators: " << (zeroBigInt < longBigInt) << std::endl;
    // Add more tests for other operators...

    return 0;
}
