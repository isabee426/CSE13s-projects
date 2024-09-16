#include<iostream>
#include "List.h"

int main() {
    List list1;
    list1.insertAfter(1);
    list1.insertAfter(2);
    list1.insertBefore(3);
    list1.insertAfter(4);
    list1.insertBefore(5);
    list1.insertAfter(1);
    list1.insertAfter(2);
    list1.insertBefore(3);
    list1.insertBefore(4);
    list1.insertAfter(5);
    list1.moveFront();
    std::cout << "List 1: " << list1 << std::endl;

    std::cout << "Removing duplicates: " << std::endl;

    if(list1.length() == 0){
        return 1;
    }
    list1.moveFront();
    int x;
    while(list1.position() < list1.length()){
        x = list1.peekNext();
        list1.moveNext();
        while(list1.findNext(x) != -1){
            list1.eraseBefore();
        }
        list1.findPrev(x);
        list1.moveNext();
    }

    std::cout << "List 1: " << list1 << std::endl;
    return 0;
}
