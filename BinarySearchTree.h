/******************************************************************************
Title       : BinarySearchTree.h
Author      : Dan Cambitsis
Created on  : 3/8/2016
Description : Header + implementation for a BST tree.
******************************************************************************/

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <algorithm>
#include <iostream>
using namespace std;       

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// int getNodeCount( )    --> Returns the amount of nodes in tree
// int getFindRecursionCount( )  --> Returns the recursion count of contains
// int getRemoveRecursionCount( ) --> Returns the recursion count of remove
// void getTheAcros( )    --> Retrieves the acronyms associated with a sequence
// int getSumDepth( )     --> Returns the sum of the depth of each node
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree {
  public:
    BinarySearchTree( ) : root_{ nullptr } { }

    /**
     * Copy constructor
     */
    BinarySearchTree( const BinarySearchTree & rhs ) : root_{ nullptr } {
        root_ = clone( rhs.root_ );
    }

    /**
     * Move constructor
     */
    BinarySearchTree( BinarySearchTree && rhs ) : root_{ rhs.root_ } {
        rhs.root_ = nullptr;
    }
    
    /**
     * Destructor for the tree
     */
    ~BinarySearchTree( ) {
        makeEmpty( );
    }

    /**
     * Copy assignment
     */
    BinarySearchTree & operator=( const BinarySearchTree & rhs ) {
        BinarySearchTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move assignment
     */
    BinarySearchTree & operator=( BinarySearchTree && rhs ) {
        std::swap( root_, rhs.root_ );       
        return *this;
    }
    
    
    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root_ )->element_;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root_ )->element_;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const string & seq ) {
        return contains( seq, root_ );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const {
        return root_ == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ostream & out = cout ) const {
        if( isEmpty( ) )
            out << "Empty tree" << endl;
        else
            printTree( root_, out );
	out << endl;
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( ) {
        makeEmpty( root_ );
    }

    /**
     * Insert x into the tree; duplicates are merged.
     */
    void insert( const Comparable & x ) {
        insert( x, root_ );
    }
     
    /**
     * Insert x into the tree; duplicates are merged.
     */
    void insert( Comparable && x ) {
        insert( std::move( x ), root_ );
    }
    
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const string & seq ) {
        remove( seq, root_ );
        --nodeCount;
    }

    /**
     * Return the node count of the tree.
     */
    int getNodeCount() const {
        return nodeCount;
    }

    /**
     * Return the recursion count.
     */
    int getFindRecursionCount() const {
        return findRecursionCount;
    }

    /**
     * Return the recursion count for remove.
     */
    int getRemoveRecursionCount() const {
        return removeRecursionCount;
    }

    /**
     * Return the sum depth.
     */
    int getSumDepth(int depth) {
        return sumDepthRec(depth, root_);
    }

    /**
     * Calls a recursion function and alters theAcros (either empty or of sequence(s))
     */
    void getTheAcros(const string query, string & theAcros) {
        getTheAcrosRec(query, theAcros, root_);
    }

  private:
    int nodeCount = 0;
    int findRecursionCount = 0;
    int removeRecursionCount = 0;
    struct BinaryNode {
        Comparable element_;
        BinaryNode *left_;
        BinaryNode *right_;

        BinaryNode( const Comparable & the_element, BinaryNode *lt, BinaryNode *rt )
          : element_{ the_element }, left_{ lt }, right_{ rt } { }
        
        BinaryNode( Comparable && the_element, BinaryNode *lt, BinaryNode *rt )
          : element_{ std::move( the_element ) }, left_{ lt }, right_{ rt } { }
    };

    BinaryNode *root_;


    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that root_s the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, BinaryNode * & t ) {
        if( t == nullptr ) {
            t = new BinaryNode{ x, nullptr, nullptr };
            ++nodeCount;
        }
        else if( x < t->element_ ) {
            insert( x, t->left_ );
        }
        else if( t->element_ < x ) {
            insert( x, t->right_ );
        }
        else {
            t -> element_.Merge(x);
        } //duplicate
    }
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, BinaryNode * & t ) {
        if( t == nullptr ) {
            t = new BinaryNode{ std::move( x ), nullptr, nullptr };
            ++nodeCount;
        }
        else if( x < t->element_ ) {
            insert( std::move( x ), t->left_ );
        }
        else if( t->element_ < x ) {
            insert( std::move( x ), t->right_ );
        }
        else {
            t -> element_.Merge(x);
        } //duplicate
    }

    /**
     * Internal method to remove seq from a subtree.
     * seq is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( const string & seq, BinaryNode * & t ) {
        if( t == nullptr )
            return;   // Item not found; do nothing
        if( seq < t->element_.GetRecoSeq() ) {
            ++removeRecursionCount;
            remove( seq, t->left_ );
        }
        else if( t->element_.GetRecoSeq() < seq ) {
            ++removeRecursionCount;
            remove( seq, t->right_ );
        }
        else if( t->left_ != nullptr && t->right_ != nullptr ) // Two children
        {
            ++removeRecursionCount;
            t->element_.GetRecoSeq() = findMin( t->right_ )->element_.GetRecoSeq();
            remove( t->element_.GetRecoSeq(), t->right_ );
        }
        else {
            BinaryNode *oldNode = t;
            t = ( t->left_ != nullptr ) ? t->left_ : t->right_;
            delete oldNode;
        }
    }

    /**
     * Internal method to find the total depth of tree.
     * Return depth + recursion results.
     */
    int sumDepthRec(int depth, BinaryNode *t) {
        if (t == nullptr) {
            return 0;
        }
        return depth + sumDepthRec(depth + 1, t -> left_) + sumDepthRec(depth + 1, t -> right_);
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    BinaryNode * findMin( BinaryNode *t ) const {
        if( t == nullptr )
            return nullptr;
        if( t->left_ == nullptr )
            return t;
        return findMin( t->left_ );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    BinaryNode * findMax( BinaryNode *t ) const {
        if( t != nullptr )
            while( t->right_ != nullptr )
                t = t->right_;
        return t;
    }

    /**
     * Internal method to find the enzyme acronyms associated with the sequence.
     * No return, theAcros passed by reference should be updated.
     */
    void getTheAcrosRec(const string query, string & theAcros, BinaryNode *t) {
        if (t == nullptr) {
            return; //return an empty string
        }
        else if (query < t-> element_.GetRecoSeq()) {
            getTheAcrosRec(query, theAcros, t -> left_);
        }
        else if (query > t -> element_.GetRecoSeq()) {
            getTheAcrosRec(query, theAcros, t -> right_);
        }
        else {
            theAcros = t -> element_.GetTheAcros();
        }
    }

    /**
     * Internal method to test if a sequence is in a subtree.
     * seq is the sequence to search for.
     * t is the node that roots the tree.
     */
    bool contains( const string & seq, BinaryNode *t ) {
        if( t == nullptr ) {
            return false;
        }
        else if( seq < t->element_.GetRecoSeq() ) {
            ++findRecursionCount;
            return contains( seq, t->left_ );
        }
        else if( t->element_.GetRecoSeq() < seq ) {
            ++findRecursionCount;
            return contains( seq, t->right_ );
        }
        else
            return true;    // Match
    }
/****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        while( t != nullptr )
            if( x < t->element_ )
                t = t->left_;
            else if( t->element_ < x )
                t = t->right_;
            else
                return true;    // Match

        return false;   // No match
    }
*****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( BinaryNode * & t ) {
        if( t != nullptr )
        {
            makeEmpty( t->left_ );
            makeEmpty( t->right_ );
            delete t;
            --nodeCount;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( BinaryNode *t, ostream & out ) const {
        if( t != nullptr )
        {
            printTree( t->left_, out );
            out << t-> element_.GetTheAcros() << ": " <<  t->element_.GetRecoSeq() << endl;
            printTree( t->right_, out );
        }
    }

    /**
     * Internal method to clone subtree.
     */
    BinaryNode * clone( BinaryNode *t ) const {
        if( t == nullptr )
            return nullptr;
        else
            return new BinaryNode{ t->element_, clone( t->left_ ), clone( t->right_ ) };
    }
};

#endif
