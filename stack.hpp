#ifndef STACK_HPP // Header guard to check if the header file is already included
#define STACK_HPP
#include "target9Header.hpp"
#include <iostream> 
using namespace std;

const int MAX = 10;
typedef Move stackEntry;
enum errorCode {success, underflow, overflow};

class Stack {
    public:
        Stack();
        bool empty() const;
        bool full() const;
        int size() const;
        errorCode top(stackEntry&) const;
        errorCode pop();
        errorCode push(const stackEntry&);
        void copyStack (Stack &destination, Stack &source);
        void initialize();
        void print() const;
    private:
        int count;
        stackEntry entry[MAX]; // An array of Move class objects
};

#endif