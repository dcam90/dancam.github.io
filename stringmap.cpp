/******************************************************************************
Title       : daniel_cambitsis_project3_imp.cpp
Author      : Dan Cambitsis
Created on  : 12/20/2015
Description : Executable for daniel_cambitsis_project3_header.hpp
******************************************************************************/
#include <iostream>
#include <string>
#include <cassert>
#include <stdexcept> 
#include <cstdlib>
#include <sstream>
#include "daniel_cambitsis_project3_header.hpp"

using namespace std;

StringMap::StringMap(const StringMap& newSM) {
	root = privateCopy(newSM.root); //set root to the privateCopy result
}

StringMap &StringMap::operator=(const StringMap& newSM) {
	if (newSM.root != nullptr) {
		if (root != nullptr) {
			delete root;
		}

		else {
			root = privateCopy(newSM.root);
		}
	}

	else {
		if (root != nullptr) {
			delete root;
		}

		root = nullptr;
	}

	return *this;
}

void StringMap::privateClear(node* thePtr) {
	if(thePtr != nullptr) { //if the tree has nodes ...
		if (thePtr -> left != nullptr) { //if the left side isn't null ...
			privateClear(thePtr -> left); //re run the function with left
		}

		if (thePtr -> right != nullptr) { //if the right side isn't null ...
			privateClear(thePtr -> right); //re run the function with right
		}

		count--; //decrement the count
		delete thePtr; //delete thePtr
	}
}

bool StringMap::privateDeleteValue(node* &thePtr, string key) {
	node* current;
	node* temp1 = thePtr;
	if (temp1 == nullptr) {
		 return false;
	}

	while (temp1 != nullptr) {
		if (temp1 -> nodeKey == key) {
			if (temp1 == thePtr) { //if the key matched is in the root ...
				if (temp1 -> left == nullptr) {
					current = temp1 -> right;
				}

				else {
					current = temp1 -> left;
				}
			}
			break;
		}

		else { //the key matched is not in the root ...
			current = temp1;
			if(key > (temp1 -> nodeKey)) {
				temp1 = temp1 -> right;
			}

			else {
				temp1 = temp1 -> left;
			}
		}
	}

	if (temp1 == nullptr) {
		return false; //key does not exist, return false
	}

	//CASE 0: node to be deleted is the root node
	if (temp1 == thePtr) {
		if ((temp1 -> left == nullptr && temp1 -> right != nullptr) || (temp1 -> left != nullptr && temp1 -> right == nullptr)) {
		// only right leaf, set right leaf to new root
			if (temp1 -> left == nullptr && temp1 -> right != nullptr) {
				if (temp1 -> left == current) {
					thePtr = current;
					delete temp1;
					temp1 = nullptr;
				}
				else {
					thePtr = current;
					delete temp1;
					temp1 = nullptr;
				}
			}

			else { //only left leaf, set left leaf to new root
				if (temp1 -> left == current) {
					thePtr = current;
					delete temp1;
					temp1 = nullptr;
				}
				else {
					thePtr = current;
					delete temp1;
					temp1=nullptr;
				}
			}
		return true;
		}

		if (temp1 -> left == nullptr && temp1 -> right == nullptr) {
			clear(); //if the root node is by itself, just clear the entire tree
			return true;
		}
	}
	
	// CASE 1: node has a single child
	if ((temp1 -> left == nullptr && temp1 -> right != nullptr) || (temp1 -> left != nullptr && temp1 -> right == nullptr)) {
		// only right leaf
		if (temp1 -> left == nullptr && temp1 -> right != nullptr) {
			if (current -> left == temp1) {
				current -> left = temp1 -> right;
				delete temp1;
				temp1 = nullptr;
			}
			else {
				current -> right = temp1 -> right;
				delete temp1;
				temp1 = nullptr;
			}
		}

		else { //only left leaf
			if (current -> left == temp1) {
				current -> left = temp1 -> left;
				delete temp1;
				temp1 = nullptr;
			}
			else {
				current -> right = temp1 -> left;
				delete temp1;
				temp1=nullptr;
			}
		}
		return true;
	}
	// CASE 2: node is a leaf node (no children)
	if (temp1 -> left == nullptr && temp1 -> right == nullptr) {
		if (current -> left == temp1) {
			current -> left = nullptr;
		}
		else {
			current -> right = nullptr;
		}

		delete temp1;
		return true;
	}
	// CASE 3: node has two children
	if (temp1 -> left != nullptr && temp1 -> right != nullptr) {
		node* check = temp1 -> right;
		if ((temp1 -> left == nullptr) && (temp1 -> right == nullptr)) {
			temp1 = check;
			delete check;
			temp1 -> right = nullptr;
		}

		else { 
			if ((temp1 -> right) -> left != nullptr) {
				node* left1;
				node* left2;
				left2 = temp1 -> right;
				left1 = (temp1 -> right) -> left;

				while(left1 -> left != nullptr) {
					left2 = left1;
					left1 = left1 -> left;
				}

				temp1 -> nodeKey = left1 -> nodeKey;
				delete left1;
				left2 -> left = nullptr;
			}

			else {
				node* temp = temp1 -> right;
				temp1 -> nodeKey=temp -> nodeKey;
				temp1->right=temp -> right;
				delete temp;
			}
		}

		return true;
	}

	return true;
}

