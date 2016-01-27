/******************************************************************************
Title       : ring.cpp
Author      : Dan Cambitsis
Created on  : 10/23/2015
Description : Executable for ring.hpp.
******************************************************************************/

#include <iostream>
#include <stdexcept> 
#include <string>
#include <cstdlib> //exit
#include <cctype> //toUpper
#include <vector>

#include "ringinterface.hpp"
#include "ring.hpp"
#include "weighable.hpp"
#include "dna.hpp"

using namespace std;


Ring::Ring(): n(DEFAULT_RING_SIZE), SequenceCount(0),referenceIndex(0) {
  
  // allocate memory for the dynamic arrays:
  sequences = new DNA[n];
  isSequenceStored = new bool[n];
  
  // make sure ring is cleared
  clearRing();
}

Ring::Ring(int ringSize): n(ringSize), SequenceCount(0),referenceIndex(0) {
  
  // sanity checking ring size
  if( ringSize < 1 ) {
    n = DEFAULT_RING_SIZE;
  }
  
  // allocate memory
  sequences = new DNA[n];
  isSequenceStored = new bool[n];
  
  // make sure ring is cleared
  clearRing();
}

void Ring::set(const DNA value) {
  // if nothing was stored at the location before
  // only then increase count
  
  if(isSequenceStored[referenceIndex] == false) { 
    SequenceCount++;
    isSequenceStored[referenceIndex] = true;
  }
  sequences[referenceIndex] = value;
  
}

DNA Ring::get() const {
  if (isSequenceStored[referenceIndex] == true) {
    return sequences[referenceIndex];
  } 
  else {
    throw std::runtime_error("no value at reference");
  }
}

bool Ring::remove() {
  bool result = true;
  
  if (isSequenceStored[referenceIndex] == false) {
    result = false;
  } 
  else {
    isSequenceStored[referenceIndex] = false;
    SequenceCount--;
  }
  
  return result;
}

void Ring::moveReference(int positions) {
  if (positions != 0 ) {
    
    if( positions > 0 ) {
      // +ve increment: the mod operation ensures wrapping 
      referenceIndex = (referenceIndex + positions) % n;
    } else {
      // negative increment: 
      referenceIndex = referenceIndex + (positions % n);
      // correction if the reference index is still -ve
      if( referenceIndex < 0 ) {
  referenceIndex = n + referenceIndex;
      }
      
    }
    
  } 
}

void Ring::moveNext() {
  moveReference(1);
}

void Ring::movePrevious() {
  moveReference(-1);
}

int Ring::getSequenceCount() const {
  return SequenceCount;
}

int Ring::getRingSize() const {
  return n;
}


void Ring::clearRing() {
  for( int i = 0; i < n ; i++ ) {
    isSequenceStored[i] = false;
  } 
  SequenceCount = 0;
}

void Ring::moveToKthLargest(int k) {
  vector<DNA> theVector; //create vector of type DNA to store DNA objects
  for (int i = 0; i < n; i++) {
    theVector.push_back(sequences[i]); //add the DNA objects to the vector
  }

  moveToKthLargestRecursion(theVector, n, k); //begin the recursion
}

void Ring::moveToKthLargestRecursion(vector<DNA> a, int size, int k) {
  int pivot = size / 2; //set pivot to the size (20) divided by 2
  double pivotValue = a[pivot].getWeight(); //set the pivot value to the weight of the selected pivot DNA object
  vector<DNA>s1; //create a vector to store weights less than pivotValue
  vector<DNA>s2; //create a vector to store weights greater than pivotValue

  for (int i = 0; i < size; i++) {
    if (a[i].getWeight() < pivotValue) { //if the DNA object's weight is less than pivotValue's weight ...
      s1.push_back(a[i]); //add to s1 vector
    }

    else if (a[i].getWeight() > pivotValue) { //else (the DNA object's weight is greater than pivotValue's weight) ...
      s2.push_back(a[i]); //add to s2 vector
    }
  }

  int sizes1 = s1.size();
  int sizes2 = s2.size();

  if (sizes2 == k - 1) { //if s2's size is equal to k -1 ...
    a[pivot].printBrief(); //print theSequence to console
    cout << " and its weight is: " << pivotValue << "."; /// ... and print its weight
  }

  else if (sizes2 > (k - 1)) { //if s2's size is greater than k - 1 ...
    moveToKthLargestRecursion(s2, sizes2, k); //redo the recursion with s2 parameters
  }

  else if (sizes2 < (k - 1)) { //if s2's size is less than k - 1 ...
    moveToKthLargestRecursion(s1, sizes1, k - sizes2 - 1); //redo the recursion with s1 parameters except for k's value
  }
}

Ring::~Ring() {
  
  delete[] sequences;
  delete[] isSequenceStored;
}
