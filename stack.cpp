#include "stack.hpp"

Stack::Stack() {
    // Constructor to initialize an empty stack
    count = 0;
}

void Stack::initialize() {
    count = 0;
}

bool Stack::empty() const {
    // If the stack is empty, return true, else return false
    return count == 0;
}

bool Stack::full() const {
    // If the stack is full return true, else return false
    return count == MAX;
}

int Stack::size() const {
    // Return the number of items in the stack
    return count;
}

errorCode Stack::top(stackEntry &item) const {
    // If the stack is empty return underflow, otherwise the top of the stack is returned IN ITEM
    // The client function will provide a stackEntry topItem variable and it will pass it as a parameter when calling
    // this function. Then, this function will return the top of the stack BY REFERENCE, to the topItem
    // variable provided by the client function. This saves us from copying values.
    if (empty()) {
        return underflow;
    }

    item = entry[count-1];  // -1 because of array indexing
    return success;
}

errorCode Stack::pop() {
    //If the stack is empty, return underflow, otherwise the top of the stack is removed
    if (empty()) {
        return underflow;
    }

    count--;
    return success;
}

errorCode Stack::push (const stackEntry &item) { 
    // const &item because of safety reasons so as NOT to change the value of the reference parameter "item", because it will change the actual item as well, because it is reference "&"
    // Also, &item because item COPIES the value which is resource-consuming in large programs, whereas &item just READS it from its memory location
    // If the stack is full return overflow, otherwise insert item into the stack(array) at position count++
    if (full()) {
        return overflow;
    }

    entry[count++] = item;
    return success;
}

void Stack::print() const {
    // Prints the stack contents
    for (int i = 0; i < count; ++i) {
        cout << "(" << entry[i].row << ", " << entry[i].col << ") ";
    }
    cout << endl;
}