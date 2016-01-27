/******************************************************************************
Title       : cambitsis_daniel_hwk3_orffinder.h
Author      : Dan Cambitsis
Created on  : 5/16/2015
Description : Prototypes for class ORF Finder.
******************************************************************************/

#ifndef _CAMBITSIS_DANIEL_HWK3_ORFFINDER_H_
#define _CAMBITSIS_DANIEL_HWK3_ORFFINDER_H_
#include "cambitsis_daniel_hwk3_codon.h"
#include "cambitsis_daniel_hwk3_orf.h"


std::string reverseStrandCreation(std::string strand); 
/*creates reverse strand from direct strand
@param: string strand (from input file)
@pre: strand contains A, G, T, C only 
@post: none
returns direct strand reversed 
*/
void swap (char & v1, char & v2);
/*reverses the individual characters within the direct strand
@param: v1 and v2, both characters and passed by reference
@pre: strand contains A, G, T, C only 
@post: characters are swapped within strand thus generating reverse strand
no return
*/
void reverseStrandConversion(std::string strand, std::string & reverseStrand); 
/*swaps the reverse strand to the appropriate complimentary bases of the direct strand
@param: string strand, string reverseStrand (passed by reference)
@pre: strand and reverse strand contain A, G, T, C only, reverse strand is direct strand reversed
@post: reverse strand: all As become Ts, Gs become Cs, etc.
no return
*/

class ORF_Finder { //ORF_Finder class
public:
	ORF_Finder() : theStrand(" "), theReverseStrand(" ") { } //default constructor, not used
	ORF_Finder(std::string strand, std::string reverseStrand) : theStrand(strand), theReverseStrand(reverseStrand) { }
	//overloaded constructor, store strand and reverse strand in ORF_Finder
	void findORFsDirect(std::vector<std::string> & orfStrands, int index); 
	/*responsible for organizing and creating all direct strand codons and ORFs
	@param: type string vector by reference, int index
	@pre: orfStrands vector is initially empty and index is set to be based off reading frame (0 -> RF1, 1 -> RF2, 2 -> RF3)
	@post: vector is filled and used in outStream, codons and ORFs are created based off input file
	no return
	*/
	void findORFsReverse(std::vector<std::string> & orfStrands, int index); 
	/*responsible for organizing and creating all reverse strand codons and ORFs
	@param: type string vector by reference, int index
	@pre: orfStrands vector is initially empty and index is set to be based off reading frame (0 -> RF1, 1 -> RF2, 2 -> RF3)
	@post: vector is filled and used in outStream, codons and ORFs are created based off input file
	no return
	*/
	void mRNAProteinCreation(std::string theCodon);
	/*responsible for creating messenger RNA strand and protein strand
	@param: string theCodon (a string type of an object of class Codon found in findORFsDirect)
	@pre: theCodon is a length of three characters
	@post: mRNA is generated (all Ts are converted to Us) and is used to create protein
	no return
	*/
	std::vector<int> theStartIndexes; //vector to store all start indexes (first ATG in every ORF)
	std::vector<int> theEndIndexes; //vector to store all end indexes (stop codon in every ORF)
	std::vector<std::string> theProtein; //stores all individual proteins
	std::vector<std::string> concProteinVector; //concatenated proteins (creates a strand), used in main
private: 
	std::string theStrand; //sets theStrand = strand
	std::string theReverseStrand; //sets theReverseStrand = reverseStrand
};

#endif /* _CAMBITSIS_DANIEL_HWK3_ORFFINDER_H_ */
