/******************************************************************************
Title       : QueryTrees.cpp
Author      : Dan Cambitsis
Created on  : 3/8/2016
Description : QueryTrees implementation.
******************************************************************************/

#include "BinarySearchTree.h"
#include "AvlTree.h"
#include "SequenceMap.h"

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

template <typename TreeType>
void TestQueryTree(TreeType & a_tree) {
  string query, theAcros;
  cout << "Enter a sequence to be searched: ";
  cin >> query; //user enters a sequence
  a_tree.getTheAcros(query, theAcros);
  if (theAcros.empty()) { //if theAcros is an empty string (nothing found) ...
    cout << "Sorry, the sequence could not be found." << endl;
  }
  else { //else print theAcros
    cout << "Success! The enzyme(s) associated with the queried sequence is/are: ";
    cout << theAcros;
  }
  
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
  size_t pos = db_line.find('/'); //find the first '/' on the line
  string seq;

  for (unsigned int i = pos + 1; i < db_line.length(); i++) {
    if (db_line[i] == '/' && db_line[i + 1] == '/') {
      temp.push_back(seq); //if a "//" is reached, push back the seq to a temp vector and break
      break;
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
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <tree-type>" << endl;

    return 0;
  }
  string db_filename(argv[1]);
  string param_tree(argv[2]);
  cout << "Input filename is " << db_filename << endl;

  ifstream file(db_filename);
  string db_line;

  if (!file) {
    cout << "Unable to open file, program will now terminate." << endl;
    exit(1);
  }

  for (int i = 0; i < 8; i++) {
    file.ignore(256, '\n'); //ignore the first 9 lines
  }

  if (param_tree == "BST") {
    cout << "I will run the BST code" << endl;
    BinarySearchTree<SequenceMap> a_tree; //create a tree

    while (getline(file, db_line)) { //while getting a line from the database file ...
      string an_enz_acro = getAnEzAcro(db_line); //set an_enz_acro to getAnEzAcro from the line
      vector<string> temp; //create a temp vector
      getARecoSeq(db_line, temp); //if a line has one or more sequences, push them to the temp vector

      for (unsigned int i = 0; i < temp.size(); i++) {
        string a_reco_seq = temp[i]; //set a_reco_seq to a member of the temp vector
        SequenceMap new_sequence_map(a_reco_seq, an_enz_acro); //create a new SequenceMap object with an enzyme and its sequence
        a_tree.insert(new_sequence_map); //insert the object into the tree
      }
      
    }

    TestQueryTree(a_tree);
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
    TestQueryTree(a_tree);
  } 
  else {
    cout << "Unknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }

  file.close();

  return 0;
}
