/******************************************************************************
Title       : main.cpp
Author      : Dan Cambitsis
Created on  : 11/17/2015
Description : An executable main that essentially asserts all of the conditions of a multistack.
Build with  : g++ -Wall -pedantic cambitsis_daniel_p2_imp.cpp main.cpp -o main -std=c++0x
Usage       : ./main
Dependencies: cambitsis_daniel_p2_header.hpp, cambitsis_daniel_p2_imp.cpp
******************************************************************************/

#include <iostream>
#include <cassert>
#include <stdexcept> 
#include <cstdlib>
#include "cambitsis_daniel_p2_header.hpp"

using namespace std;

int main() {
  MultiStack stackA;
  assert(stackA.isEmpty()==true);
  stackA.push('a');
  stackA.push('b');
  stackA.push('a');
  stackA.push('b');
  stackA.push('c');
  stackA.push('a');
  assert(stackA.isEmpty()==false);
  assert(stackA.getSize()==6);
  assert(stackA.getRepeatCounts()==3);
  assert(stackA.getUniqueCount()==3);

  // test stack B
  MultiStack stackB(stackA);
  assert(stackB.multiPop()=='a');
  assert(stackB.isEmpty()==false);
  // these next 3 statements have been fixed
  assert(stackB.getSize()==3);
  assert(stackB.getRepeatCounts()==1);
  assert(stackB.getUniqueCount()==2);

  // test stack A again...
  assert(stackA.isEmpty()==false);
  assert(stackA.getSize()==6);
  assert(stackA.getRepeatCounts()==3);
  assert(stackA.getUniqueCount()==3);

  // test stack C
  MultiStack stackC;
  assert(stackC.isEmpty()==true);
  assert(stackC.getSize()==0);
  assert(stackC.getRepeatCounts()==0);
  assert(stackC.getUniqueCount()==0);

  stackC = stackA;

  assert(stackC.multiPop()=='a');
  assert(stackC.isEmpty()==false);
  assert(stackC.getSize()==3);
  assert(stackC.getRepeatCounts()==1);
  assert(stackC.getUniqueCount()==2);

  
  // test stack A again...
  assert(stackA.isEmpty()==false);
  assert(stackA.getSize()==6);
  assert(stackA.getRepeatCounts()==3);
  assert(stackA.getUniqueCount()==3);

  // testing a new Stack X...

  MultiStack stackX;
  stackX.push('1');
  stackX.push('#');
  stackX.push('!');
  stackX.push('@');
  stackX.push('!');
  assert(stackX.getSize()==5);
  assert(stackX.getRepeatCounts()==2);
  assert(stackX.getUniqueCount()==4);

  return 0;

}
