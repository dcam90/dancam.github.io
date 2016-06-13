/******************************************************************************
Title       : TestChain.cpp
Author      : Dan Cambitsis
Created on  : 2/14/2016
Description : Implementation file for Chain.
******************************************************************************/

#include <iostream>
#include <string>
#include <cstdlib>
#include <stdexcept>

#include "Chain.h"
#include "main.cpp"

using namespace std;

template <typename Object>
Chain<Object> &Chain<Object>::operator=(const Chain<Object> & rhs) { //copy assignment operator
	if (this != &rhs) {
		Chain temp(rhs); //create a temp to hold rhs
		std::swap(size_, temp.size_); //swap size_ and temp's size
		std::swap(array_, temp.array_); //swap array_ with temp's array
	}

	return *this; //return rhs
}

template <typename Object>
Chain<Object> &Chain<Object>::operator=(Chain<Object> && rhs) { //move assignment operator
	if (this != &rhs) {
		std::swap(size_, rhs.size_); //swap size_ with rhs' size
		std::swap(array_, rhs.array_); //swap array_ with rhs' array
	}
		
	return *this; //return rhs
}

template <typename Object>
void Chain<Object>::print(ostream & out) const { //print function used in overloaded << operator
	for (unsigned int i = 0; i < size_; i++) {
		out << array_[i] << " "; //print the contents of the array
	}
}

template <typename Object>
void Chain<Object>::ReadChain() {
	int count = 0;

	cout << "Enter a size: ";
	cin >> size_; //user enters desired size

	array_ = new Object[size_]; //create a new dynamic array of size "size_"

	for (unsigned int i = 0; i < size_; i++) {
		cout << "Enter element " << count + 1 << ": "; //user enters each individual element
		cin >> array_[i];
		count++;
	}
}

template <typename Object>
size_t Chain<Object>::Size() const {
	return 0; //returns the size of the array 
}

template <typename Object>
Chain<Object> &Chain<Object>::operator+=(const Chain<Object> & rhs) { //overloaded += operator
	Chain temp(size_ + rhs.size_); //create temp of size "size_ + rhs.size_" (in main: a's size + b's size)

	for (unsigned int i = 0; i < size_; i++) {
		temp.array_[i] = array_[i]; //set first portion of temp's array to a's array
	}

	int j = 0;
	for (unsigned int k = size_; k < size_ + rhs.size_; k++, j++) {
		temp.array_[k] = rhs.array_[j]; //set the remainder of temp's array to b's array
	}

	*this = temp; //set *this to temp
	return *this; //return temp (combination of two Chains)
}

template <typename Object>
Chain<Object> Chain<Object>::operator+(const Chain<Object> & rhs) const { //overloaded to add two Chains
	Chain temp(*this); //create a temp to hold rhs
	temp += rhs; //add temp to rhs and set it equal to temp
	return temp; //return the temp (should be combination of two Chains)
}

template <typename Object>
Chain<Object> Chain<Object>::operator+(const Object & rhs) const { //overloaded to add literal string
	Chain temp(size_ + 1); //create temp and set its size to size_ + 1 (to hold new literal string value)

	unsigned int i;
	for (i = 0; i < size_; i++) {
		temp.array_[i] = array_[i]; //set temp equal to rhs' array_
	}
	temp.array_[i] = rhs; //the last value of temp's array is equal to rhs (the string literal)
	return temp; //return the altered Chain (should have the string literal as its last value)
}

template <typename Object>
Object &Chain<Object>::operator[](int num) const{
	int size = size_; //sets size's value to size_ (to avoid unsigned vs. signed warning in compiler)

	if (num < 0 || num > size) {
		throw out_of_range("Index is out of range, program will now terminate.");
	}

	return array_[num]; //return array_'s value at num
	
}

template <typename Object>
Chain<Object>::~Chain<Object>() { //destructor
	delete[] array_; //delete the dynamic array
}