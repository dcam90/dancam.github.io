/******************************************************************************
Title       : TestTrees.cpp
Author      : Dan Cambitsis
Created on  : 3/8/2016
Description : TestTrees implementation.
******************************************************************************/

#include "BinarySearchTree.h"
#include "AvlTree.h"
#include "SequenceMap.h"

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

template <typename TreeType>
void TestQueryTree(TreeType & a_tree, ifstream & file2) {
  string query_line;
  double successQuery = 0, successRemove = 0, findRecursionCount = 0, removeRecursionCount = 0, averageDepth = 0;
  bool check = false;

  cout << "Node Count: " << a_tree.getNodeCount() << endl; //get the node count
  cout << "Sum Depth: " << a_tree.getSumDepth(0) << endl; //get the sumDepth with 0 as an argument
  averageDepth = static_cast<double>(a_tree.getSumDepth(0)) / static_cast<double>(a_tree.getNodeCount()); 
  //static cast the results to double to get a decimal #
  cout << "Average depth: " << averageDepth << endl; //print the average depth
  cout << "Average depth to log (base 2) of node count: " << averageDepth / log2(a_tree.getNodeCount()) << endl;
  //get the ratio
  cout << endl;

  cout << "Counting matches and removals ... " << endl;
  while (getline(file2, query_line)) { //while getting each line from sequences.txt ...
    if (a_tree.contains(query_line)) { //if the tree contains said line ...
      ++successQuery; //increment successQuery (found in tree)
      if (check) { //a conditional statement to remove every other successful query
        a_tree.remove(query_line); //remove the node that contains the line from the tree
        ++successRemove; //increment successRemove (removed in tree)
        check = false; //set check back to false (to prevent sequential removals)
        continue; //skip the below
      }

      check = true; //set check to true (to allow for removal of every other node)
    }
  }

  findRecursionCount = a_tree.getFindRecursionCount(); //get the recursion count for the contains function
  removeRecursionCount = a_tree.getRemoveRecursionCount(); //get the recursion count for the removal function

  cout << "Total number of successful queries: " << successQuery << endl;
  cout << "Total number of find recursion calls: " << findRecursionCount << endl;
  cout << "Average number of find recursion calls: " << findRecursionCount / successQuery << endl;
  cout << "Total number of removals: " << successRemove << endl;
  cout << "Total number of remove recursion calls: " << removeRecursionCount << endl;
  cout << "Average number of remove recursion calls: " << removeRecursionCount / successRemove << endl;
  cout << endl;

  cout << "Node Count: " << a_tree.getNodeCount() << endl;
  cout << "Sum Depth: " << a_tree.getSumDepth(0) << endl;
  averageDepth = static_cast<double>(a_tree.getSumDepth(0)) / static_cast<double>(a_tree.getNodeCount());
  cout << "Average depth: " << averageDepth << endl;
  cout << "Average depth to log (base 2) of node count: " << averageDepth / log2(a_tree.getNodeCount()) << endl;
}

string getAnEzAcro(const string db_line) {
  string theAcro;

  for (unsigned int i = 0; i < db_line.length(); i++) {
    if (db_line[i] == '/') {
      break; //break if a '/' is detected
    }

    theAcro += db_line[i]; //append all characters to theAcro until a '/' is reached
  }

  return theAcro;
}

void getARecoSeq(const string db_line, vector<string> & temp) {
  size_t pos = db_line.find('/');
  string seq;

  for (unsigned int i = pos + 1; i < db_line.length(); i++) {
    if (db_line[i] == '/' && db_line[i + 1] == '/') {
      temp.push_back(seq);
      break; //if a "//" is reached, push back the seq to a temp vector and break
    }
    if (db_line[i] == '/') { //this accounts for all sequences within a line
      temp.push_back(seq); //add the seq to the temp vector
      seq.clear(); //clear the string
      continue; //ignore the line below
    }

    seq += db_line[i]; //append characters of the line to the seq
  }
}

int main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename> <tree-type>" << endl;
    return 0;
  }
  string db_filename(argv[1]);
  string query_filename(argv[2]);
  string param_tree(argv[3]);
  cout << "Input file is " << db_filename << ", and query file is " << query_filename << endl;

  ifstream file(db_filename);
  ifstream file2(query_filename);
  string db_line;

  if (!file || !file2) {
    cout << "Unable to open database/query file, program will now terminate." << endl;
    exit(1);
  }

  for (int i = 0; i < 8; i++) {
    file.ignore(256, '\n'); //ignore the first 9 lines
  }

  if (param_tree == "BST") {
    cout << "I will run the BST code" << endl;
    BinarySearchTree<SequenceMap> a_tree;

    while (getline(file, db_line)) {
      string an_enz_acro = getAnEzAcro(db_line);
      vector<string> temp;
      getARecoSeq(db_line, temp);

      for (unsigned int i = 0; i < temp.size(); i++) {
        string a_reco_seq = temp[i];
        SequenceMap new_sequence_map(a_reco_seq, an_enz_acro);
        a_tree.insert(new_sequence_map);
      }
      
    }

    TestQueryTree(a_tree, file2);
  } 
  else if (param_tree == "AVL") {
    cout << "I will run the AVL code" << endl;
    AvlTree<SequenceMap> a_tree;

    while (getline(file, db_line)) {
      string an_enz_acro = getAnEzAcro(db_line);
      vector<string> temp;
      getARecoSeq(db_line, temp);
      
      for (unsigned int i = 0; i < temp.size(); i++) {
        string a_reco_seq = temp[i];
        SequenceMap new_sequence_map(a_reco_seq, an_enz_acro);
        a_tree.insert(new_sequence_map);
      }
    }
   
    TestQueryTree(a_tree, file2);
  } 
  else {
    cout << "Unknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }

  file.close();
  file2.close();

  return 0;
}

