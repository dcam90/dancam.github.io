/******************************************************************************
Title       : main.cpp
Author      : Dan Cambitsis
Created on  : 10/23/2015
Description : A program that is designed to store twenty DNA objects into a Ring. From said Ring, 
the program outputs the 5th, 10th, and 15th heaviest DNA sequences to the console. The DNA objects
are obtained from a file (dna_sequences.txt). 
Build with  : g++ -Wall -pedantic main.cpp ring.cpp dna.cpp -o main
Usage       : ./main
Dependencies: weighable.hpp, dna.hpp, ringinterface.hpp, ring.hpp, ring.cpp, dna.cpp
******************************************************************************/

#include <iostream>
#include <stdexcept> 
#include <cassert>
#include <string>
#include <fstream> //input file
#include <cstdlib> //exit
#include <cctype> //toUpper
#include <vector>

#include "weighable.hpp"
#include "dna.hpp"
#include "ringinterface.hpp"
#include "ring.hpp"

using namespace std;

int main() {
  ifstream inStream; //create input stream
  string filename1, aSequence; //create filename1 string and aSequence to store imported sequence
  Ring theSequences(20); //initiate a new Ring object called theSequences to store up to 20 DNA sequences

  assert(theSequences.getRingSize() == 20); //make sure the size is 20

  cout << "Enter the filename: " << endl;
  cin >> filename1; //user inputs filename (dna_sequences.txt)
  inStream.open(filename1.c_str()); //open the file

  if (!inStream.is_open()){ 
    cout << "ERROR: Input file does not exist. Program will now terminate." << endl;
    exit(1); //if input file does not exist, display error and exit
  }

  while (!inStream.eof()) { //while not the end of the file ...
    DNA theSequence; //set up an object theSequence of DNA class
    getline(inStream, aSequence); //read one line from the file
    theSequence.setSequence(aSequence); //set the line from the file as an attribute of theSequence
    theSequences.set(theSequence); //put theSequence object into the Ring
    theSequences.moveNext(); //move the point of reference
    theSequence.clear(); //empty the string and set its weight to 0

    assert(theSequence.isEmpty() == true); //check to see if the string is actually empty
  }

  inStream.close(); //close the inStream

  assert(theSequences.getSequenceCount() == 20); //check to see if the sequence count is indeed 20

  for (int i = 0; i < theSequences.getSequenceCount(); i++) {
    if (i == 5 || i == 10 || i == 15) {
      cout << "The " << i << "th heaviest sequence is: ";
      theSequences.moveToKthLargest(i); //move to either the 5th, 10th, or 15th largest sequence
      cout << endl;
    }
    theSequences.moveNext(); //move the point of reference
  }

    
  return 0;
}
