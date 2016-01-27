/******************************************************************************
Title       : cambitsis_daniel_hwk3_codon.h
Author      : Dan Cambitsis
Created on  : 5/16/2015
Description : Prototypes for class Codon.
******************************************************************************/

#ifndef _CAMBITSIS_DANIEL_HWK3_CODON_H_
#define _CAMBITSIS_DANIEL_HWK3_CODON_H_

class Codon { //Codon class
public:
	Codon() : aTriplet(" ") { } //default constructor, not used but needed since loaded constructor was called
	Codon(std::string triplet) : aTriplet(triplet) { } //loaded constructor, sets aTriplet = triplet
	std::string getATriplet() const; 
	/*returns the triplet back to the ORF finder function
	@param: none
	@pre: triplet was created within ORF finder function
	@post: none
	returns aTriplet
	*/
private:
	std::string aTriplet; //set equal to triplet 
};

#endif /* _CAMBITSIS_DANIEL_HWK3_CODON_H_ */
