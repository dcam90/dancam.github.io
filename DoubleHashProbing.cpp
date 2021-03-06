/******************************************************************************
Title       : DoubleHashProbing.cpp
Author      : Dan Cambitsis
Created on  : 3/31/2016
Description : Double hash implementation.
******************************************************************************/

template <typename HashedObj>
bool DoubleHashTable<HashedObj>::Contains(const HashedObj & x) {
  return IsActive(FindPos(x));
}

template <typename HashedObj>
void DoubleHashTable<HashedObj>::MakeEmpty() {
  current_size_ = 0;
  for (auto & entry : array_)
    entry.info_ = kEmpty;
}

template <typename HashedObj>
bool DoubleHashTable<HashedObj>::Insert(const HashedObj & x) {
  // Insert x as active.
  int current_pos = FindPos(x);
  if (IsActive(current_pos)) {
    return false;
  }
  
  array_[current_pos].element_ = x;
  array_[current_pos].info_ = kActive;
  
  // Rehash; see Section 5.5.
  if (++current_size_ > array_.size() / 2) {
    Rehash();
  }
  
  return true;
}
    
template <typename HashedObj>
bool DoubleHashTable<HashedObj>::Insert(HashedObj && x) {
  // Insert x as active.
  int current_pos = FindPos(x);
  if (IsActive(current_pos)) {
    return false;
  }
  
  array_[current_pos] = std::move(x);
  array_[current_pos].info_ = kActive;
  
  // Rehash; see Section 5.5.
    if (++current_size_ > array_.size())
      Rehash();
    
    return true;
}

template <typename HashedObj>
bool DoubleHashTable<HashedObj>::Remove(const HashedObj & x) {
  int current_pos = FindPos(x);
  if (!IsActive(current_pos)) {
    return false;
  }
  
  array_[current_pos].info_ = kDeleted;
  return true;
}

template <typename HashedObj>
int DoubleHashTable<HashedObj>::FindPos(const HashedObj & x) {
  probe_count_ = 1; //reset the probe count to 1
  unsigned int current_pos = InternalHash(x); //calculate the initial hash
  unsigned int copy_current_pos = current_pos; //copy that value
  unsigned int offset = R_VALUE - (current_pos % R_VALUE); //calculate the offset (second hash)
  int counter = 1;

  while (array_[current_pos].info_ != kEmpty && array_[current_pos].element_ != x ) {
    // Compute ith probe.
    current_pos = ((counter * offset) + copy_current_pos) % array_.size();
    ++counter; //increment the counter
    ++collisions_; //increment collisions because we hit a non-empty bucket
    ++probe_count_;
    if (current_pos >= array_.size()) {
      current_pos -= array_.size( );
    }
  }
  return current_pos;
}

template <typename HashedObj>
void DoubleHashTable<HashedObj>::Rehash() {
  int store_collisions = collisions_;
  vector<HashEntry> old_array = array_;
  // Create new double-sized, empty table.
  array_.resize(NextPrime(2 * old_array.size()));
  for (auto & entry : array_)
    entry.info_ = kEmpty;
  
  // Copy table over.
  current_size_ = 0;
  for (auto & entry : old_array)
    if (entry.info_ == kActive)
      Insert(std::move(entry.element_));
  collisions_ = store_collisions;
}
