/******************************************************************************
Title       : SeparateChaining.cpp
Author      : Dan Cambitsis
Created on  : 3/31/2016
Description : Implementation for separate chaining.
******************************************************************************/

template <typename HashedObj>
bool ChainHashTable<HashedObj>::Contains(const HashedObj & x) {
  probe_count_ = 0;
  auto & chain = array_[InternalHash(x)];
  typename list<HashedObj>::const_iterator it; //iterator declared to traverse the chain
  for (it = chain.begin(); it != chain.end(); ++it) {
    if (*it == x) { //if the iterator is equal to the inquired element ...
      ++probe_count_; //increment the probe count one last time
      break; //end the for loop
    }

    ++probe_count_; // ... else, increment the probe count for each member of the chain checked
  }
  return find(begin(chain), end(chain), x) != end(chain);
}

template <typename HashedObj>
void ChainHashTable<HashedObj>::MakeEmpty() {
  for (auto & chain : array_) {
    chain.clear();
  }
}

template <typename HashedObj>
bool ChainHashTable<HashedObj>::Insert(const HashedObj & x) {
  // Insert x as active.
  auto & chain = array_[InternalHash(x)];
  if (find(begin(chain), end(chain), x) != end(chain)) {
    return false;
  }
  
  chain.push_back(x);
  
  // Rehash; see Section 5.5.
  if (++current_size_ > array_.size()) {
    Rehash();
  }
  
  return true;
}
    
template <typename HashedObj>
bool ChainHashTable<HashedObj>::Insert(HashedObj && x) {
  // Insert x as active.
  auto & chain = array_[InternalHash(x)];
  if (find(begin(chain), end(chain), x) != end(chain)) {
    return false;
  }
  
  chain.push_back(std::move(x));
  
  // Rehash; see Section 5.5.
  if (++current_size_ > array_.size()) {
    Rehash();
  }
  
  return true;
}

template <typename HashedObj>
bool ChainHashTable<HashedObj>::Remove(const HashedObj & x) {
  auto & chain = array_[InternalHash(x)];
  auto itr = find(begin(chain), end(chain), x);

  if (itr == end(chain)) {
    return false;
  }

  chain.erase(itr);
  --current_size_;

  return true;
}

template <typename HashedObj>
void ChainHashTable<HashedObj>::Rehash() {
  vector<list<HashedObj>> old_array = array_;
  array_.resize(NextPrime(2 * array_.size()));
  for (auto & chain: array_) {
    chain.clear();
  }

  current_size_ = 0;
  for (auto & chain: old_array) {
    for (auto & x: chain) {
      Insert(std::move(x));
    }
  }
}
