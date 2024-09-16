/*
Isabella Shapland // First and Last Name
ishaplan // UCSC UserID
2024 Winter CSE101 PA6 // Replace ID with assignment number
BigInteger.cpp // FileName
All of the functions for the biginteger structure// Description
*/ 


#include<iostream>
#include<string>
#include<stdexcept>
#include <sstream>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include"List.h"
#include "BigInteger.h"

const int power = 9;
const long base = pow(10, power); //base should be 10^power


// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger(){
    signum = 0;
    digits = List();
    digits.clear();

}

// BigInteger()
// Constructor that creates a new BigInteger from the long value x.
BigInteger::BigInteger(long x){
    signum = 0;
    std::string numstr = std::to_string(x);
    BigInteger temp(numstr);
    digits = temp.digits;
    if(x > 0){
        signum = 1;
    }
    else if(x < 0){
        signum = -1;
    }
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s){
    digits = List();
    signum = 0;
    if(s.length() == 0){
        throw std::invalid_argument("empty string");
        return;
    }
    bool found = false;
    for (char ch : s){
        if(isdigit(ch)){
            found = true;
        }
    }
    if(!found){
        throw std::invalid_argument("no digits in string");
        return;
    }

    bool iszero = true;
    std::string temp = "";
    if(s[0] == '-'){
        signum = -1;
    }
    else{
        signum = 1;
    }
    for (int i  = s.length()-1; i >=0; i--){ 
        if(isdigit(s[i])){
            long d = std::stol(std::string(1, s[i]));
            temp = s[i] + temp; //test on temp
            if(d != 0){
                iszero = false;
            }
            if(temp.length() == power){
                //std::cout << "numsstr " << numsstr << std::endl;
                digits.insertAfter(std::stol(temp));
                temp = "";
            }   
        }
    }
    if(temp.length() > 0){
        digits.insertAfter(std::stol(temp));
    }
    if(iszero){
        signum = 0;
        digits.clear();
    }
    //std::cout << "digits " << digits << std::endl;

}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N){
    List copydigits(N.digits);
    digits = copydigits;
    signum = N.signum;
}

// Optional Destuctor
BigInteger::~BigInteger(){
    digits.clear();
}
// ~BigInteger();


// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const{
    return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const{ //destroy copy
    if(N.digits.equals(digits)){
        return 0;
    }
    if(digits.length() > N.digits.length()){
        return 1;
    }
    else if(digits.length() < N.digits.length()){
        return -1;
    }
    else{
        List digitscopy(digits);
        List ncopy(N.digits);
        digitscopy.moveFront();
        ncopy.moveFront();
        while(digitscopy.position() != digitscopy.length() && ncopy.position() != ncopy.length()){
            if(digitscopy.peekNext() != ncopy.peekNext()){
                if(digitscopy.peekNext() > ncopy.peekNext()){
                    return 1;
                }
                else{
                    return -1;
                }
            }
            digitscopy.moveNext();
            ncopy.moveNext();
        }
        return 0;
    }
}

// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero(){
    signum = 0;
    if(digits.length() > 0){
        digits.clear();
        //std::cout << "digits made zero " << digits << std::endl;
    }
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate(){
    if(signum == 1){
        signum = -1;
    }
    else if(signum == -1){
        signum = 1;
    }
    else{
        return;
    }
}

