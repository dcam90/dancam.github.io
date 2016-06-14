/******************************************************************************
Title       : LinearProbing.h
Author      : Dan Cambitsis
Created on  : 3/31/2016
Description : Header file for linear probing.
******************************************************************************/

#ifndef CSCI335_HASHING_LINEAR_PROBING_H_
#define CSCI335_HASHING_LINEAR_PROBING_H_

#include <vector>
#include <iostream>

using namespace std;

template <typename HashedObj>
class LinearHashTable {
public:
	enum EntryType {kActive, kEmpty, kDeleted};
	explicit LinearHashTable(int size = 101) : array_(NextPrime(size)) {
	  MakeEmpty(); 
	}
  LinearHashTable(const LinearHashTable &a_hash_table) = default;
  LinearHashTable(LinearHashTable &&a_hash_table) = default;
  LinearHashTable &operator=(const LinearHashTable &a_hash_table) = default;
 	LinearHashTable &operator=(LinearHashTable &&a_hash_table) = default;
  ~LinearHashTable() = default;

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
  int ReturnCollisions() const {
    return collisions_;
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
  struct HashEntry {
    HashedObj element_;
    EntryType info_;
    
    HashEntry(const HashedObj &element = HashedObj{}, EntryType infotype = kEmpty)
     : element_{element}, info_{infotype} {}    
    HashEntry(HashedObj &&element, EntryType infotype = kEmpty)
     : element_{std::move(element)}, info_{infotype} { }
  };
  // The hash table.
  vector<HashEntry> array_;
  // Number of elements in the hash table.
  unsigned int current_size_ = 0;

  // @param current_pos: position in the hash table.
  // @return true if item in that position is kActive,
  //    false otherwise.
  // No error checking is performed (i.e. it is assumed
  //   that current_pos is within the correct range).
  bool IsActive(int current_pos) const { 
    return array_[ current_pos ].info_ == kActive; 
  }

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

#include "LinearProbing.cpp"  // For template compilation.
#endif  // CSCI335_HASHING_LINEAR_PROBING_H_