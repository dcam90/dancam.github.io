/******************************************************************************
Title       : SequenceMap.h
Author      : Dan Cambitsis
Created on  : 3/8/2016
Description : Header + implementation for a sequence map.
******************************************************************************/

#ifndef SEQUENCE_MAP_
#define SEQUENCE_MAP_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class SequenceMap {
public:
	SequenceMap(const SequenceMap & rhs) = default; //copy constructor set to default
	SequenceMap & operator=(const SequenceMap & rhs) = default; //copy assignment operator set to default
	SequenceMap(SequenceMap && rhs) = default; //move constructor set to default
	SequenceMap & operator=(SequenceMap && rhs) = default; //move assignment operator set to default
	~SequenceMap() = default; //destructor set to default

	SequenceMap(const string & a_rec_seq, const string & an_enz_acro) : recognition_sequence_{a_rec_seq} {
		enzyme_acronyms_.push_back(an_enz_acro);
	} //loaded constructor 

	bool operator<(const SequenceMap & rhs) const {
		return recognition_sequence_ < rhs.recognition_sequence_;
	} //overloaded < operator to allow for comparison

	/**
     * Returns a recognition sequence.
     */
	string GetRecoSeq() const {
		return recognition_sequence_;
	}

	/**
     * Sets enzAcros to all contents of enzyme_acronyms_ vector and returns it.
     */
	string GetTheAcros() const {
		string enzAcros;

		for (unsigned int i = 0; i < enzyme_acronyms_.size(); i++) {
			enzAcros += enzyme_acronyms_[i] + " ";
		}

		return enzAcros;
	}

	/**
     * Merges contents of vectors based on recognition sequence.
     */
	void Merge(const SequenceMap & other_sequence) {
		enzyme_acronyms_.insert(enzyme_acronyms_.end(), other_sequence.enzyme_acronyms_.begin(), other_sequence.enzyme_acronyms_.end());
		//merge the two vectors, essentially changing the object's vector (adding other_sequence's vector to it)
		
	}

private:
	string recognition_sequence_;
	vector<string> enzyme_acronyms_;
};

ostream& operator<<(ostream & out, const SequenceMap & rhs) {
	return out;
} //overloaded << operator to allow for output

#endif