List normalize(List& L, long carry){
    L.moveBack();
    long mod = 0;
    long curr = 0;
    while(L.position() > 0){
        curr = L.peekPrev();
        if(carry > 0 || carry < 0){
            //std::cout << "carry: " << carry << std::endl;
            curr += carry;
            L.setBefore(curr);
            carry = 0;
        }
        if(curr >= base){
            mod = curr % base;
            carry = curr / base;
            //std::cout << "carry: " << carry << std::endl;
            L.setBefore(mod);
        }
        else if(curr < 0){
            carry = -1;
            mod = base + curr;
            L.setBefore(mod);
        }
        L.movePrev();
    }
    //if(carry < 0)
        //means we will have to normalize again
        //just leave it, ill fix it in sub, by saying if carry < 0 make everything but the front negative and normalize again
    
    if (carry > 0){
        L.moveFront();
        L.insertBefore(carry);
    }
    //std::cout << "l: " << L << std::endl;

    return L;
}
// BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const{ //figure out how to add neg and pos
    if(N.signum == 0){
        BigInteger thiscopy(*this);
        return thiscopy;
    }
    else if(signum == 0){ //it is not a new bigint
        BigInteger Ncopy(N);
        //std::cout << "digits: " << Ncopy.digits << std::endl;
        return Ncopy;
    }
    else if(signum == 1 && N.signum -1){
        BigInteger Ncopy(N);
        Ncopy.signum = 1;
        return this->sub(Ncopy);
    }
    else if(signum == -1 && N.signum == 1){
        BigInteger thiscopy(*this);
        thiscopy.signum = 1;
        return N.sub(thiscopy);
    }
    else{
        BigInteger sum;
        List Ncopy(N.digits);
        List digitscopy(digits);
        //std::cout << "thiscopy: " << digitscopy << std::endl;
        //std::cout << "Ncopy: " << Ncopy << std::endl;
        Ncopy.moveBack();
        digitscopy.moveBack();
        List finished;
        long carry =0;
        //finished.moveFront();
        while(digitscopy.position() > 0 && Ncopy.position() > 0){
            long thiscurr = digitscopy.peekPrev();
            long Ncurr = Ncopy.peekPrev();
            long added = thiscurr + Ncurr;
            //std::cout << "added: " << added << std::endl;
            finished.insertAfter(added);
            digitscopy.movePrev();
            Ncopy.movePrev();
        }
        //std::cout << "finished: " << finished << std::endl;
         if(digitscopy.position() != 0){
            while(digitscopy.position() !=0){
                long curr = digitscopy.movePrev();
                finished.insertAfter(curr);
            }
        }
        else if(Ncopy.position() != 0){
            while(Ncopy.position() !=0){
                long curr = Ncopy.movePrev();
                finished.insertAfter(curr);
            }
        }
        //std::cout << "finished: " << finished << std::endl;
        
        normalize(finished, carry);
        
        std::string str = finished.to_string();
        //std::cout << "finished: " << finished << std::endl;
        //std::cout << "Ncopy: " << Ncopy << std::endl;
        if(signum == -1 && N.signum == -1){
            sum.signum = -1;
        }
        else{
            sum.signum = 1;
        }
        sum.digits = finished;
        //std::cout << "digits: " << str << std::endl;
        return sum;
    }
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const{
    
    if((N.signum == 0 && signum == 0) || (*this) == N){
        BigInteger zero;
        return zero;
    }
    if(N.signum == 0){
        BigInteger thiscopy(*this);
        thiscopy.signum = 1;
        return thiscopy;
    }
    else if(signum == 0){ //it is not a new bigint
        BigInteger Ncopy(N);
        Ncopy.signum = -1;
        return Ncopy;
    }
    else if(signum == 1 && N.signum == -1){
        BigInteger Ncopy(N);
        Ncopy.signum = 1;
        return (*this).add(Ncopy);
    }
    else if(signum == -1 && N.signum == 1){
        BigInteger thiscopy(*this);
        thiscopy.signum = 1;
        BigInteger neg = N.add(thiscopy);
        neg.signum = -1;
        return neg;
    }
    if(N > *this){
        BigInteger neg = N.sub(*this);
        if(signum == -1 && N.signum == -1){
            neg.signum = 1;
            return neg;
        }
        else if(signum == 1 && N.signum == -1){
            BigInteger Ncopy(N);
            Ncopy.signum = 1;
            neg = Ncopy.sub(*this);
            neg.signum = -1;
            return neg;
        }
        neg.signum = -1;
        return neg;
    }
    else{
        BigInteger ncpy(N);
        BigInteger thiscpy(*this);
        std::string str = ncpy.to_string();
        std::string str2 = thiscpy.to_string();
        List Ncopy= ncpy.digits;
        List digitscopy = thiscpy.digits;
        
        BigInteger sub;
        //std::cout << "thiscopy: " << digitscopy << std::endl;
        //std::cout << "Ncopy: " << Ncopy << std::endl;
        Ncopy.moveBack();
        digitscopy.moveBack();
        List finished;
        long carry =0;
        //finished.moveFront();
        while(digitscopy.position() > 0 && Ncopy.position() > 0){
            long thiscurr = digitscopy.peekPrev();
            long Ncurr = Ncopy.peekPrev();
            long subtracted = thiscurr - Ncurr;
            std::cout << "subtracted: " << subtracted << std::endl;
            finished.insertAfter(subtracted);
            digitscopy.movePrev();
            Ncopy.movePrev();
        }
         if(digitscopy.position() != 0){
            while(digitscopy.position() !=0){
                long curr = digitscopy.movePrev();
                finished.insertAfter(curr);
            }
        }
        else if(Ncopy.position() != 0){
            while(Ncopy.position() !=0){
                long curr = Ncopy.movePrev();
                finished.insertAfter(curr);
            }
        }
        //std::cout << "finished: " << finished << std::endl;
        normalize(finished, carry);
        //std::cout << "finished: " << finished << std::endl;
        /*
        if(carry < 0){ //technically shouldnt neeed this?
            while(carry < 0){
                finished.moveFront();
                finished.moveNext();
                while(finished.position() < finished.length()){
                    long neg = finished.peekNext();
                    finished.setAfter(-neg);
                }
                normalize(finished, 0);
            }
            
        }*/
        if(signum == -1 && N.signum == -1){
            sub.signum = -1;
        }
        else{
            sub.signum = 1;
        }
        sub.digits = finished;
        //std::cout << "digits: " << finished << std::endl;
        return sub;
    }
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const{
    //scalar multiply the second list by the last number of the first list
    if(signum == 0 || N.signum == 0){
        BigInteger zero;
        return zero;
    }
    BigInteger thiscopy(*this);
    BigInteger Ncopy(N);
    BigInteger product;

    List digits = thiscopy.digits;
    List Ndigits = Ncopy.digits;

    if(digits.length() > Ndigits.length()){
        product = Ncopy.mult(thiscopy);
        return product;
    }

    digits.moveBack();
    long count = 0;
    while(digits.position() > 0){
        long val = digits.peekPrev();
        List p;
        Ndigits.moveBack();
        long carry = 0;
        long t = 0;

        while(Ndigits.position() > 0){
            t = (Ndigits.peekPrev()*val)+carry;
            carry = t/base;
            t = t%base;
            p.insertAfter(t);
            Ndigits.movePrev();
        }
        if(carry > 0){
            p.insertAfter(carry);
        }
        p.moveBack();
        for(int i = 0; i < count; i++){
            p.insertAfter(0);
        }

        BigInteger sum;
        sum.signum= 1;
        sum.digits = p;
        product+= sum;

        digits.movePrev();
        count++;
    }
    product.signum = thiscopy.signum * Ncopy.signum;
    return product;
    
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string(){ //remember that a zero digits list will not print and will cause a seg fault
    if(signum == 0){
        return "0";
    }
    std::string str = (signum == -1) ? "-" : "";
    
    digits.moveFront();
    bool nonzero = false;
    while(digits.position() < digits.length()){
        long digit = digits.peekNext();
        if(digit == 0){
            if(!nonzero){
                digits.eraseAfter();
            }
        }
        else{
            nonzero = true;
            break;
        }
    }

    //std::cout << "digits: " << digits << std::endl;
    digits.moveFront();
    while(digits.position() < digits.length()){
        long LE = digits.peekNext();
        std::string curr = std::to_string(LE);
        if(curr.length() < power){
            if(digits.position() > 0){
                for(int i = curr.length(); i < power; i++){
                    curr = "0" + curr;
                }   
            }
            
        }
        str += curr;
        digits.moveNext();
    }
    return str;
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.

std::ostream& operator<<(std::ostream& stream, BigInteger N) {
    std::string s = N.to_string();
    //std::cout << "here is s " << s << std::endl;
    return stream << s; // Output the string representation of BigInteger
}


// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ){
    return (A.digits.equals(B.digits)) && (A.signum == B.signum);
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ){
    return A.compare(B) == -1;
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){
    return (A.compare(B) == -1 || A.compare(B) == 0);
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){
    return A.compare(B) == 1;
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){
    return (A.compare(B) == 1 ||  A.compare(B) == 0);
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
    return A.add(B);
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
    A = A.add(B);
    return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
    return A.sub(B);
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
    A = A.sub(B);
    return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
    return A.mult(B);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
    A = A.mult(B);
    return A;
}
