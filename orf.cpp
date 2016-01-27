/******************************************************************************
Title       : cambitsis_daniel_hwk3_orf.cpp
Author      : Dan Cambitsis
Created on  : 5/16/2015
Description : Functions for class ORF. 
******************************************************************************/

#include <iostream>
#include <string> //string class
#include <cctype> //to convert lower case to upper case
#include <vector> //to store information
#include <fstream> //inputting and outputting files
#include "cambitsis_daniel_hwk3_orf.h"

using namespace std; 

string ORF::getAnORF() const {
	return anORF; 
}

int ORF::getStartIndex() const {
	return aStartIndex;
}

int ORF::getEndIndex() const {
	return anEndIndex;
}
