/******************************************************************************
Title       : main.cpp
Author      : Dan Cambitsis
Created on  : 2/15/2016
Description : Main file for Chain, executes certain functions to display Chain's capability.
Build with  : g++ -Wall -pedantic TestChain.cpp main.cpp -o testchain -std=c++0x
Usage       : ./testchain or testchain (or ./TestChain if Makefile is used)
Dependencies: Chain.h and TestChain.cpp
******************************************************************************/

#include <iostream>
#include <string>
#include <cstdlib>

#include "Chain.h"

using namespace std;

void TestPart1();
void TestPart2();

template <typename Object>
ostream & operator<<(ostream & out, const Chain<Object> & rhs) {
	rhs.print(out);
	return out;
}

int main(int argc, char **argv) {
   TestPart1();
   TestPart2();
  return 0;
}

void TestPart1() {
	cout << "---PART 1---" << endl;
	Chain<int> a, b; //Two empty Chains
	cout << a.Size() << " " << b.Size() << endl; //yields 0 0

	Chain<int> d{7}; //chain containing 7 should be created
	cout << d << endl;

	a.ReadChain(); //user enters a chain
	cout << a << endl; //output should be what user entered

	b.ReadChain();
	cout << b << endl;

	Chain<int> c{a}; //copy constructor
	cout << c << endl;
	cout << a << endl;

	a = b; //copy assignment operator
	cout << a << endl;

	Chain<int> e = std::move(c); //move constructor
	cout << e << endl;
	cout << c << endl;

	a = std::move(e); //move assignment operator
	cout << a << endl;
	cout << e << endl;

} //destructor will be called

void TestPart2() {
	cout << "---PART 2---" << endl;
	Chain<string> a, b;

	a.ReadChain(); //user provides input for Chain a
	cout << a << endl;

	b.ReadChain(); //user provides input for Chain b
	cout << b << endl; 

	cout << a + b << endl; //concatenates the two Chains

	Chain<string> d = a + b;
	cout << d << endl;

	cout << d + "hi_there" << endl; //adds an element to the end

	cout << a[2] << endl; //should print 3rd element, exception is thrown if it is out of range

	b[1] = "b_string";
	cout << b << endl;
	b[0] = "a_string";
	cout << b;
}