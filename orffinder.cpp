/******************************************************************************
Title       : cambitsis_daniel_hwk3_orffinder.cpp
Author      : Dan Cambitsis
Created on  : 5/16/2015
Description : Functions for class ORF Finder. 
******************************************************************************/

#include <iostream>
#include <string> //string class
#include <cctype> //to convert lower case to upper case
#include <vector> //to store information
#include <fstream> //inputting and outputting files
#include "cambitsis_daniel_hwk3_orffinder.h"

using namespace std;

string reverseStrandCreation(string strand) {
	int start = 0;
	int end = strand.length(); 
	string reverseStrand = strand; //set the reverseStrand to be equal to the strand

	while (start < end) {
		end--;
		swap(reverseStrand[start], reverseStrand[end]);
		start++;
		//swap the last position and the first position of reverseStrand while end decrements and start increments
	}

	reverseStrandConversion(strand, reverseStrand); 
	//convert all As to Ts, Gs to Cs, Cs to Gs, and Ts to As, hence complimentary

	return reverseStrand; 
}

void swap (char & v1, char & v2) {
	char temp = v1;
	v1 = v2;
	v2 = temp; 
	//simple swap of characters
}

void reverseStrandConversion(string strand, string & reverseStrand) {
	for (int i = 0; i < reverseStrand.length(); i++) {
		if (strand[i] == 'A') {
			reverseStrand[i] = 'T';
		}
		else if (strand[i] == 'C') {
			reverseStrand[i] = 'G';
		}
		else if (strand[i] == 'T') {
			reverseStrand[i] = 'A';
		}
		else if (strand[i] == 'G') {
			reverseStrand[i] = 'C';
		}
	}
	//convert the bases to their respective opposites and pass by reference back to reverseStrandCreation function
}

void ORF_Finder::findORFsDirect(vector<string> & orfStrands, int index) { //for direct strand
	vector<string> theCodons; //declare vector of codons type string
	string triplet, codonsCopy, concProtein;
	int startIndex, endIndex; 

	while (index < theStrand.length()) {
		triplet = theStrand.substr(index, 3);
		//create triplet so that it respects the boundaries of a triplet, substring from the index (0 for ORF1, for example) to length 3
		Codon aCodon(triplet);
		//declare aCodon as an object of class Codon 

		string theCodon = aCodon.getATriplet();
		//set theCodon equal to triplet through accessor function 

		if (theCodon == "ATG") {
			mRNAProteinCreation(theCodon); //pass the codon into the mRNA/protein fabrication function, if it is "ATG"
			theCodons.push_back(theCodon); //add the Codon to the vector of codons
			index = index + 3; //increase the index by 3 to respect the codon boundaries
			startIndex = index - 2; //start Index of the ATG, subtracted by 2 to record the position of the "A" rather than the "G"
			continue; //continue to the end of the loop and reiterate the loop
		}

		else if (theCodons.empty()) { //if the codon is empty (we are NOT in a potential ORF) ...
			index = index + 3; //increment the index by 3
			continue; //continue to the end of the loop
		}

		else if (theCodon != "TAA" && theCodon != "TAG" && theCodon != "TGA") { //else if we ARE in a potential ORF (ATG was passed into vector)
			//theCodon is not a stop codon
			mRNAProteinCreation(theCodon); //pass the codon into the mRNA/protein fabrication function
			theCodons.push_back(theCodon); //add the Codon to the vector of codons
			index = index + 3; //increment index by 3
			continue; //continue
		}

		if (theCodon == "TAA" || theCodon == "TAG" || theCodon == "TGA") {
			//if the codon is a stop codon ...
			theCodons.push_back(theCodon); //add codon to vector of codons
			if (theCodons.size() > 7) { //if the size of the codons vector is greater than 7, proceed to the following
				mRNAProteinCreation(theCodon); //pass codon into mRNA/protein fabrication function
				for (int i = 0; i < theCodons.size(); i++) { 
					codonsCopy += theCodons[i]; //copy the vector of codons into a string type codonsCopy to concatenate the codons
				}

				for (int i = 0; i < theProtein.size(); i++) {
					concProtein += theProtein[i]; //copy the vector of individual proteins into a string type concProtein, concatenates the proteins 
				}
				concProteinVector.push_back(concProtein); //add the string of proteins into the concProtein vector

				endIndex = index + 3; //create the end index (the position of the last A or G)
				ORF anORF(codonsCopy, startIndex, endIndex); //declare an object anORF of class ORF to store codonsCopy, start and end index
				theCodons.clear(); //clear the codons vector to be refilled later
				theProtein.clear(); //clear the protein vector to be refilled later
				concProtein.clear(); //clear the conc protein string to be refilled later
				codonsCopy.clear(); //clear the codons copy string to be refilled later

				string theORF = anORF.getAnORF(); //set the ORF string to be equal to the accessor function of getAnORF
				int theStartIndex = anORF.getStartIndex(); //set the start index equal to the accessor function of getStartIndex
				theStartIndexes.push_back(theStartIndex); //add the start index to the vector of start indexes
				int theEndIndex = anORF.getEndIndex(); //likewise to start index, create an end index value for vector
				theEndIndexes.push_back(theEndIndex); //add end index to vector
				orfStrands.push_back(theORF); //add the ORF strand to the vector of ORFs to be used in main
				index = index + 3; //increment the index value
			}

			else {
				theCodons.clear(); //else the ORF strand isn't over 7 codons long, delete the codons vector
				index = index + 3; //increment the index value
			}
		}
	}
	theStartIndexes.clear(); //clear the start indexes vector
	theEndIndexes.clear(); //clear the end indexes vector
	concProteinVector.clear(); //clear the concatenated proteins vector
}

