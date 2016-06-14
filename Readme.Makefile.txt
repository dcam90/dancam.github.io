This project involves the creation of Chains (containers that imitate STL vectors) and various functions involved in said Chains.

- Initiation of all Chains are empty and thus return a size of 0. 
- ReadChain() prompts the user to enter a size for a Chain and then prompts the user to enter elements up to the selected size.
- The "big five" (copy constructor, copy assignment operator, move constructor, move assignment operator, destructor) is exemplified here in this project.
- The project is broken down into two parts: 
	- PART I: Chains of type int are created and the "big five" is showcased. 
	- PART II: Chains of type string are created and operator overloading is showcased. 

HOW TO RUN THE PROGRAM:
(without Makefile) g++ -Wall -pedantic TestChain.cpp main.cpp -o TestChain -std=c++11
TestChain or ./TestChain
(with Makefile) make all 
TestChain or ./TestChain

BUGS/MISHAPS:

- Size() is meant to return the size of the Chain. In my program, I had it return 0. 
Frankly, I couldn't figure out how to set the default size without causing an issue. Setting the default size to 1 displayed
"7" but set the empty Chains' sizes to 1. Setting the default size to 0 set the empty Chains to 0 but the "7" wouldn't display.