/******************************************************************************
Title       : AvlTree.h
Author      : Dan Cambitsis
Created on  : 3/8/2016
Description : Header + implementation for an AVL tree.
******************************************************************************/

#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "dsexceptions.h"
#include <algorithm>
#include <iostream> 
using namespace std;

// AvlTree class
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
// void printBetweenSequences( )  --> Prints all sequences between and including inquired sequences
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class AvlTree
{
  public:
    AvlTree( ) : root_{nullptr}
      { }
    
    AvlTree(const AvlTree & rhs) : root_{nullptr} {
        root_ = clone(rhs.root_);
    }

    AvlTree(AvlTree && rhs) : root_{rhs.root_} {
        rhs.root_ = nullptr;
    }
    
    ~AvlTree( ) {
        makeEmpty( );
    }

    /**
     * Deep copy.
     */
    AvlTree & operator=( const AvlTree & rhs ) {
        AvlTree copy = rhs;
        std::swap(*this, copy);
        return *this;
    }
        
    /**
     * Move.
     */
    AvlTree & operator=( AvlTree && rhs ) {
        std::swap(root_, rhs.root_);
        
        return *this;
    }
    
    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin(root_) -> element_;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax(root_) -> element_;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const string & seq ) {
        return contains(seq, root_);
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
    void printTree( ) const {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printTree(root_);
	cout << endl;
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( ) {
        makeEmpty(root_);
    }

    /**
     * Insert x into the tree; duplicates are merged.
     */
    void insert(const Comparable & x) {
        insert(x, root_);
    }
     
    /**
     * Insert x into the tree; duplicates are merged.
     */
    void insert(Comparable && x) {
        insert( std::move(x), root_ );
    }
     
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove(const string & seq) {
        remove( seq, root_ );
        --nodeCount;
    }

    /**
     * Return the height of the tree.
     */
    int heightOfTree() const {
      return heightOfNode(root_);
    }

    /**
     * Return the node count of the tree.
     */
    int getNodeCount() const {
        return nodeCount;
    }

    /**
     * Return the recursion count for find.
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
     * Calls a recursion function and alters theAcros (either empty or of sequence(s))
     */
    void getTheAcros(const string query, string & theAcros) {
        getTheAcrosRec(query, theAcros, root_);
    }

    /**
     * Return the sum of depths.
     */
    int getSumDepth(int depth) {
        return sumDepthRec(depth, root_);
    }

    /**
     * Calls a recursion function to print sequences between and including str1 and str2.
     */
    void printBetweenSequences(const string & str1, const string & str2) const {
    	printBetweenSequenceRec(str1, str2, root_);
    }

  private:
  	int nodeCount = 0;
  	int removeRecursionCount = 0;
  	int findRecursionCount = 0;
    struct AvlNode {
        Comparable element_;
        AvlNode *left_;
        AvlNode *right_;
        int height_;

        AvlNode( const Comparable & ele, AvlNode *lt, AvlNode *rt, int h = 0 )
          : element_{ ele }, left_{ lt }, right_{ rt }, height_{ h } { }
        
        AvlNode( Comparable && ele, AvlNode *lt, AvlNode *rt, int h = 0 )
          : element_{ std::move( ele ) }, left_{ lt }, right_{ rt }, height_{ h } { }
    };

    AvlNode *root_;


    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, AvlNode * & t ) {
        if( t == nullptr ) {
            t = new AvlNode{ x, nullptr, nullptr };
        	++nodeCount;
        }
        else if( x < t->element_ ) {
            insert( x, t->left_ );		
        }
        else if( t->element_ < x ) {
            insert( x, t->right_ );
        }
        else if(x.GetRecoSeq() == t -> element_.GetRecoSeq()) {
            t -> element_.Merge(x);
        } //duplicate
        
        balance( t );
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, AvlNode * & t ) {
        if( t == nullptr ) {
            t = new AvlNode{ std::move( x ), nullptr, nullptr };
        	++nodeCount;
        }
        else if( x < t->element_ ) {
            insert( std::move( x ), t->left_ );
        }
        else if( t->element_ < x ) {
            insert( std::move( x ), t->right_ );
        }
        else if(x.GetRecoSeq() == t -> element_.GetRecoSeq()) {
            t -> element_.Merge(x);
        } //duplicate
        
        balance( t );
    }
     
    /**
     * Internal method to remove seq from a subtree.
     * seq is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( const string & seq, AvlNode * & t ) {
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
            AvlNode *oldNode = t;
            t = ( t->left_ != nullptr ) ? t->left_ : t->right_;
            delete oldNode;
        }
        balance( t );
    }

    int sumDepthRec(int depth, AvlNode *t) {
        if (t == nullptr) {
            return 0;
        }
        return depth + sumDepthRec(depth + 1, t -> left_) + sumDepthRec(depth + 1, t -> right_);
    }
    
    static const int ALLOWED_IMBALANCE = 1;

    // Assume t is balanced or within one of being balanced
    void balance( AvlNode * & t ) {
        if( t == nullptr )
            return;
        
        if( heightOfNode( t->left_ ) - heightOfNode( t->right_ ) > ALLOWED_IMBALANCE ) {
            if( heightOfNode( t->left_->left_ ) >= heightOfNode( t->left_->right_ ) )
                rotateWithLeftChild( t );
            else
                doubleWithLeftChild( t );
        } else if( heightOfNode( t->right_ ) - heightOfNode( t->left_ ) > ALLOWED_IMBALANCE ) {
            if( heightOfNode( t->right_->right_ ) >= heightOfNode( t->right_->left_ ) )
                rotateWithRightChild( t );
            else
                doubleWithRightChild( t );
	}
        t->height_ = max( heightOfNode( t->left_ ), heightOfNode( t->right_ ) ) + 1;
    }
    
    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    AvlNode * findMin( AvlNode *t ) const {
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
    AvlNode * findMax( AvlNode *t ) const {
        if( t != nullptr )
            while( t->right_ != nullptr )
                t = t->right_;
        return t;
    }

     /**
     * Internal method to find the enzyme acronyms associated with the sequence.
     * No return, theAcros passed by reference should be updated.
     */
    void getTheAcrosRec(const string query, string & theAcros, AvlNode *t) {
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
    bool contains( const string & seq, AvlNode *t ) {
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
    bool contains( const Comparable & x, AvlNode *t ) const
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
    void makeEmpty( AvlNode * & t ) {
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
    void printTree( AvlNode *t ) const {
        if( t != nullptr )
        {
            printTree( t->left_ );
            cout << t-> element_.GetTheAcros() << ": " <<  t->element_.GetRecoSeq() << endl;
            printTree( t->right_ );
        }
    }

    /**
     * Prints inquired sequences and sequences between them.
     */
    void printBetweenSequenceRec(const string & str1, const string & str2, AvlNode *t) const {
    	if (t != nullptr) {
            printBetweenSequenceRec(str1, str2, t -> left_);
            if (t -> element_.GetRecoSeq() >= str1 && t -> element_.GetRecoSeq() <= str2) {
                cout << t -> element_.GetTheAcros() << ": " <<  t -> element_.GetRecoSeq() << endl;
            }
            printBetweenSequenceRec(str1, str2, t -> right_);
        }
    }

    /**
     * Internal method to clone subtree.
     */
    AvlNode * clone( AvlNode *t ) const {
        if( t == nullptr )
            return nullptr;
        else
            return new AvlNode{ t->element_, clone( t->left_ ), clone( t->right_ ), t->height_ };
    }
        // Avl manipulations
    /**
     * Return the height of node t or -1 if nullptr.
     */
    int heightOfNode( AvlNode *t ) const {
        return t == nullptr ? -1 : t->height_;
    }

    int max( int lhs, int rhs ) const {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left_ child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild( AvlNode * & k2 ) {
        AvlNode *k1 = k2->left_;
        k2->left_ = k1->right_;
        k1->right_ = k2;
        k2->height_ = max( heightOfNode( k2->left_ ), heightOfNode( k2->right_ ) ) + 1;
        k1->height_ = max( heightOfNode( k1->left_ ), k2->height_ ) + 1;
        k2 = k1;
    }

    /**
     * Rotate binary tree node with right_ child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild( AvlNode * & k1 ) {
        AvlNode *k2 = k1->right_;
        k1->right_ = k2->left_;
        k2->left_ = k1;
        k1->height_ = max( heightOfNode( k1->left_ ), heightOfNode( k1->right_ ) ) + 1;
        k2->height_ = max( heightOfNode( k2->right_ ), k1->height_ ) + 1;
        k1 = k2;
    }

    /**
     * Double rotate binary tree node: first left_ child.
     * with its right child; then node k3 with new left_ child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild( AvlNode * & k3 ) {
        rotateWithRightChild( k3->left_ );
        rotateWithLeftChild( k3 );
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left_ child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild( AvlNode * & k1 ) {
        rotateWithLeftChild( k1->right_ );
        rotateWithRightChild( k1 );
    }
};

#endif
