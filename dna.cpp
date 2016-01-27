/******************************************************************************
Title       : dna.cpp
Author      : Dan Cambitsis
Created on  : 10/23/2015
Description : Executable for dna.hpp.
******************************************************************************/

#include <iostream>
#include <stdexcept> 
#include <string>
#include <cstdlib> //exit
#include <cctype> //toUpper
#include <vector>

#include "weighable.hpp"
#include "dna.hpp"

using namespace std;

void DNA::setSequence(string aSequence) {

  if (aSequence.length() == 0) {
    cout << "There is an empty sequence within the file. Program will now terminate." << endl;
    exit(1); //cease the program if an empty sequence is found
  }

  string::size_type found = aSequence.find_first_not_of("AGTC "); 
  //finds the first letter that isn't A, G, T, or C

  if (found != string::npos) {
    cout << "The input file contains a non-nucleotide (must contain A, G, C, and T). Program will now terminate." << endl;
    exit(1); 
    //if a letter other than A, G, T, or C is found, display error and exit
  }

  for (unsigned int i = 0; i < aSequence.length(); i++) {
    aSequence[i] = toupper(aSequence[i]); 
  } //convert all letters to upper case if not already

  theSequence = aSequence; //set private member variable theSequence to imported aSequence value

  setWeight(theSequence); //set the weight of the DNA object
}

void DNA::printBrief() { 
  if (theSequence.length() == 0) {
    cout << "Empty sequence." << endl; //if length of sequence = 0, print "Empty Sequence". 
    //This should never execute since the program will terminate if an empty sequence is found.
  }

  else {
    for (int i = 0; i < 10; i++) {
      cout << theSequence[i]; //prints first 10 letters of sequence
    }
  }
}

void DNA::setWeight(string theSequence) {
  double sumNucleotide = 0; 
  for (unsigned int i = 0; i < theSequence.length(); i++) {
    if (theSequence[i] == 'A') {
      sumNucleotide += 1.6;
    }
    else if (theSequence[i] == 'G') {
      sumNucleotide += 2.2;
    }
    else if (theSequence[i] == 'T') {
      sumNucleotide += 1.23;
    }
    else if (theSequence[i] == 'C') {
      sumNucleotide += 1.55;
    }
  }

  theWeight = sumNucleotide; //set theWeight equal to sumNucleotide 
}

void DNA::clear() {
  theSequence.clear(); //clear theSequence string
  theWeight = 0; //set the weight equal to 0
}

bool DNA::isEmpty() {
  if (theSequence.length() == 0) { //check to see if the sequence is empty
    return true;
  }
  else {
    return false;
  }
}
