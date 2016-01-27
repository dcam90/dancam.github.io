/******************************************************************************
Title       : cambitsis_daniel_p2_imp.cpp
Author      : Dan Cambitsis
Created on  : 11/17/2015
Description : Executable for cambitsis_daniel_p2_header.hpp.
******************************************************************************/

#include <iostream>
#include <cassert>
#include <stdexcept> 
#include <cstdlib>
#include "cambitsis_daniel_p2_header.hpp"

using namespace std;

MultiStack::MultiStack() : top(nullptr) { } //set top to nullptr

MultiStack::MultiStack(const MultiStack& newMultiStack) {
    if (newMultiStack.top == nullptr) {
      top = nullptr;
    }
    else {
      // perform "deep copy"
      top = new node; 
      top -> theChar = newMultiStack.top -> theChar; //copy the first node
      count++;

      //...and the rest of the nodes
      node *newPtr = top;
      for (node *origPtr = newMultiStack.top -> next; origPtr != nullptr; origPtr = origPtr -> next) {
        newPtr -> next = new node;
        newPtr = newPtr -> next;
        newPtr -> theChar = origPtr -> theChar;
        count++;
      }

      newPtr -> next = nullptr;
    }
}

MultiStack& MultiStack::operator=(const MultiStack& newMultiStack) {
    if (newMultiStack.top != nullptr) {
      if (top != nullptr) {
        delete top;
      }

      else {
        top = new node; 
        top -> theChar = newMultiStack.top -> theChar; //copy the first node
        count++;

        //...and the rest of the nodes
        node *newPtr = top;
        for (node *origPtr = newMultiStack.top -> next; origPtr != nullptr; origPtr = origPtr -> next) {
            newPtr -> next = new node;
            newPtr = newPtr -> next;
            newPtr -> theChar = origPtr -> theChar;
            count++;
        }

        newPtr -> next = nullptr;
      }
    }

    else {
      if (top != nullptr) {
        delete top;
      }

      top = nullptr;
    }

    return *this;
}

void MultiStack::push(char c) {
    node* newPtr = new node; //create a new node
    newPtr -> theChar = c; //character that is pushed is set as theChar, saved as newPtr's character
    newPtr -> next = top; //sets the node as the new 'top' of the stack
    top = newPtr; //top is equal to the newPtr
    count++; //increment the count by 1 (we added content to the stack)
}

char MultiStack::pop() {
    if (isEmpty()) {
      throw logic_error("Stack is empty, program will terminate.");
    }

    node* temp = top; //set the temp equal to the top of the stack
    top = top -> next; //top is now pointing to the next node ("under" the original top)
    temp -> next = nullptr; //point the old top to NULL
    delete temp; //delete the old top
    count--; //reduce the count by 1 (we popped off a value from the stack) 

    return 0; 
}

char MultiStack::multiPop() {
    if (isEmpty()) {
      throw logic_error("Stack is empty, program will terminate.");
    }

    MultiStack tempStack1; //create a tempStack to store non-'a's
    MultiStack tempStack2; //create a tempStack to store 'a's 
    char topOfStackChar = top -> theChar; //create a character that is = to the character on top of stack
    while (count > 0) {
      if (top -> theChar != topOfStackChar) {
        tempStack1.push(top -> theChar); //push non-'a's onto temporary stack
        pop(); //pop off the top of original stack
      }

      else {
        tempStack2.push(top -> theChar); //push the character 'a' onto the other temporary stack
        pop(); //pop off the top of original stack
      }
    }

    int sizeTempStack1 = tempStack1.getSize(); //set size of tempStack1 to int variable

    for (int i = 0; i < sizeTempStack1; i++) {
      push(tempStack1.top -> theChar); //push contents of tempStack1 (non 'a's) back to original stack
      tempStack1.pop(); //pop off the top of temporary stack, eventually destroys tempStack1
    }

    return tempStack2.top -> theChar; //return 'a' (the top of the other temporary stack)
    //tempStack2 destroyed by destructor
}

int MultiStack::getRepeatCounts() {
    if (isEmpty()) {
      return 0; //if the stack is empty, return 0
    }

    int repeatCount = 0;
    node* temp = top; //creates a temporary value to point to the top node
    while (temp != nullptr) { //while the temporary is not the nullptr ...
      if (temp -> theChar == top -> theChar) { //if the temp pointing to theChar is equal to the top pointing to the top ...
        repeatCount++; //increment repeatCount, the temp value is equal to the top of the stack
      }

      temp = temp -> next; //traverse the temp and terminate while loop when it's done analyzing the last node
    }

    delete temp; //delete the temporary pointer
    return repeatCount; //return the repeatCount
}

bool MultiStack::isEmpty() const {
    return top == nullptr; //returns true if top is the nullptr, otherwise false (nothing exists in stack)
}

int MultiStack::getSize() const {
    return count; //returns the count based off of push and pop
}

int MultiStack::getUniqueCount() {
    if (isEmpty()) {
      return 0; //if the stack is empty, return 0
    }

    node* temp = top; //create temp to point to top node
    MultiStack tempStack1; //create a temporary stack to mimic original stack

    while (temp != nullptr) {
      tempStack1.push(temp -> theChar);
      temp = temp -> next; //push all values of original stack into temporary stack, do not pop off anything from original
    }

    int uniqueCount = 0; //counter variable 

    while (!tempStack1.isEmpty()) { //while the temporary stack isn't empty ...
      if (tempStack1.getRepeatCounts() > 1) { //if the repeated counts of the top node is greater than one ...
        uniqueCount++; //increment uniqueCount
        tempStack1.multiPop(); //pop off the top and all instances of top within the temporary stack
      }

      else { //else if the repeated count of the top is exactly 1
        uniqueCount++; //increment uniqueCount
        tempStack1.pop(); //pop the top off
      }
    }

    delete temp; //delete the temporary value
    return uniqueCount; //return uniqueCount
}

MultiStack::~MultiStack() {
    while (!isEmpty()) {
      pop(); //while a MultiStack isn't empty, pop off all of the contents
    }

    count = 0; //in case count isn't set to 0 from pop, set it to 0
    delete top; //delete the top if not deleted
    top = nullptr; //set it to the nullptr
}
