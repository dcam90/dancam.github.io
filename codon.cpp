/******************************************************************************
Title       : cambitsis_daniel_hwk3_codon.cpp
Author      : Dan Cambitsis
Created on  : 5/16/2015
Description : Functions for class Codon. 
******************************************************************************/

#include <iostream>
#include <string> //string class
#include <cctype> //to convert lower case to upper case
#include <vector> //to store information
#include <fstream> //inputting and outputting files
#include "cambitsis_daniel_hwk3_codon.h"

using namespace std; 

string Codon::getATriplet() const {
	return aTriplet; 
}