StringMap::node* StringMap::privateCopy(const node* newSM) {
	if (newSM == nullptr) {
		return nullptr; //if newSM is invalid, return nullptr
	}

	node* copy = new node; //else, create a copy node
	copy -> nodeValue = newSM -> nodeValue; 
	copy -> nodeKey = newSM -> nodeKey;
	copy -> left = privateCopy(newSM -> left);
	copy -> right = privateCopy(newSM -> right);
	//copy all values 

	return copy; //return the copy
}


bool StringMap::isEmpty() const {
	return root == nullptr; //returns true if root is the nullptr, otherwise false.
}

int StringMap::getSize() const {
	return count; //return the size of the tree
}

bool StringMap::addValue(string key, string value) {
	bool check = true;
	if (key.empty() || value.empty()) {
		check = false; //either key or value is empty
	}

	else { 
		node* theNode = new node;
		node* theParent;
		theNode -> nodeValue = value;
		theNode -> nodeKey = key;
		theNode -> left = nullptr;
		theNode -> right = nullptr;
		theParent = nullptr;

		if (isEmpty()) {
			root = theNode; //if the tree is empty, set the root equal to theNode
			count++; //increment the count (we've added the root)
		}

		else {
			node* temp = root;

			while (temp != nullptr) { //while temp isn't the nullptr ...
				theParent = temp; //set theParent to the temp
				if (theNode -> nodeKey > temp -> nodeKey) {
					temp = temp -> right; //traverse to the right if theNode's key > the temp's key
				}

				else { //else, traverse the left side (is less than the temp's key)
					temp = temp -> left;
				}
			}

			if (theNode -> nodeKey > theParent -> nodeKey) {
				theParent -> right = theNode; //set the right to the new node
				count++; //increment the count
			}

			else {
				theParent -> left = theNode; //else, set the left to the new node
				count++; //increment the count
			}
		}
	}

	return check; //return true (initial assumption, else return false if either key or value is empty)
}

void StringMap::clear() {
	privateClear(root); //call recursive function to delete nodes

	root = nullptr; //set the root to the nullptr
	delete root; //delete the root, no more elements in tree
}

bool StringMap::deleteValue(string key) {
	if (privateDeleteValue(root, key)) {
		count--;
		return true;
	}

	return false;
}

bool StringMap::contains(string key) {
	node* temp = root;
			
	while (temp != nullptr) { //while temp is not the nullptr ...
		if (temp -> nodeKey == key) { //if temp's key is equal to the inputted key ...
			return true; //return true (it contains)
		}

		else if (temp -> nodeKey < key) { //else if, the temp's key is less than the inputting key
			temp = temp -> right; //go to the right side
		}

		else if (temp -> nodeKey > key) {
			temp = temp -> left; //else, go to the left (less than temp's key)
		}
	}

	delete temp;
	return false; //return false (we could not find the inputted key)
}

string StringMap::getValue(string key) {
	string findValue; //create a findValue string to be set equal to a node's value
	node* temp = root;
	if (key == root -> nodeKey) { //if the key is equal to the root's key
		return root -> nodeValue; //return the root's value
	}

	else { //else, traverse the tree depending on the key's name
		while (temp != nullptr) {
			if (key == temp -> nodeKey) {
				findValue = temp -> nodeValue;
				return findValue; //findValue is only returned if it is equal to the temp's key
			}

			else if (temp -> nodeKey < key) {
				temp = temp -> right;
			}

			else if (temp -> nodeKey > key) {
				temp = temp -> left;
			}
		}
	}

	if (temp == nullptr) {
		throw logic_error("Key is not in tree, program will now terminate.");
		//error is thrown if the temp reaches a nullptr (i.e. the key doesn't exist)
	}

	delete temp;
	return findValue; //return the value
}

StringMap::~StringMap() {
	clear(); //clear everything
}
