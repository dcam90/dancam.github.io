/******************************************************************************
Title       : Chain.h
Author      : Dan Cambitsis
Created on  : 2/14/2016
Description : Header file for Chain.
******************************************************************************/

#ifndef CSCI335_HOMEWORK1_CHAIN_
#define CSCI335_HOMEWORK1_CHAIN_
#include <cstddef>

using namespace std;

template <typename Object>
class Chain {
public:
  explicit Chain(const Object & value = Object()) : size_{1} { //constructor for Chain
    array_ = new Object{value};
  }
  Chain(size_t num) : array_{new Object[num]}, size_{num} { } //loaded constructor for temp
  Chain(const Chain & rhs) : size_{rhs.size_} {
    array_ = new Object[size_];

    for (unsigned int i = 0; i < size_; i++) {
      array_[i] = rhs.array_[i];
    }
  }
  /*copy constructor
  @param: const Chain & rhs
  @pre: rhs.size_ and rhs.array_ are valid
  @post: sets the new array and size to rhs' array and size
  no return
  */
  Chain & operator=(const Chain & rhs);
  /*copy assignment operator
  @param: const Chain & rhs
  @pre: rhs.size_ and rhs.array_ are valid
  @post: swaps a newly created temp's size and array with array_ and size_
  return *this
  */
  Chain(Chain && rhs) : array_{rhs.array_}, size_{rhs.size_} {
    rhs.array_ = nullptr;
    rhs.size_ = 0;
  }
  /*move constructor
  @param: Chain && rhs
  @pre: rhs.size_ and rhs.array_ are valid
  @post: sets array_ to rhs' array and size_ to rhs' size, sets rhs' array and size to null (or 0)
  no return
  */
  Chain & operator=(Chain && rhs);
  /*move assignment operator
  @param: const Chain && rhs
  @pre: rhs.size_ and rhs.array_ are valid
  @post: swaps size_ with rhs' size and array_ with rhs' array
  return *this
  */
  void print(ostream & out) const;
  /*print function (paired with overloaded << operator)
  @param: ostream & out
  @pre: none
  @post: prints contents of array_
  no return
  */
  void ReadChain();
  /*read function (reads input from user)
  @param: none
  @pre: user enters valid size and contents for array
  @post: size is set and array is filled
  no return
  */
  size_t Size() const;
  /*Size function (returns the size of the array)
  @param: none
  @pre: none
  @post: prints the size of the array
  return size_
  */
  Chain & operator+=(const Chain & rhs);
  /*overloaded += operator (paired with overloaded + operator for adding two Chains)
  @param: const Chain & rhs
  @pre: rhs.size_ and rhs.array_ are valid
  @post: fills a temp Chain with rhs' size and array values
  return *this
  */
  Chain operator+(const Chain & rhs) const;
  /*overloaded + operator (paired with overloaded += operator for adding two Chains)
  @param: const Chain & rhs
  @pre: rhs.size_ and rhs.array_ are valid, temp is valid
  @post: prepares temp to be returned (combination of two Chains)
  return temp
  */
  Chain operator+(const Object & rhs) const;
  /*overloaded + operator (to add string literal to the end of a Chain)
  @param: const Object & rhs
  @pre: rhs.size_ and rhs.array_ are valid, temp is valid
  @post: prepares temp to be returned (combination of a Chain + string literal)
  return temp
  */
  Object & operator[](int num) const;
  /*overloaded [] operator
  @param: int num
  @pre: num is valid, mustn't be greater than the array's size or less than 0
  @post: none
  return array_[num]
  */
  ~Chain(); //destructor (destroys array_)

private:
  Object *array_; //dynamic array
  size_t size_; //size of array
};


#endif //CSCI_335_HOMEWORK1_CHAIN_