void ORF_Finder::findORFsReverse(vector<string> & orfStrands, int index) { //similar to the above, except for the reverse strand
	vector<string> theCodons;
	string triplet, codonsCopy, concProtein; 
	int startIndex, endIndex; 

	while (index < theReverseStrand.length()) { //only difference is to check the reverse strand rather than the direct
		triplet = theReverseStrand.substr(index, 3);
		Codon aCodon(triplet);

		string theCodon = aCodon.getATriplet(); 

		if (theCodon == "ATG") {
			theCodons.push_back(theCodon);
			mRNAProteinCreation(theCodon);  
			index = index + 3; 
			startIndex = index - 2; 
			continue;
		}

		else if (theCodons.empty()) {
			index = index + 3; 
			continue;
		}

		else if (theCodon != "TAA" && theCodon != "TAG" && theCodon != "TGA") {
			theCodons.push_back(theCodon); 
			mRNAProteinCreation(theCodon); 
			index = index + 3; 
			continue;
		}

		if (theCodon == "TAA" || theCodon == "TAG" || theCodon == "TGA") {
			theCodons.push_back(theCodon); 
			if (theCodons.size() > 7) {
				mRNAProteinCreation(theCodon); 
				for (int i = 0; i < theCodons.size(); i++) {
					codonsCopy += theCodons[i]; 
				}

				for (int i = 0; i < theProtein.size(); i++) {
					concProtein += theProtein[i]; 
				}

				concProteinVector.push_back(concProtein); 

				endIndex = index + 3; 
				ORF anORF(codonsCopy, startIndex, endIndex);
				theCodons.clear();
				theProtein.clear(); 
				concProtein.clear(); 
				codonsCopy.clear();

				string theORF = anORF.getAnORF();
				int theStartIndex = anORF.getStartIndex(); 
				theStartIndexes.push_back(theStartIndex); 
				int theEndIndex = anORF.getEndIndex(); 
				theEndIndexes.push_back(theEndIndex); 
				orfStrands.push_back(theORF);
				index = index + 3;
			}

			else {
				theCodons.clear();
				index = index + 3;
			}
		}
	}
	theStartIndexes.clear(); 
	theEndIndexes.clear(); 
	concProteinVector.clear(); 
}

void ORF_Finder::mRNAProteinCreation(string theCodon) {
	for (int i = 0; i < theCodon.length(); i++) {
		if (theCodon[i] == 'T') {
			theCodon[i] = 'U'; //convert all Ts to Us for each codon, to respect the transcription of DNA to mRNA
		}
	}

	//convert all codons to proteins
	//note: I tried using a switch here but apparently, I can't use a switch with a type string
	if (theCodon == "UUU" || theCodon == "UUC") { 
			theCodon = 'F';
		}
	else if (theCodon == "UUA" || theCodon == "UUG") { 
			theCodon = 'L'; 
		}
	else if (theCodon == "CUU" || theCodon == "CUC" || theCodon == "CUA" || theCodon == "CUG") {
			theCodon = 'L'; 
		}
	else if (theCodon == "AUU" || theCodon == "AUC" || theCodon == "AUA") {
			theCodon = 'I'; 
		}
	else if (theCodon == "AUG") {
			theCodon = 'M';
		}
	else if (theCodon == "GUU" || theCodon == "GUC" || theCodon == "GUA" || theCodon == "GUG") {
			theCodon = 'V'; 
		}
	else if (theCodon == "UCU" || theCodon == "UCC" || theCodon == "UCA" || theCodon == "UCG") { 
			theCodon = 'S';
		}
	else if (theCodon == "CCU" || theCodon == "CCC" || theCodon == "CCA" || theCodon == "CCG") {
			theCodon = 'P';
		}
	else if (theCodon == "ACU" || theCodon == "ACC" || theCodon == "ACA" || theCodon == "ACG") { 
			theCodon = 'T'; 
		}
	else if (theCodon == "GCU" || theCodon == "GCC" || theCodon == "GCA" || theCodon == "GCG") {
			theCodon = 'A'; 
		}
	else if (theCodon == "UAU" || theCodon == "UAC") {
			theCodon = 'Y';
		}
	else if (theCodon == "UAA" || theCodon == "UAG" || theCodon == "UGA") {
			theCodon = '*';
		}
	else if (theCodon == "CAU" || theCodon == "CAC") {
			theCodon = 'H';
		}
	else if (theCodon == "CAA" || theCodon == "CAG") {
			theCodon = 'Q';
		}
	else if (theCodon == "AAU" || theCodon == "AAC") {
			theCodon = 'N'; 
		}
	else if (theCodon == "AAA" || theCodon == "AAG") { 
			theCodon = 'K';
		}
	else if (theCodon == "GAU" || theCodon == "GAC") { 
			theCodon = 'D';
		}
	else if (theCodon == "GAA" || theCodon == "GAG") { 
			theCodon = 'E';
		}
	else if (theCodon == "UGU" || theCodon == "UGC") {
			theCodon = 'C';
		}
	else if (theCodon == "UGG") {
			theCodon = 'W';
		}
	else if (theCodon == "CGU" || theCodon == "CGC" || theCodon == "CGA" || theCodon == "CGG" || theCodon == "AGA" || theCodon == "AGG") {
			theCodon = 'R';
		}
	else if (theCodon == "AGU" || theCodon == "AGC") {
			theCodon = 'S';
		}
	else if (theCodon == "GGU" || theCodon == "GGC" || theCodon == "GGA" || theCodon == "GGG") { 
			theCodon = 'G'; 
	}

	theProtein.push_back(theCodon); //add the protein to the vector
}

