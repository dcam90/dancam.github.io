/******************************************************************************
Title       : main.cpp
Author      : Dan Cambitsis
Created on  : 5/16/2015
Description : Program will find all open reading frames, given a strand. Said strand will
be used to create a reverse strand. When the reverse strand is generated, both strands will
then be searched for possible open reading frames, depending on whether a start codon is
present. When an ORF is found in a particular reading frame, it will be outputted to an output
file.  
Build with  : g++ -Wall -pedantic main.cpp cambitsis_daniel_hwk3_orf.cpp cambitsis_daniel_hwk3_codon.cpp cambitsis_daniel_hwk3_orffinder.cpp -o main
Usage       : ./main
Dependencies: cambitsis_daniel_hwk3_orf.cpp, cambitsis_daniel_hwk3_codon.cpp, cambitsis_daniel_hwk3_orffinder.cpp
******************************************************************************/

#include <iostream>
#include <string> //string class
#include <cctype> //to convert lower case to upper case
#include <vector> //to store information
#include <fstream> //inputting and outputting files
#include "cambitsis_daniel_hwk3_codon.h"
#include "cambitsis_daniel_hwk3_orf.h"
#include "cambitsis_daniel_hwk3_orffinder.h"

using namespace std; 

int main (int argc, char * argv[]) {
	ifstream inStream; //declare input stream
	ofstream outStream; //declare output stream
	string filename1, filename2, importedStrand, strand, sampleName, reverseStrand; 

	cin >> filename1 >> filename2; //user inputs the name of input file and output file, respectively
	inStream.open(filename1.c_str()); //open the input file
	outStream.open(filename2.c_str()); //open the output file

	if (!inStream.is_open()){
		cout << "ERROR: Input file does not exist. Program will now terminate." << endl;
		exit(1); //if input file does not exist, display error and exit
	}

	inStream.ignore(1, '>'); //ignore the initial '>' character in the input file, precedes the name 
	getline(inStream, sampleName); //gets the name of the sequence

	while (!inStream.eof()) {
		getline(inStream, importedStrand);
		strand = strand.append(importedStrand); 
		//while not the end of the inStream, get each individual line and append to strand
	}

	inStream.close(); //close the inStream

	reverseStrand = reverseStrandCreation(strand); //create reverseStrand from strand

	int start = 0;
	int end = reverseStrand.length(); 

	while (start < end) {
		end--;
		swap(reverseStrand[start], reverseStrand[end]);
		start++;
		//reswaps the reverse strand so the 3' is at index 0, rather than being at the last index
	}

	ORF_Finder theFinder(strand, reverseStrand); //declare ORF_Finder
	vector<string> orf1StrandsDirect; //creation of six empty vectors to store ORF strands
	vector<string> orf2StrandsDirect;
	vector<string> orf3StrandsDirect;
	vector<string> orf1StrandsReverse;
	vector<string> orf2StrandsReverse;
	vector<string> orf3StrandsReverse;
	int sizeOfStrand = strand.length(); //sizeOfStrand is the length of the strand

	if (sizeOfStrand < 21 || sizeOfStrand > 5000) {
		cout << "The size of the DNA sequence is either too large or too small. Program will now terminate." << endl;
		exit(1); 
		//if the size of the strand is less than 21 or greater than 5000, display error and exit
	}

	for (int i = 0; i < sizeOfStrand; i++) {
		strand[i] = toupper(strand[i]); 
		reverseStrand[i] = toupper(reverseStrand[i]); 
		//converts the strand and the reverse strand to uppercase, if not already
	}

	string::size_type found = strand.find_first_not_of("AGTC "); 
	//finds the first letter that isn't A, G, T, or C

	if (found != string::npos) {
		cout << "The input file contains a non-nucleotide (must contain A, G, C, and T). Program will now terminate." << endl;
		exit(1); 
		//if a letter other than A, G, T, or C is found, display error and exit
	}

	outStream << "ORF results for " << "\"" << sampleName << "\"" << " containing " << sizeOfStrand << " bases." << endl;
	//display sample name and the size of strand to the output file
	outStream << endl;
	outStream << endl;

	theFinder.findORFsDirect(orf1StrandsDirect, 0);
	//finds all possible ORFs in reading frame 1 for the direct strand

	if (orf1StrandsDirect.empty()) {
		outStream << "No ORFs were found in reading frame 1 on the direct strand." << endl;
		outStream << endl;
		//if the vector is empty, display message to output file
	}

	else {
		int counter = 1;
		for (int i = 0; i < orf1StrandsDirect.size(); i++) {
			outStream << ">ORF number " << counter << " in reading frame 1 on the direct strand" <<
			" extends from base " << theFinder.theStartIndexes[i] << " to base " << theFinder.theEndIndexes[i] << endl;
			outStream << orf1StrandsDirect[i] << endl;
			outStream << endl;
			outStream << ">Translation of ORF number " << counter << " in reading frame 1 on the direct strand: " <<
			theFinder.concProteinVector[i];
			outStream << endl;
			outStream << endl;
			counter++;
			//display information if vector is filled
		}
	}

	theFinder.findORFsDirect(orf2StrandsDirect, 1);
	//finds all possible ORFs in reading frame 2 for the direct strand

	if (orf2StrandsDirect.empty()) {
		outStream << "No ORFs were found in reading frame 2 on the direct strand." << endl;
		outStream << endl;
	}

	else {
		int counter = 1;
		for (int i = 0; i < orf2StrandsDirect.size(); i++) {
			outStream << ">ORF number " << counter << " in reading frame 2 on the direct strand" <<
			" extends from base " << theFinder.theStartIndexes[i] << " to base " << theFinder.theEndIndexes[i] << endl;
			outStream << orf2StrandsDirect[i] << endl;
			outStream << endl;
			outStream << ">Translation of ORF number " << counter << " in reading frame 2 on the direct strand: " <<
			theFinder.concProteinVector[i]; 
			outStream << endl;
			outStream << endl;
			counter++; 
		}
	}

	theFinder.findORFsDirect(orf3StrandsDirect, 2);
	//finds all possible ORFs in reading frame 3 for the direct strand

	if (orf3StrandsDirect.empty()) {
		outStream << "No ORFs were found in reading frame 3 on the direct strand." << endl;
		outStream << endl;
	}

	else {
		int counter = 1;
		for (int i = 0; i < orf3StrandsDirect.size(); i++) {
			outStream << ">ORF number " << counter << " in reading frame 3 on the direct strand" <<
			" extends from base " << theFinder.theStartIndexes[i] << " to base " << theFinder.theEndIndexes[i] << endl;
			outStream << orf3StrandsDirect[i] << endl;
			outStream << endl;
			outStream << ">Translation of ORF number " << counter << " in reading frame 3 on the direct strand: " <<
			theFinder.concProteinVector[i]; 
			outStream << endl; 
			outStream << endl;
			counter++; 
		}
	}

	theFinder.findORFsReverse(orf1StrandsReverse, 0);
	//finds all possible ORFs in reading frame 1 for the reverse strand

	if (orf1StrandsReverse.empty()) {
		outStream << "No ORFs were found in reading frame 1 on the reverse strand." << endl;
		outStream << endl;
	}

	else {
		int counter = 1;
		for (int i = 0; i < orf1StrandsReverse.size(); i++) {
			outStream << ">ORF number " << counter << " in reading frame 1 on the reverse strand" <<
			" extends from base " << theFinder.theStartIndexes[i] << " to base " << theFinder.theEndIndexes[i] << endl;
			outStream << orf1StrandsReverse[i] << endl;
			outStream << endl;
			outStream << ">Translation of ORF number " << counter << " in reading frame 1 on the reverse strand: " <<
			theFinder.concProteinVector[i]; 
			outStream << endl;
			outStream << endl;
			counter++;
		}
	}


	theFinder.findORFsReverse(orf2StrandsReverse, 1);
	//finds all possible ORFs in reading frame 2 for the reverse strand

	if (orf2StrandsReverse.empty()) {
		outStream << "No ORFs were found in reading frame 2 on the reverse strand." << endl;
		outStream << endl;
	}

	else {
		int counter = 1;
		for (int i = 0; i < orf2StrandsReverse.size(); i++) {
			outStream << ">ORF number " << counter << " in reading frame 2 on the reverse strand" <<
			" extends from base " << theFinder.theStartIndexes[i] << " to base " << theFinder.theEndIndexes[i] << endl;
			outStream << orf2StrandsReverse[i] << endl;
			outStream << endl;
			outStream << ">Translation of ORF number " << counter << " in reading frame 2 on the reverse strand: " <<
			theFinder.concProteinVector[i]; 
			outStream << endl; 
			outStream << endl;
			counter++;
		}
	}

	theFinder.findORFsReverse(orf3StrandsReverse, 2);
	//finds all possible ORFs in reading frame 3 for the reverse strand

	if (orf3StrandsReverse.empty()) {
		outStream << "No ORFs were found in reading frame 3 on the reverse strand." << endl;
		outStream << endl;
	}

	else {
		int counter = 1;
		for (int i = 0; i < orf3StrandsReverse.size(); i++) {
			outStream << ">ORF number " << counter << " in reading frame 3 on the reverse strand" <<
			" extends from base " << theFinder.theStartIndexes[i] << " to base " << theFinder.theEndIndexes[i] << endl;
			outStream << orf3StrandsReverse[i] << endl;
			outStream << endl;
			outStream << ">Translation of ORF number " << counter << " in reading frame 3 on the reverse strand: " <<
			theFinder.concProteinVector[i];  
			outStream << endl;
			outStream << endl;
			counter++;
		}
	}

	outStream.close(); 
	

	return 0;
}
