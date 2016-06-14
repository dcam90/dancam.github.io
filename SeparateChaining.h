/******************************************************************************
Title       : SeparateChaining.h
Author      : Dan Cambitsis
Created on  : 3/31/2016
Description : Header file for separate chaining.
******************************************************************************/

#ifndef CSCI335_HASHING_CHAIN_PROBING_H_
#define CSCI335_HASHING_CHAIN_PROBING_H_

#include <vector>
#include <list>
#include <algorithm>
#include <iterator>

using namespace std;

template <typename HashedObj>
class ChainHashTable {
public:
	explicit ChainHashTable(int size = 101) : array_(NextPrime(size)) {
	  MakeEmpty(); 
	}
  ChainHashTable(const ChainHashTable &a_hash_table) = default;
  ChainHashTable(ChainHashTable &&a_hash_table) = default;
  ChainHashTable &operator=(const ChainHashTable &a_hash_table) = default;
 	ChainHashTable &operator=(ChainHashTable &&a_hash_table) = default;
  ~ChainHashTable() = default;

  // @param x: A given item.
  // @return true if item is in the hash table and false otherwise.
  bool Contains(const HashedObj & x);

  // Empties the hash table.
 	void MakeEmpty();

  // @param x: Item to insert.
  // @return true if insertion was succesfull, false otherwise
  //   (i.e. when x is already in the hash table).
  // Insertion may lead to rehashing.
  bool Insert(const HashedObj & x);

  // Same as above Insert for x being an rvalue reference.
  bool Insert(HashedObj && x);
  
  // @param x: Item to be removed.
  // @return true if succesfull, false if x is not found in the
  //   hash table.
  bool Remove(const HashedObj & x);

  // no param
  // @return the amount of collisions in the table
  // note: this function returns 0, no collisions in separate chaining
  int ReturnCollisions() const {
    return 0;
  }

  // no param
  // @return the amount of elements in the table
  int ReturnElementCount() const {
    return current_size_;
  }

  // no param
  // @return the size of the table
  int ReturnTableSize() const {
    return array_.size();
  }

  // no param
  // @return the probes used to find a specific element
  int ReturnProbeCount() const {
    return probe_count_;
  }
private:
  // Each hash entry contains the item and its type.
  int collisions_ = 0, probe_count_ = 0;
  // The hash table.
  vector<list<HashedObj>> array_;
  // Number of elements in the hash table.
  unsigned int current_size_ = 0;

  // @param x: a given item.
  // @returns the location of x in the hash table if item
  //   is there (i.e. a HashEntry with element_ equal to x
  //   and info_ being kActive). If x is not in the 
  //   hash table, the function returns the position of
  //   insertion of x.
  int FindPos(const HashedObj & x);

  // Performs rehashing by creating a new hash table having
  // size being equal to the next prime greater than or equal
  // to the double of the current table size.
  // Note that table size is _array.size();
  void Rehash(); 

  // @param x: a given item.
  // Returns the hash value of x.
  // Assumes that a class hash<HashedObj> has been defined,
  // with an overloaded () operator.
  size_t InternalHash(const HashedObj & x) const {
    static hash<HashedObj> hf;
    return hf(x) % array_.size();
  }
};

#include "SeparateChaining.cpp"  // For template compilation.
#endif  // CSCI335_HASHING_CHAIN_PROBING_H_