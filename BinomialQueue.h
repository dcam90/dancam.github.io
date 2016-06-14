/******************************************************************************
Title       : BinomialQueue.h
Author      : Dan Cambitsis
Created on  : 3/31/2016
Description : Header file for the binomial queue implementation.
******************************************************************************/

#ifndef COURSES_CSCI335_BINOMIAL_QUEUE_H_
#define COURSES_CSCI335_BINOMIAL_QUEUE_H_

#include <iostream>
#include <vector>
#include "dsexceptions.h"
using namespace std;

// Binomial queue class
//
// CONSTRUCTION: with no parameters
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void NewInsert( x )    --> Insert x (without using merge)
// deleteMin( )           --> Return and remove smallest item
// Comparable findMin( )  --> Return smallest item
// bool isEmpty( )        --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void merge( rhs )      --> Absorb rhs into this heap
// void NewMerge ( rhs )  --> Absorb rhs into this heap (with slight improvements)
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinomialQueue {
 public:
  
  // Default constructor.
  BinomialQueue(): the_trees_(1) {
    for (auto & root : the_trees_)
      root = nullptr;
    current_size_ = 0;
  }
 
  // Copy constructor.
  BinomialQueue(const BinomialQueue &rhs): the_trees_(rhs.the_trees_.size()),
    current_size_{rhs.current_size_} { 
    for (int i = 0; i < rhs.the_trees_.size(); ++i)
      the_trees_[i] = clone(rhs.the_trees_[i]);
  }
  
  // Move constructor.
  BinomialQueue(BinomialQueue &&rhs): 
  the_trees_{std::move(rhs.the_trees_)}, current_size_{rhs.current_size_} { }
  
  // Move constructor.   
  BinomialQueue(const Comparable &item) : the_trees_(1), current_size_{1} {
    the_trees_[0] = new BinomialNode{item, nullptr, nullptr}; }
  
  // Copy assignment operator.
  BinomialQueue & operator=(const BinomialQueue &rhs) {
        BinomialQueue copy = rhs;
        std::swap(*this, copy);
        return *this;
  }
        
  // Move assignment operator.
  BinomialQueue & operator=(BinomialQueue && rhs) {
    std::swap(current_size_, rhs.current_size_);
    std::swap(the_trees_, rhs.the_trees_);
    
    return *this;
  }
 
  ~BinomialQueue() { MakeEmpty(); }

  
  // Return true if empty; false otherwise.
  bool IsEmpty() const {return current_size_ == 0;}
  
  // Returns minimum item.
  // Throws UnderflowException if empty.
  const Comparable &FindMin( ) const {
    if (IsEmpty())
      throw UnderflowException{ };
    
    return the_trees_[FindMinIndex()]->element_;
  }
  
  // Insert item x into the priority queue; allows duplicates.
  void Insert(const Comparable & x) { 
    BinomialQueue one_item_queue{x}; 
    Merge(one_item_queue); 
  }
  
  // Insert item x into the priority queue; allows duplicates.
  void Insert(Comparable && x) { 
    BinomialQueue one_item_queue{std::move(x)}; 
    Merge(one_item_queue); 
  }

  // A faster implementation of the insert method, does not use merge.
  void NewInsert(const Comparable & x) { 
    BinomialNode* theNode = new BinomialNode{x, nullptr, nullptr};
    ++current_size_;
    NewInsert(theNode, 0);
  }

  // A faster implementation of the insert method, does not use merge.
  void NewInsert(Comparable && x) {
    BinomialNode* theNode = new BinomialNode{std::move(x), nullptr, nullptr};
    ++current_size_;
    NewInsert(theNode, 0);
  }
    
  // Remove the smallest item from the priority queue.
  // Throws UnderflowException if empty.
  void DeleteMin() {
    Comparable x;
    DeleteMin(x);
  }

  // Remove the minimum item and place it in min_item.
  // Throws UnderflowException if empty.
  void DeleteMin(Comparable & min_item) {
    if (IsEmpty())
      throw UnderflowException{};

    const int min_index = FindMinIndex( );
    min_item = the_trees_[min_index]->element_;

    BinomialNode *old_root = the_trees_[min_index];
    BinomialNode *deleted_tree = old_root->left_child_;
    delete old_root;
    
    // Construct H''
    BinomialQueue deleted_queue;
    deleted_queue.the_trees_.resize(min_index + 1);
    deleted_queue.current_size_ = (1 << min_index) - 1;
    for (int j = min_index - 1; j >= 0; --j) {
      deleted_queue.the_trees_[j] = deleted_tree;
      deleted_tree = deleted_tree->next_sibling_;
      deleted_queue.the_trees_[j]->next_sibling_ = nullptr;
    }

    // Construct H'
    the_trees_[min_index] = nullptr;
    current_size_ -= deleted_queue.current_size_ + 1;

    Merge(deleted_queue);
  }

  // Make the priority queue logically empty.
  void MakeEmpty() {
    current_size_ = 0;
    for (auto & root : the_trees_)
      MakeEmpty(root);
  }

  // Merge rhs into the priority queue.
  // rhs becomes empty. rhs must be different from this.
  void Merge(BinomialQueue & rhs) {
    if( this == &rhs )    // Avoid aliasing problems
      return;

    current_size_ += rhs.current_size_;

    if (current_size_ > Capacity()) {
      int old_number_of_trees = the_trees_.size();
      int new_number_of_trees = max(the_trees_.size(), rhs.the_trees_.size()) + 1;
      the_trees_.resize(new_number_of_trees);
      for (int i = old_number_of_trees; i < new_number_of_trees; ++i) {
	         the_trees_[i] = nullptr;
      }
    }

    BinomialNode *carry = nullptr;

    for (unsigned int i = 0, j = 1; j <= current_size_; ++i, j *= 2) {
      BinomialNode *t1 = the_trees_[i];
      BinomialNode *t2 = i < rhs.the_trees_.size() ? rhs.the_trees_[ i ] : nullptr;
      
      int which_case = t1 == nullptr ? 0 : 1;
      which_case += t2 == nullptr ? 0 : 2;
      which_case += carry == nullptr ? 0 : 4;
      
      switch (which_case) {
      case 0:  // No trees.
      case 1:  // Only this tree.
	    break;
      case 2:  // Only rhs tree.
	    the_trees_[i] = t2;
	    rhs.the_trees_[i] = nullptr;
	    break;
      case 4:  // Only carry tree.
	    the_trees_[i] = carry;
	    carry = nullptr;
	    break;
      case 3:  // this and rhs trees.
	    carry = CombineTrees(t1, t2);
	    the_trees_[i] = rhs.the_trees_[i] = nullptr;
	    break;
      case 5:  // this and carry trees.
	    carry = CombineTrees(t1, carry);
	    the_trees_[i] = nullptr;
	    break;
      case 6:  // rhs and carry trees.
	    carry = CombineTrees(t2, carry);
	    rhs.the_trees_[i] = nullptr;
	    break;
      case 7: // this, rhs and carry trees.
	    the_trees_[i] = carry;
	    carry = CombineTrees(t1, t2);
	    rhs.the_trees_[i] = nullptr;
	    break;
      }
    }
    
    // Invalidate rhs tree.
    for (auto & root : rhs.the_trees_)
      root = nullptr;
    rhs.current_size_ = 0;
  }  // End of Merge Routine.

   // Merge rhs into the priority queue.
  // rhs becomes empty. rhs must be different from this.
  void NewMerge(BinomialQueue & rhs) {
    if( this == &rhs )    // Avoid aliasing problems
      return;

    current_size_ += rhs.current_size_;

    if (current_size_ > Capacity()) {
      int old_number_of_trees = the_trees_.size();
      int new_number_of_trees = max(the_trees_.size(), rhs.the_trees_.size()) + 1;
      the_trees_.resize(new_number_of_trees);
      for (int i = old_number_of_trees; i < new_number_of_trees; ++i) {
           the_trees_[i] = nullptr;
      }
    }

    BinomialNode *carry = nullptr;

    for (unsigned int i = 0, j = 1; j <= current_size_; ++i, j *= 2) {
      BinomialNode *t1 = the_trees_[i];
      BinomialNode *t2 = i < rhs.the_trees_.size() ? rhs.the_trees_[ i ] : nullptr;
      
      int which_case = t1 == nullptr ? 0 : 1;
      which_case += t2 == nullptr ? 0 : 2;
      which_case += carry == nullptr ? 0 : 4;

      if (i > rhs.the_trees_.size() && carry == nullptr) {
        break; //break if H2's vector of trees is empty and the carry is nullptr
        //I'm assuming that if i is greater than the size of rhs' tree vector,
        //it means that there are no more trees left in H2's (rhs') tree vector.
      }

      
      switch (which_case) {
      case 0:  // No trees.
      case 1:  // Only this tree.
      break;
      case 2:  // Only rhs tree.
      the_trees_[i] = t2;
      rhs.the_trees_[i] = nullptr;
      break;
      case 4:  // Only carry tree.
      the_trees_[i] = carry;
      carry = nullptr;
      break;
      case 3:  // this and rhs trees.
      if (t2 -> element_ > t1 -> element_) {
        std::swap(t2, t1); //if t2 is larger than t1, swap them
      }
      carry = CombineTrees(t1, t2);
      the_trees_[i] = rhs.the_trees_[i] = nullptr;
      break;
      case 5:  // this and carry trees.
      if (carry -> element_ > t1 -> element_) {
        std::swap(carry, t1); //if carry is larger than t1, swap them
      }
      carry = CombineTrees(t1, carry);
      the_trees_[i] = nullptr;
      break;
      case 6:  // rhs and carry trees.
      if (carry -> element_ > t2 -> element_) {
        std::swap(carry, t2); //if carry is larger than t2, swap them
      }
      carry = CombineTrees(t2, carry);
      rhs.the_trees_[i] = nullptr;
      break;
      case 7: // this, rhs and carry trees.
      if (t2 -> element_ > t1 -> element_) {
        std::swap(t2, t1); //if t2 is larger than t1, swap them
      }
      the_trees_[i] = carry;
      carry = CombineTrees(t1, t2);
      rhs.the_trees_[i] = nullptr;
      break;
      }
    }
    
    // Invalidate rhs tree.
    for (auto & root : rhs.the_trees_)
      root = nullptr;
    rhs.current_size_ = 0;
  }  // End of Merge Routine.


  private:
  struct BinomialNode {
    Comparable    element_;
    BinomialNode *left_child_;
    BinomialNode *next_sibling_;
    
    BinomialNode(const Comparable & e, BinomialNode *lt, BinomialNode *rt)
     : element_{e}, left_child_{lt}, next_sibling_{rt} {}
    
    BinomialNode(Comparable &&e, BinomialNode *lt, BinomialNode *rt)
     : element_{ std::move(e) }, left_child_{lt}, next_sibling_{rt} {}
  };


  vector<BinomialNode *> the_trees_;  // An array of tree roots.
  unsigned int current_size_;                  // Number of items in the priority queue.
  

  // Find index of tree containing the smallest item in the priority queue.
  // The priority queue must not be empty.
  // Return the index of tree containing the smallest item.
  int FindMinIndex() const {
    unsigned int i;
    int min_index;
    
    for (i = 0; the_trees_[i] == nullptr; ++i)
      ;

    for (min_index = i; i < the_trees_.size(); ++i)
      if (the_trees_[i] != nullptr &&
	  the_trees_[i]->element_ < the_trees_[min_index]->element_)
	min_index = i;
    
    return min_index;
  }


  // Return the Capacity, i.e. maximum items that can be stored
  // using all available trees in the arrray the_trees_.
  unsigned int Capacity() const { 
    return (1 << the_trees_.size()) - 1; 
  }
  
  // Return the result of merging equal-sized t1 and t2,
  // The return result is the root of the combined tree.
  BinomialNode * CombineTrees(BinomialNode *t1, BinomialNode *t2) {
    if (t2->element_ < t1->element_)
      return CombineTrees( t2, t1 );
    t2->next_sibling_ = t1->left_child_;
    t1->left_child_ = t2;
    return t1;
  }

  // Make a binomial tree logically empty, and free memory.
  // Start from given root t.
  void MakeEmpty(BinomialNode * & t) {
    if (t != nullptr) {
      MakeEmpty(t->left_child_);
      MakeEmpty(t->next_sibling_);
      delete t;
      t = nullptr;
    }
  }

  // A recursive function to insert a new node.
  // Basically, it inserts a node into the first nullptr spot 
  // it encounters in the vector of trees. 
  void NewInsert(BinomialNode* theNode, int counter) {
    if (current_size_ > Capacity()) {
      int old_number_of_trees = the_trees_.size();
      int new_number_of_trees = the_trees_.size() + 1;
      the_trees_.resize(new_number_of_trees);
      for (int i = old_number_of_trees; i < new_number_of_trees; ++i) {
           the_trees_[i] = nullptr; //handle any capacitiy issues (seen in Merge())
      }
    }

    if (the_trees_[counter] == nullptr) {
      the_trees_[counter] = theNode; //base case
    }

    else {
      BinomialNode* temp = CombineTrees(the_trees_[counter], theNode);
      the_trees_[counter] = nullptr;
      NewInsert(temp, counter + 1); //search the_trees_ until we encounter a nullptr
    }
  }
  
  // Clones tree with root t and returns root of cloned tree.
  BinomialNode * clone(BinomialNode * t) const {
    if (t == nullptr)
      return nullptr;
    else
      return new BinomialNode{ t->element_, clone(t->left_child_), clone(t->next_sibling_) };
    }
};

#endif  // COURSES_CSCI335_BINOMIAL_QUEUE_H_
