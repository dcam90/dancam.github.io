/******************************************************************************
Title       : cambitsis_daniel_hwk3_orf.h
Author      : Dan Cambitsis
Created on  : 5/16/2015
Description : Prototypes for class ORF.
******************************************************************************/

#ifndef _CAMBITSIS_DANIEL_HWK3_ORF_H_
#define _CAMBITSIS_DANIEL_HWK3_ORF_H_

class ORF { //ORF class
public: 
	ORF() : anORF(" "), aStartIndex(0) { } //default constructor, not used
	ORF(std::string codonsCopy, int startIndex, int endIndex) : anORF(codonsCopy), aStartIndex(startIndex), anEndIndex(endIndex) { }
	//overloaded constructor, sets anORF = codonsCopy, aStartIndex = startIndex, and anEndIndex = endIndex
	std::string getAnORF() const; 
	/*returns an ORF (concatenation of codons) back to the ORF finder function
	@param: none
	@pre: codons were successfully created and concatenated
	@post: none
	returns anORF
	*/
	int getStartIndex() const; 
	/*returns start index back to the ORF finder function, later to be used in main
	@param: none
	@pre: index was successfully incremented
	@post: none
	returns aStartIndex
	*/
	int getEndIndex() const; 
	/*returns last index back to the ORF finder function, later to be used in main
	@param: none
	@pre: index was successfully incremented
	@post: none
	returns anEndIndex
	*/
private:
	std::string anORF; //set equal to codonsCopy
	int aStartIndex; //set equal to startIndex
	int anEndIndex; //set equal to endIndex
};

#endif /* _CAMBITSIS_DANIEL_HWK3_ORF_H_ */
